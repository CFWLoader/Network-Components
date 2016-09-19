#ifndef NET_CHANNEL_H_
#define NET_CHANNEL_H_

#include <functional>
#include <memory>
#include <nc/util/Noncopyable.hpp>

#include <nc/util/Timestamp.h>

namespace nc
{
	namespace net
	{
		class EventLoop;

		class Channel : nc::util::Noncopyable
		{
		public:

			typedef std::function<void()> EventCallback;

			typedef std::function<void(Timestamp)> ReadEventCallback;

			Channel(EventLoop* loop, int fd);

			~Channel();

			void handleEvent(Timestamp receiveTime);

			void setReadCallback(const ReadEventCallback& cb)
			{
				readCallback_ = cb;
			}

			void setWriteCallback(const EventCallback& cb)
			{
				writeCallback_ = cb;
			}

			void setCloseCallback(const EventCallback& cb)
			{
				closeCallback_ = cb;
			}

			void setErrorCallback(const EventCallback& cb)
			{
				errorCallback_ = cb;
			}

#ifdef __GXX_EXPERIMENTAL_CXX0X__

			void setReadCallback(ReadEventCallback&& cb)
			{
				readCallback_ = std::move(cb);
			}

			void setWriteCallback(EventCallback&& cb)
			{
				writeCallback_ = std::move(cb);
			}

			void setCloseCallback(EventCallback&& cb)
			{
				closeCallback_ = std::move(cb);
			}

			void setErrorCallback(EventCallback&& cb)
			{
				errorCallback_ = std::move(cb);
			}

#endif

			void tie(const std::shared_ptr<void>&);

			int fd() const
			{
				return fd_;
			}

			int events() const
			{
				return events_;
			}

			void set_revents(int revt)
			{
				revents_ = revt;
			}

			bool isNoneEvent() const
			{
				return events_ == kNoneEvent;
			}

			void enableReading()
			{
				events_ |= kReadEvent;

				update();
			}

			void disableReading()
			{
				events_ &= ~kReadEvent;

				update();
			}

			void enableWriting()
			{
				events_ |= kWriteEvent;

				update();
			}

			void disableWriting()
			{
				events_ &= ~kWriteEvent;

				update();
			}

			void disableAll()
			{
				events_ = kNoneEvent;

				update();
			}

			bool isWriting() const
			{
				return events_ & kWriteEvent;
			}

			bool isReading() const
			{
				return events_ & kReadEvent;
			}

			int index()
			{
				return index_;
			}

			void set_index(int idx)
			{
				index_ = idx;
			}

			string reventsToString() const;

			string eventsToString() const;

			void doNotLogHup()
			{
				logHup_ = false;
			}

			EventLoop* ownerLoop()
			{
				return loop_;
			}

			void remove();

		private:

			static string eventsToString(int fd, int ev);

			void update();

			void handleEventWithGuard(Timestamp receiveTime);

			static const int kNoneEvent;

			static const int kReadEvent;

			static const int kWriteEvent;

			EventLoop* loop_;

			const int fd_;

			int events_;

			int revents_;

			int index_;

			bool logHup_;

			std::weak_ptr<void> tie_;

			bool tied_;

			bool eventHandling_;

			bool addedToLoop_;

			ReadEventCallback readCallback_;

			EventCallback writeCallback_;

			EventCallback closeCallback_;

			EventCallback errorCallback_;
		};
	}
}


#endif