
#include "nel/misc/types_nl.h"
#include "nel/misc/command.h"
#include "dyn_lib_test.h"
#include "singleton_test.h"

NLMISC_COMMAND(aDynLibCommand, "no help", "bla bla bla")
{
	return true;
}

class CDynLibTest : public IDynLibTest
{
public:
	void onLibraryLoaded(bool firstTime)
	{
	}
	void onLibraryUnloaded(bool lastTime)
	{
	}

	virtual void testSingleton(CSafeSingletonTS *testSuite)
	{
		uint count = NL_GET_INSTANCE_COUNTER(CSafeSingleton);
		if (!(NL_GET_INSTANCE_COUNTER(CSafeSingleton) == 1))
		{
			testSuite->assertmentWrapper(::Test::Source(__FILE__, __LINE__, "NL_GET_INSTANCE_COUNTER(CSafeSingleton) == 1"));
			if (!testSuite->continue_after_failureWrapper()) return;
		}

		CSafeSingleton &ss = CSafeSingleton::getInstance();

		count = NL_GET_INSTANCE_COUNTER(CSafeSingleton);
		if (!(NL_GET_INSTANCE_COUNTER(CSafeSingleton) == 1))
		{
			testSuite->assertmentWrapper(::Test::Source(__FILE__, __LINE__, "NL_GET_INSTANCE_COUNTER(CSafeSingleton) == 1"));
			if (!testSuite->continue_after_failureWrapper()) return;
		}

		count = NL_GET_INSTANCE_COUNTER(CUnsafeSingleton);
		if (!(NL_GET_INSTANCE_COUNTER(CUnsafeSingleton) == 1))
		{
			testSuite->assertmentWrapper(::Test::Source(__FILE__, __LINE__, "NL_GET_INSTANCE_COUNTER(CUnsafeSingleton) == 1"));
			if (!testSuite->continue_after_failureWrapper()) return;
		}

		CUnsafeSingleton &us = CUnsafeSingleton::getInstance();

		count = NL_GET_INSTANCE_COUNTER(CUnsafeSingleton);
		if (!(NL_GET_INSTANCE_COUNTER(CUnsafeSingleton) == 2))
		{
			testSuite->assertmentWrapper(::Test::Source(__FILE__, __LINE__, "NL_GET_INSTANCE_COUNTER(CUnsafeSingleton) == 2"));
			if (!testSuite->continue_after_failureWrapper()) return;
		}

	}
};

// Export the pure nel library entry
NLMISC_DECL_PURE_LIB(CDynLibTest);


