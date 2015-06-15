#include <iostream>

#include "../Noncopyable.hpp"

using namespace clown;
using namespace clown::utilities;

using namespace std;

class DerivedNoncopyable : public Noncopyable{};

int main(int argc, char* argv[])
{
	DerivedNoncopyable a1;
	//DerivedNoncopyable a2(a1);
	return 0;
}
