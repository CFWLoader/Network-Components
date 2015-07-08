#include "CallBackClass.h"

#include <iostream>

#include <functional>

using namespace clown;

void CallBackClass::callBackFunction()
{
	std::cout << "Call back!" << std::endl;	
}

Thread::ThreadFunction CallBackClass::getCallBack()
{
	return std::bind(&CallBackClass::callBackFunction, this);
}