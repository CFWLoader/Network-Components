#	Chat Room
-	The little project is under experiment.

### Fixed Problems
-	The invoke of binded function will crash the server program when the server use multithreading.
	-	Reason: Object isn't a pointer and will be destructed in the server thread.The service thread references an invalid object and crashed because invoke the function of an invalid function.
	-	Solution: Use pointer to cancel the life-cycle management.Use Shared pointer to intelligently manage the instances.

### Current Problems
-	Manage the Event instance pointers via intelligent pointer.