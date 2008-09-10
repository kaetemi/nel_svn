
#include "nel/misc/app_context.h"
#include "nel/misc/debug.h"
#include "nel/misc/dynloadlib.h"
#include "nel/misc/command.h"
#include "nel/misc/path.h"

#include <cpptest.h>

#include "dyn_lib_test.h"

using namespace std;
using namespace NLMISC;

class CSafeSingleton
{
	NL_INSTANCE_COUNTER_DECL(CSafeSingleton);
	NLMISC_SAFE_SINGLETON_DECL(CSafeSingleton);
	CSafeSingleton() {}

public:


};

NL_INSTANCE_COUNTER_IMPL(CSafeSingleton);
NLMISC_SAFE_SINGLETON_IMPL(CSafeSingleton);


class CUnsafeSingleton
{
	NL_INSTANCE_COUNTER_DECL(CUnsafeSingleton);

	static CUnsafeSingleton	*_Instance;

	CUnsafeSingleton() {}
	CUnsafeSingleton(const CUnsafeSingleton &other) {}

public:

	static CUnsafeSingleton &getInstance()
	{
		if (_Instance == NULL)
			_Instance = new CUnsafeSingleton;
		return *_Instance;
	}
};

NL_INSTANCE_COUNTER_IMPL(CUnsafeSingleton);
CUnsafeSingleton	*CUnsafeSingleton::_Instance = NULL;


// Test suite for Singleton behavior
class CSafeSingletonTS : public Test::Suite
{
	std::string WorkingPath;
	std::string OldPath;
public:
	CSafeSingletonTS(const std::string &workingPath)
		: WorkingPath(workingPath)
	{
		TEST_ADD(CSafeSingletonTS::createSingleton);
		TEST_ADD(CSafeSingletonTS::accessSingleton);
		TEST_ADD(CSafeSingletonTS::multiDllSingleton);
	}

	void setup()
	{
		OldPath = NLMISC::CPath::getCurrentPath();

		NLMISC::CPath::setCurrentPath(WorkingPath.c_str());
	}

	void tear_down()
	{
		NLMISC::CPath::setCurrentPath(OldPath.c_str());
	}
	
	void createSingleton()
	{
		TEST_ASSERT(CInstanceCounterManager::getInstance().getInstanceCounter("CSafeSingleton") == 0);
		CSafeSingleton &ss = CSafeSingleton::getInstance();
	
		TEST_ASSERT(NL_GET_INSTANCE_COUNTER(CSafeSingleton) == 1);

		TEST_ASSERT(NL_GET_INSTANCE_COUNTER(CUnsafeSingleton) == 0);
		CUnsafeSingleton &us = CUnsafeSingleton::getInstance();
	
		TEST_ASSERT(NL_GET_INSTANCE_COUNTER(CUnsafeSingleton) == 1);
	}

	void accessSingleton()
	{
		TEST_ASSERT(NL_GET_INSTANCE_COUNTER(CSafeSingleton) == 1);
		CSafeSingleton &ss = CSafeSingleton::getInstance();
	
		TEST_ASSERT(NL_GET_INSTANCE_COUNTER(CSafeSingleton) == 1);

		TEST_ASSERT(NL_GET_INSTANCE_COUNTER(CUnsafeSingleton) == 1);
		CUnsafeSingleton &us = CUnsafeSingleton::getInstance();
	
		TEST_ASSERT(NL_GET_INSTANCE_COUNTER(CUnsafeSingleton) == 1);
	}

	void multiDllSingleton()
	{
		TEST_ASSERT(CCommandRegistry::getInstance().exists("aDynLibCommand") == false);

		CLibrary lib;
		if (lib.loadLibrary("dyn_lib_test", true, true, true) != true)
		{
			TEST_ASSERT_MSG(false, "failed to reload the dll for testing singletons across dlls");
			return;
		}

		TEST_ASSERT(CCommandRegistry::getInstance().isCommand("aDynLibCommand") == true);

		IDynLibTest *libTest = dynamic_cast<IDynLibTest*>(lib.getNelLibraryInterface());
		TEST_ASSERT(libTest != NULL);

		libTest->testSingleton(this);
	}

	void assertmentWrapper(Test::Source src)
	{
		assertment(src);
	}

	bool continue_after_failureWrapper()
	{
		return continue_after_failure();
	}

	friend class CDynLibTest;
};



