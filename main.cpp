#include <iostream>
#include <functional>

#include <unistd.h>

#include "Thread.h"

using namespace std;
using namespace soran;

int main(int argc, char* argv[])
{
	Thread thread([](){

		cout << "Thread " << pthread_self() << " is saying Hello!" << endl;

		sleep(3);

		cout << "Thread " << pthread_self() << " woke!" << endl;
	});

	if(thread.start())
	{
		cout << "Failed to create thread!" << endl;
	}
	// else
	// {
	// 	cout << "The thread is executing." << endl;
	// }

	if(thread.detach())
	{
		cout << "Failed to detach thread!" << endl;
	}

	cout << "Main thread " << pthread_self() << " is saying Hello!" << endl;

	return 0;
}
