#include <iostream>
#include <functional>

#include "Thread.h"

using namespace std;
using namespace soran;

int main(int argc, char* argv[])
{
	Thread thread([](){cout << "Thread " << pthread_self() << " is saying Hello!" << endl;});

	if(thread.start())
	{
		cout << "Failed to create thread!" << endl;
	}
	// else
	// {
	// 	cout << "The thread is executing." << endl;
	// }

	cout << "Main thread " << pthread_self() << " is saying " << endl;

	return 0;
}
