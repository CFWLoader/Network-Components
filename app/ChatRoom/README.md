#	Chat Room
-	The little project is under experiment.

### Current Problems
-	Unknown Reason: The invoke of binded function will crash the server program when the server use multithreading.
	-	Probable Reason 1: The the binded function is stack-private.But when I pass a pointer pointing to the server, the pointer
		do effect.
	-	Probable Reason 2: The binded function is an c++ object, the crash happened in thread_create's 4th parameter is a pointer.
		A static_cast can't invoke the constructor of binded function and the content of binded function haven't been initialized.