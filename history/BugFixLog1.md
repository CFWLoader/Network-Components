#	Destructor and multithreading.
###	2015.07.06	-	2015.07.12<br/>
This period I found a bug that TcpServer will crash if the client abort the connection. The direct reason is I used C++11 new trait -- std::bind.<br/>
But the deep level reason is I ignore the destructor's execution time is different in different threads.<br/>
In my algorithom, TcpServer will dispatch a new thread to serve the active client socket file description(SFD).<br/>
### Code:
```
clown::Event clientEventThread(
					clientEvents[i].data.fd,
					std::bind(&TcpServer::closeClientFD, this, static_cast<int>(clientEvents[i].data.fd))
					);

				clientEventThread->happen();
```
In every thread serving the active client SFD, I pass a callback function to them for closing the SFD if the client abort the connection<br/>
via std::bind() in order to server do some left work(such as unregister in server's client table).<br/>
The problem comes, the client aborting connection triggers the closing callback function and leads to segment fault.<br/>
I tried pass the raw pointer of TcpServer and let the programm runs in single thread and the crash does not occur.<br/>
I guessed other reasons and proved they're wrong.<br/>
The reason is the clown::Event instance is destructed in the TcpServer main thread and the service thread references the destructed object.<br/>
std::function is an object instance that will be destructed when the outter object is being destructed.<br/>
In the start, I suspect it the bug of std library and replace the std::bind with boost::bind and the problem still unsolved.<br/>
It's sure that the reason is my codes.<br/>
<br/>
Why the segment fault do not happen if I pass the raw pointer of TcpServer instance in place of std::function()?<br/>
Because the raw pointer is a value. But it's still dangerous if we use the value in destructed object.<br/>
<br/>
After figuring out the problem. I fixed the code as the following.
### Code:
```
clown::Event* clientEventThread = new clown::Event(
					clientEvents[i].data.fd,
					std::bind(&TcpServer::closeClientFD, this, static_cast<int>(clientEvents[i].data.fd))
					);

				clientEventThread->happen();
```
But it still has a problem: How to control the destruction time of the thread?<br/>
In current implements, I transit the destruction control to the service.In future, I will use thread pool to optimize it.
### Code:
```
void clown::Event::serveFunction()
{
	/*
	Logical codes.
	*/

	delete this;
}
```
Here are some advice:
-	You should check the timing of destruction if you are coding multithreading program and encountered segment fault.
-	The bug of library is the last thing being considered.
-	Pointer may be the powerful tools in multithreading.