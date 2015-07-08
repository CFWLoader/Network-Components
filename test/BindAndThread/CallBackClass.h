#ifndef CALLBACKCLASS_H_
#define CALLBACKCLASS_H_

#include "ClownThread.h"

namespace clown
{
	class CallBackClass
	{
	public:
		void callBackFunction();

		Thread::ThreadFunction getCallBack();
	private:
	};
}

#endif