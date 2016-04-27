#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

#include "../MutexLock.h"

class MultiThreadCounter
{
public:

	void increase()
	{
		mutexLock.lock();

		std::cout << " From  " << countValue;

		++countValue;

		std::cout << " to " << countValue << std::endl;

		mutexLock.unlock();
	}

private:

	clown::MutexLock mutexLock;

	int countValue;
};

static MultiThreadCounter theCounter;

void* threadFunction(void* arg)
{
	int localCounter;

	int threadId = static_cast<int>(syscall(SYS_gettid));

	for(localCounter = 0; localCounter < 100; ++localCounter)
	{
		std::cout << "Thread ID:   " << threadId;

		theCounter.increase();
	}

	return nullptr;
}

int main(int argc, char* argv[])
{
	pthread_t threads[20];

	for(int index = 0; index < 20; ++index)
	{

		pthread_create(&threads[index], 0, threadFunction, 0);

		pthread_join(threads[index], 0);

	}

	return 0;
}