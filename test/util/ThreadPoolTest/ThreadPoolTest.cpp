#include <iostream>
#include <functional>

#include <unistd.h>

#include <util/ThreadPool.h>

using namespace std;
using namespace soran::util;

int main(int argc, char* argv[])
{
	ThreadPool* threadPool = new ThreadPool(3);

	for(int idx = 0; idx < 100000000; ++idx)
	{
		threadPool->submit([idx](){
			cout << "Hello!" << idx << endl;
		});
	}

	threadPool->joinAll();

	while(threadPool->hasTasks());

	cout << "Sending kill signal." << endl;

	threadPool->shutdownAll();

	return 0;
}
