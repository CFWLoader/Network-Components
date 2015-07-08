#include "ClownThread.h"
#include "CallBackClass.h"

#include <functional>

using namespace clown;
using namespace std;

int main(int argc, char* argv[])
{
	CallBackClass cbc;

	Thread theThread(cbc.getCallBack());

	theThread.start();

	theThread.join();

	return 0;
}