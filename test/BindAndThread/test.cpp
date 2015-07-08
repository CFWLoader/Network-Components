#include "ClownThread.h"
#include "CallBackClass.h"

#include <functional>
#include <iostream>

#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>

#include <cstdio>

using namespace clown;
using namespace std;

int main(int argc, char* argv[])
{
	CallBackClass cbc;

	Thread theThread(cbc.getCallBack());

	pid_t theMainThreadID = static_cast<pid_t>(::syscall(SYS_gettid));

	//cout << "Main Thread ID: " << static_cast<unsigned long>(theMainThreadID) << end;

	printf("Main Thread ID: %ld\n", theMainThreadID);

	theThread.start();

	//theThread.join();
	//cbc.busy();
	cbc.sleep();

	return 0;
}