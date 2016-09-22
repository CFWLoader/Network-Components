#ifndef NET_POLLER_H_
#define NET_POLLER_H_

#include <map>
#include <vector>

#include <nc/util/Noncopyable.hpp>
#include <nc/util/Timestamp.h>
#include <nc/net/EventLoop.h>

namespace nc
{
	namespace net
	{
		class Channel;

		class Poller : nc::util::Noncopyable
		{
		public:

			typedef std::vector<Channel*> ChannelList;

			Poller(EventLoop* loop);

			virtual ~Poller();

			virtual Timestamp poll(int timeoutMs, ChannelList* activeChannels) = ;

			virtual void updateChannel(Channel* channel) = 0;

			virtual void removeChannel(Channel* channel) = 0;

			virtual bool hasChannel(Channel* channel) const;

			static Poller* newDefaultPoller(EventLoop* loop);

			void assertInLoopThread() const
			{
				ownerLoop_->assertInLoopThread();
			}

		protected:

			typedef std::map<int, Channel*> ChannelMap;

			ChannelMap channels_;

		private:

			EventLoop* ownerLoop_;
		}
	}
}

#endif