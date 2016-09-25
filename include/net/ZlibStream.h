#pragma once

#include <nc/net/Buffer.h>
#include <nc/util/Noncopyable.hpp>

#pragma GCC diagnostic ignored "-Wold-style-cast"

#include <zlib.h>

namespace nc
{
	namespace net
	{
		class ZlibInputStream : nc::util::Noncopyable
		{
		public:

			explicit ZlibInputStream(Buffer* output) :
				output_(output),
				zerror_(Z_OK)
			{
				bzero(&zstream_, sizeof zstream_);

				zerror_ = inflateInit(&zstream_);
			}

			~ZlibInputStream()
			{
				finish();
			}

			bool write(StringPiece buf);

			bool write(Buffer* input);

			bool finish();

		private:

			int decompress(int flush);

			BUffer* output_;

			z_stream zstream_;

			int zerror_;
		};

		class ZlibOutputStream : nc::util::Noncopyable
		{
		public:

			explicit ZlibOutputStream(Buffer* output) :
				output_(output),
				zerror_(Z_OK),
				bufferSize_(1024)
			{
				bzero(&zstream_, sizeof zstream_);

				zerror_ = deflateInit(&zstream_, Z_DEFAULT_COMPRESSION);
			}

			~ZlibOutputStream()
			{
				finish();
			}

			const char* zlibErrorMessage() const
			{
				return zstream_.msg;
			}

			int zlibErrorCode() const
			{
				return zerror_;
			}

			int64_t inputBytes() const
			{
				return zstream_.total_in;
			}

			int64_t outputBytes() const
			{
				return zstream_.total_out;
			}

			int internalOutputBufferSize() const
			{
				return bufferSize_;
			}

			bool write(StringPiece buf)
			{
				if(zerror_ != Z_OK)
				{
					return false;
				}

				assert(zstream_.next_in == NULL && zstream_.avail_in == 0);

				void* in = const_cast<char*>(buf.data());

				zstream_.next_in = static_cast<Bytef*>(in);

				zstream_.avail_in = buf.size();

				while(zstream_.avail_in > 0 && zerror_ == Z_OK)
				{
					zerror_ = compress(Z_NO_FLUSH);
				}

				if(zstream_.avail_in == 0)
				{
					assert(static_cast<const void*>(zstream_.next_in) == buf.end());

					zstream_.next_in = NULL;
				}  

				return zerror_ == Z_OK;
			}

			bool write(Buffer* input)
			{
				if(zerror_ != Z_OK)
				{
					return false;
				}

				void* in = const_cast<char*>(input->peek());

				zstream_.next_in = static_cast<Bytef*>(in);

				zstream_.avail_in = static_cast<int>(input->readableBytes());

				if(zstream_.avail_in > 0 && zerror_ == Z_OK)
				{
					zerror_ = compress(Z_NO_FLUSH);
				}

				input->retrieve(input->readableBytes() - zstream_.avail_in);

				return zerror_ == Z_OK;
			}

			bool finish()
			{
				if(zerror_ != Z_OK)
				{
					return false;
				}

				while(zerror_ == Z_OK)
				{
					zerror_ = compress(Z_FINISH);
				}

				zerror_ = defalteEnd(&zstream_);

				bool ok = zerror_ == Z_OK;

				zerror_ = Z_STREAM_END;

				return ok;
			}

		private:

			int compress(int flush)
			{
				output->ensureWritableBytes(bufferSize_);

				zstream_.next_out = reinterpret_cast<Bytef*>(output_->beginWrite());

				zstream_.avail_in = static_cast<int>(output_->writableBytes());

				int error = ::deflate(&zstream_, flush);

				output->hasWritten(output_->writableBytes() - zstream_.avail_out);

				if(output->writableBytes() == 0 && bufferSize_ < 65535)
				{
					bufferSize_ *= 2;
				}

				return error;
			}

			Buffer* output_;

			z_stream zstream_;

			int zerror_;

			int bufferSize_;
		};
	}
}