#include <nc/net/EventLoop.h>

#include <nc/util/Logging.h>
#include <nc/util/Mutex.h>
#include <nc/net/Channel.h>
#include <nc/net/Poller.h>
#include <nc/net/SocketsOps.h>
#include <nc/net/TimerQueue.h>

#include <functional>

#include <signal.h>
#include <sys/eventfd.h>

using namespace nc;
using namespace nc::net;

namespace
{
	__thread EventLoop* t_loopInThisThread = 0;

	const int kPollTimeMs = 10000;

	int createEventfd()
	{
		int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);

		if(evtfd < 0)
		{
			LOG_SYSERR << "Failed in eventfd";
			abort();
		}

		return evtfd;
	}

#pragma GCC diagnostic ignored "-Wold-style-cast"
	class IgnoreSigPipe
	{
	public:
		IgnoreSigPipe()
		{
			::signal(SIGPIPE, SIG_IGN);
		}
	};

#pragma GCC diagnostic error "-Wold-style-cast"

	IgnoreSigPipe initObj;
}

EventLoop* EventLoop::getEventLoopOfCurrentThread()
{
	return t_loopInThisThread;
}

EventLoop::EventLoop() :
	looping_(false),
	quit_(false),
	eventHandling_(false),
	callingPendingFunctors_(false),
	iteration_(0),
	threadId_(CurrentThread::tid()),
	poller_(Poller::newDefaultPoller(this)),
	timerQueue_(new TimerQueue(this)),
	wakeupFd_(createEventfd()),
	wakeupChannel_(new Channel(this, wakeupFd_)),
	currentActiveChannel_(NULL)
{
	LOG_DEBUG << "EventLoop created " << this << " in thread " << threadId_;

	if(t_loopInThisThread)
	{
		LOG_FATAL << "Another EventLoop " << t_loopInThisThread << " exists in this thread " << threadId_;
	}
	else
	{
		t_loopInThisThread = this;
	}
}

EventLoop::~EventLoop()
{
	LOG_DEBUG << "EventLoop " << this << " of thread " << threadId_
		<< " destructs in thread " << CurrentThread::tid();

	wakeupChannel_->disableAll();

	wakeupChannel_->remove();
	
	::close(wakeupFd_);

	t_loopInThisThread = NULL;
}

void EventLoop::loop()
{
	assert(!looping_);

	assertInLoopThread();

	looping_ = true;

	quit_ = false;

	LOG_TRACE << "EventLoop " << this << " start looping";

	while(!quit_)
	{
		activeChannels_.clear();

		pollReturnTime_ = poller_->poll(kPollTimeMs, &activeChannels_);

		++iteration_;

		if(Logger::logLevel() <= Logger::TRACE)
		{
			printActiveChannels();
		}

		eventHandling_ = true;

		for(ChannelList::iterator it = activeChannels_.begin();
			it != activeChannels_.end(); ++it)
		{
			currentActiveChannel_ = *it;

			currentActiveChannel_->handleEvent(pollReturnTime_);
		}

		currentActiveChannel_ = NULL;

		eventHandling_ = false;

		doPendingFunctors();
	}

	LOG_TRACE << "EventLoop " << this << " stop looping";

	looping_ = false;
}