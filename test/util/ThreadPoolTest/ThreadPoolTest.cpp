#include <iostream>
#include <functional>

#include <unistd.h>

#include <util/ThreadPool.h>

using namespace std;
using namespace soran::util;

int main(int argc, char* argv[])
{
	ThreadPool threadPool(3);

	return 0;
}
