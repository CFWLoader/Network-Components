#include "CallBackClass.h"

#include <iostream>

#include <functional>

#include <cstdlib>
#include <unistd.h>

using namespace clown;

void CallBackClass::callBackFunction()
{
	int counter;

	for(counter = 1; counter < 11; ++counter)
		std::cout << "Call back!" << std::endl;	
}

Thread::ThreadFunction CallBackClass::getCallBack()
{
	return std::bind(&CallBackClass::callBackFunction, this);
}

void CallBackClass::busy()
{
	while(true);
}

int CallBackClass::sleep()
{
	sleep(3);
}