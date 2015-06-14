# Network-Components

This project is linux-based library network components and using c++ 11 programming priciples.<br/>
Also, multithreading will be added in order to promote the library's performance.<br/>

### Document 'lib' is the components I encapsulated from linux C interface to C++ classes.<br/>
### Document 'dev' is the components I'm developing.<br/>
### Document 'test' is the test units.But the 'dev' has unit test files, so 'test' seems it will contain integrated tests.<br/>
### Document 'app' is the applications use the components.<br/>

I'm still thinking how to organize this project.Especially the test units.<br/>
Java object design is worth being referenced, so you will see some java style.<br/>

#This version
Add utility -- AppendLogger, a class that providing the interface to append string to a file.(2015-06-14)<br/>

## Update History
Add a class -- Noncopyable, this class is mainly for being inherited by the class that forbidding copy.(2015-06-13)<br/>