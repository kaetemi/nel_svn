
#include "nel/misc/app_context.h"
#include "nel/misc/debug.h"
#include "nel/misc/sstring.h"

#include "cpptest.h"

using namespace std;
using namespace NLMISC;

// Test suite for CSString class
class CSStringTS : public Test::Suite
{
public:
	CSStringTS ()
	{
		TEST_ADD(CSStringTS::testStrtok);

		// TODO insert code from ryzom/test/sstring.cpp
	}
	
	void testStrtok()
	{
		CSString testLine("  a=b  c   (a=e b=c) \t\t  c(a=e b=c) toto(bimbo(foo(bar(a=b))))");

		CSString part;
		part = testLine.strtok(" \t", true, false);
		TEST_ASSERT(part == "a=b");
		part = testLine.strtok(" \t", true, false);
		TEST_ASSERT(part == "c");
		part = testLine.strtok(" \t", true, false);
		TEST_ASSERT(part == "(a=e b=c)");
		part = testLine.strtok(" \t", true, false);
		TEST_ASSERT(part == "c");
		part = testLine.strtok(" \t=", true, false);
		TEST_ASSERT(part == "(a=e b=c)");
		part = testLine.strtok(" \t=", true, false);
		TEST_ASSERT(part == "toto");
		part = testLine.strtok(" \t=", true, false);
		TEST_ASSERT(part == "(bimbo(foo(bar(a=b))))");
		part = part.stripBlockDelimiters();
		CSString part2 = part.strtok(" \t=", true, false);
		TEST_ASSERT(part2 == "bimbo");
		part2 = part.strtok(" \t=", true, false);
		TEST_ASSERT(part2 == "(foo(bar(a=b)))");

	}
};

Test::Suite *createCSStringTS()
{
	return new CSStringTS;
}
