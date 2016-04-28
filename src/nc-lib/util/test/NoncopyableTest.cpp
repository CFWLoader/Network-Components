#include <iostream>

#include <Noncopyable.hpp>

using namespace nc;
using namespace nc::util;

using namespace std;

class DerivedNoncopyable : public Noncopyable{};

int main(int argc, char* argv[])
{
	DerivedNoncopyable a1;
	//DerivedNoncopyable a2(a1);
	return 0;
}
