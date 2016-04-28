#include <iostream>

//#include "../File.h"
//#include "../File.cpp"

#include <File.h>

using namespace std;

using namespace nc;
using namespace nc::util;

int main(int argc, char* argv[])
{
	string filename = "./Temporary Datafiles/LogFiles1.log";

	File al(filename);

	string data = "asd56f1as6dg15a641g65a1g35a1dfg\n";

	for(int i = 0; i < 1024; ++i)
	{
		while(data.size() < 64 * 1024)
		{
			data.append("asd56f1as6dg15a641g65a1g35a1dfg\n");
		}

		al.append(data.data(), data.size());

		data.clear();
	}

	//al.append(data.c_str(), data.size());

	return 0;
}