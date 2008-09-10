
#include "nel/misc/types_nl.h"
#include "nel/misc/debug.h"
#include "nel/misc/dynloadlib.h"
#include "nel/net/sock.h"
#include "nel/net/module_manager.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "cpptest.h"

#include "nel/misc/path.h"

using namespace std;

class CNetUnitTestNelLibrary : public NLMISC::INelLibrary { 
	void onLibraryLoaded(bool firstTime) { } 
	void onLibraryUnloaded(bool lastTime) { }  
};
NLMISC_DECL_PURE_LIB(CNetUnitTestNelLibrary);

Test::Suite *createModuleTS(const std::string &workingPath);
Test::Suite *createCMessageTS();
Test::Suite *createServiceAndModuleTS(const std::string &workingPath);
Test::Suite *createLayer3TS(const std::string &workingPath);

// global test for any misc feature
class CNetTS : public Test::Suite
{
public:
	CNetTS(const std::string &workingPath)
	{
		// init the network API
		NLNET::CSock::initNetwork();

		add(auto_ptr<Test::Suite>(createCMessageTS()));
		add(auto_ptr<Test::Suite>(createModuleTS(workingPath)));
		add(auto_ptr<Test::Suite>(createServiceAndModuleTS(workingPath)));
		add(auto_ptr<Test::Suite>(createLayer3TS(workingPath)));
		
		// initialise the application context
		NLMISC::CApplicationContext::getInstance();
		NLNET::IModuleManager::getInstance();

		NLMISC::createDebug();
	}

	~CNetTS()
	{
		// close the network API
		NLNET::CSock::releaseNetwork();
	}
	
private:
};


auto_ptr<Test::Suite> intRegisterTestSuite(const std::string &workingPath)
{
	return auto_ptr<Test::Suite>(static_cast<Test::Suite*>(new CNetTS(workingPath)));
}

NL_LIB_EXPORT_SYMBOL(registerTestSuite, void, intRegisterTestSuite);
