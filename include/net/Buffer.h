#ifndef NET_BUFFER_H_
#define NET_BUFFER_H_

#include <nc/util/Copyable.hpp>
#include <nc/util/StringPiece.h>
#include <nc/util/Types.h>

#include <nc/net/Endian.h>

#include <algorithm>
#include <vector>

#include <assert.h>
#include <string.h>

namespace nc
{
	namespace net
	{
		class Buffer : public nc::util::Copyable
		{
		public:

			static const size_t kCheapPrepend = 8;

			static const size_t kInitialSize = 1024;

			explicit Buffer(size_t initialSize = kInitialSize) :
				buffer_(kCheapPrepend + initialSize),
				readerIndex_(kCheapPrepend),
				writerIndex_(kCheapPrepend)
			{
				assert(readableBytes() == 0);

				assert(writableBytes() == 0);

				assert(prependableBytes() == 0);
			}

			void swap(Buffer& rhs)
			{
				buffer_.swap(rhs.buffer_);

				std::swap(readerIndex_, rhs.readerIndex_);

				std::swap(writerIndex_, rhs.writerIndex_);
			}

			size_t readableBytes() const
			{
				return writerIndex_ - readerIndex_;
			}

			size_t writableBytes() const
			{
				return buffer_.size() -writerIndex_;
			}

			size_t prependableBytes() const
			{
				return readerIndex_;
			}

			const char* peek() const
			{
				return readerIndex_;
			}

			const char* findCRLF() const
			{
				const char* crlf = std::search(peek(), beginWrite(), kCRLF, kCRLF + 2);

				return crlf == beginWrite() ? NULL : crlf;
			}

			const char* findCRLF(const char* start) const
			{
				assert(peek() <= start);

				assert(start <= beginWrite());

				const char* crlf = std::search(start, beginWrite(), kCRLF, kCRLF + 2);

				return crlf == beginWrite() ? NULL : crlf;
			}

			const char* findEOL() const
			{
				const void* eol = memchr(peek(), '\n', readableBytes());

				return static_cast<const char*>(eol);
			}

			const char* findEOL(const char* start) const
			{
				assert(peek() <= start);

				assert(start <= beginWrite());

				const void* eol = memchr(start, '\n', beginWrite() - start);

				return static_cast<const char*>(eol);
			}

			void retrieve(size_t len)
			{
				assert(len <= readableBytes());

				if(len < readableBytes())
				{
					readerIndex_ += len;
				}
				else
				{
					retrieveAll();
				}
			}

			void retrieveUntil(const char* end)
			{
				assert(peek() <= end);

				assert(end <= beginWrite());

				retrieve(end - peek());
			}

			void retrieveInt64()
			{
				retrieve(sizeof(int64_t));
			}

			void retrieveInt32()
			{
				retrieve(sizeof(int32_t));
			}

			void retrieveInt16()
			{
				retrieve(sizeof(int16_t));
			}

			void retrieveInt8()
			{
				retrieve(sizeof(int8_t));
			}

			void retrieveAll()
			{
				readerIndex_ = kCheapPrepend;
				writerIndex_ = kCheapPrepend;
			}

			string retrieveAllAsString()
			{
				return retrieveAsString(readableBytes());
			}

			string retrieveAsString(size_t len)
			{
				assert(len <= readableBytes());

				string result(peek(), len);

				retrieve(len);

				return result;
			}

			StringPiece toStringPiece() const
			{
				return StringPiece(peek(), static_cast<int>(readableBytes()));
			}

			void append(const StringPiece& str)
			{
				append(str.data(), str.size());
			}

			void append(const char* data, size_t len)
			{
				ensureWritableBytes(len);

				std::copy(data, data + len, beginWrite());

				hasWritten(len);
			}

			void append(const void* data, size_t len)
			{
				append(static_cast<const char*>(data), len);
			}

			void ensureWritableBytes(size_t len)
			{
				if(writableBytes() < len)
				{
					makeSpace(len);
				}

				assert(writableBytes() >= len);
			}

			char* beginWrite()
			{
				return begin() + writerIndex_;
			}

			const char* beginWrite() const
			{
				return begin() + writerIndex_;
			}

			void hasWritten(size_t len)
			{
				assert(len <= writableBytes());

				writerIndex_ += len;
			}

			void unwrite(size_t len)
			{
				assert(len <= readableBytes());

				writerIndex_ -= len;
			}

			void appendInt64(int64_t x)
			{
				int64_t be64 = sockets::hostToNetWork64(x);

				append(&be64, sizeof be64);
			}

		private:

			std::vector<char> buffer_;

			size_t readerIndex_;

			size_t writerIndex_;

			static const char kCRLF[];
		};
	}
}

#endif