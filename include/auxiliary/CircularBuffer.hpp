#ifndef AUXILIARY_CIRCULAR_BUFFER_H_
#define AUXILIARY_CIRCULAR_BUFFER_H_

#include <algorithm>
#include <cstddef>
#include <cassert>
#include <stdexcept>
#include <iostream>

namespace nc
{
	namespace aux
	{
		template<typename T>
		class CircularBuffer
		{
		public:

			typedef size_t size_type;
			typedef T& reference;
			typedef const T& const_reference;
			typedef T* pointer;
			typedef const T* const_pointer;

			explicit CircularBuffer(size_type);

			CircularBuffer(const CircularBuffer<T>&);

			CircularBuffer(CircularBuffer<T>&);

			~CircularBuffer();

			size_type size() const;

			size_type capacity() const;

			bool isFull() const;

			const_reference

		private:

			pointer buffer_;

			size_type capacity_;

			size_type front_;

			bool full_;
		};
	}
}

#endif