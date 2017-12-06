#include <iostream>
#include <functional>

#include <unistd.h>

#include <util/ThreadPool.h>

using namespace std;
using namespace soran::util;

int main(int argc, char* argv[])
{
	ThreadPool threadPool(3);

	sleep(4);

	cout << "Sending kill signal." << endl;

	threadPool.shutdownAll();

	threadPool.joinAll();

	return 0;
}
