#include <iostream>
#include <functional>

#include <unistd.h>

#include <util/ThreadPool.h>

using namespace std;
using namespace soran::util;

int main(int argc, char* argv[])
{
	ThreadPool* threadPool = new ThreadPool(3);

	for(int idx = 0; idx < 100; ++idx)
	{
		threadPool->submit([idx](){
			cout << "Hello!" << idx << endl;
		});
	}

	sleep(4);

	// cout << "Sending kill signal." << endl;

	// threadPool.shutdownAll();

	threadPool->joinAll();

	return 0;
}
