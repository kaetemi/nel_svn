
#include "nel/misc/common.h"
#include "nel/misc/path.h"
#include "nel/misc/dynloadlib.h"
#include "nel/misc/debug.h"
#include "nel/misc/command.h"

#include "nel/net/module_manager.h"
#include "nel/net/module.h"
#include "nel/net/module_gateway.h"


#include "cpptest.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

typedef void (TStartFunc)(const char *serviceName, const char *serviceShortName, uint16 listenPort); 
typedef void (TCommandFunc)(const char *commandString); 
typedef void (TStopFunc)(); 

const uint32	NB_SERVICES = 3;

// Test suite for stream based classes
// ! not complete at all at time of writing !
class CServiceAndModuleTS: public Test::Suite
{
	string	_WorkingPath;
	string	_RestorePath;

	IModuleProxy *retrieveModuleProxy(IModuleGateway *gw, const std::string &modName)
	{
		vector<IModuleProxy*> proxList;
		gw->getModuleProxyList(proxList);

		for (uint i=0; i<proxList.size(); ++i)
		{
			if (proxList[i]->getModuleName().find(modName) == (proxList[i]->getModuleName().size() - modName.size()))
				return proxList[i];
		}

		return NULL;
	}

	CLibrary	ServiceLib[NB_SERVICES];

	TCommandFunc *cmdFuncs[NB_SERVICES];

public:
	CServiceAndModuleTS (const std::string &workingPath)
		: _WorkingPath(workingPath)
	{
		TEST_ADD(CServiceAndModuleTS::createL5Transport);
//		TEST_ADD(CServiceAndModuleTS::sendMessage);

	}

	void sendMessage()
	{
		IModuleManager &mm = IModuleManager::getInstance();
		CCommandRegistry &cr = CCommandRegistry::getInstance();

		IModule *mod = mm.createModule("StandardGateway", "gw", "");
		cr.execute("gw.plug gw", InfoLog());
		cr.execute("gw.transportAdd L3Server l3s", InfoLog());
		cr.execute("gw.transportCmd l3s(open port=8060)", InfoLog());

		// create a gateway in each service
		cmdFuncs[0]("moduleManager.createModule StandardGateway gw1");
		cmdFuncs[1]("moduleManager.createModule StandardGateway gw2");
		cmdFuncs[2]("moduleManager.createModule StandardGateway gw3");

		// plug gateway in themselves
		cmdFuncs[0]("gw1.plug gw1");
		cmdFuncs[1]("gw2.plug gw2");
		cmdFuncs[2]("gw3.plug gw3");

		// create L5 transports
		cmdFuncs[0]("gw1.transportAdd L5Transport l5");
		cmdFuncs[0]("gw1.transportAdd L3Client l3c");
		cmdFuncs[1]("gw2.transportAdd L5Transport l5");
		cmdFuncs[2]("gw3.transportAdd L5Transport l5");

		// open the transports
		cmdFuncs[0]("gw1.transportCmd l5(open)");
		cmdFuncs[0]("gw1.transportCmd l3c(connect addr=localhost:8060)");
		cmdFuncs[1]("gw2.transportCmd l5(open)");
		cmdFuncs[2]("gw3.transportCmd l5(open)");

		// let some time for the commands to execute
		nlSleep(2000);

		// update the network
		for (uint i=0; i<10; ++i)
		{
			mm.updateModules();
			nlSleep(40);
		}

		// send a ping from each service gateway to the test gateway
		string fullName = mod->getModuleFullyQualifiedName();
		cmdFuncs[0](toString("gw1.sendPing %s", fullName.c_str()).c_str());
		cmdFuncs[1](toString("gw2.sendPing %s", fullName.c_str()).c_str());
		cmdFuncs[2](toString("gw3.sendPing %s", fullName.c_str()).c_str());

		// update the network
		for (uint i=0; i<10; ++i)
		{
			mm.updateModules();
			nlSleep(40);
		}

		// check the ping counter
		IModuleGateway *gGw;
		gGw = dynamic_cast<IModuleGateway *>(mod);
		TEST_ASSERT(gGw != NULL);

		TEST_ASSERT(gGw->getReceivedPingCount() == 3);

		// cleanup
		mm.deleteModule(mod);
	}

	void createL5Transport()
	{
		IModuleManager &mm = IModuleManager::getInstance();
		CCommandRegistry &cr = CCommandRegistry::getInstance();

		IModule *mod = mm.createModule("StandardGateway", "gw", "");
		TEST_ASSERT(mod != NULL);
		cr.execute("gw.plug gw", InfoLog());
		cr.execute("gw.transportAdd L3Server l3s", InfoLog());
		cr.execute("gw.transportCmd l3s(open port=8060)", InfoLog());

		// create a gateway in each service
		cmdFuncs[0]("moduleManager.createModule StandardGateway gw1");
		cmdFuncs[1]("moduleManager.createModule StandardGateway gw2");
		cmdFuncs[2]("moduleManager.createModule StandardGateway gw3");

		// plug gateway in themselves
		cmdFuncs[0]("gw1.plug gw1");
		cmdFuncs[1]("gw2.plug gw2");
		cmdFuncs[2]("gw3.plug gw3");

		// create L5 transports
		cmdFuncs[0]("gw1.transportAdd L5Transport l5");
		cmdFuncs[0]("gw1.transportAdd L3Client l3c");
		cmdFuncs[1]("gw2.transportAdd L5Transport l5");
		cmdFuncs[2]("gw3.transportAdd L5Transport l5");

		// open the transports
		cmdFuncs[0]("gw1.transportCmd l5(open)");
		cmdFuncs[0]("gw1.transportCmd l3c(connect addr=localhost:8060)");
		cmdFuncs[1]("gw2.transportCmd l5(open)");
		cmdFuncs[2]("gw3.transportCmd l5(open)");

		// let some time for the commands to execute
		nlSleep(2000);

		// update the network
		for (uint i=0; i<10; ++i)
		{
			mm.updateModules();
			nlSleep(40);
		}

		cmdFuncs[0]("gw1.dump");
		nlSleep(10);
		cmdFuncs[1]("gw2.dump");
		nlSleep(10);
		cmdFuncs[2]("gw3.dump");
		nlSleep(10);

		// ok, check the list of available module
		IModuleGateway *gGw;
		gGw = dynamic_cast<IModuleGateway *>(mod);
		TEST_ASSERT(gGw != NULL);

		vector<IModuleProxy*> proxList;
		gGw->getModuleProxyList(proxList);

		IModuleProxy *gw1Prox, *gw2Prox, *gw3Prox; 
		gw1Prox = retrieveModuleProxy(gGw, "gw1");
		TEST_ASSERT(gw1Prox != NULL);
		TEST_ASSERT(gw1Prox->getModuleDistance() == 1);

		gw2Prox = retrieveModuleProxy(gGw, "gw2");
		TEST_ASSERT(gw2Prox != NULL);
		TEST_ASSERT(gw2Prox->getModuleDistance() == 2);

		gw3Prox = retrieveModuleProxy(gGw, "gw3");
		TEST_ASSERT(gw3Prox != NULL);
		TEST_ASSERT(gw3Prox->getModuleDistance() == 2);


		// cleanup
		mm.deleteModule(mod);
	}
	
	
	void setup()
	{
//_CrtCheckMemory();
		_RestorePath = CPath::getCurrentPath();

		nlverify(CPath::setCurrentPath(_WorkingPath.c_str()));

		string debugPath = CPath::getCurrentPath();

		// copy the service dll and config file to
		// have completely different memory context

//_CrtCheckMemory();
		for (uint i=0; i<NB_SERVICES; ++i)
		{
			string libName = CLibrary::makeLibName("net_service_lib_test");

			// copy the dll file
			string srcDll = string("net_service_lib_test/")+libName;
			string destDll = toString("%s_%u", libName.c_str(), i+1);

			nlverify(CFile::copyFile(destDll.c_str(), srcDll.c_str(), false));

			// copy the config file
			string srcCfg = "net_service_lib_test/net_service_lib_test.cfg";
			string destCfg = toString("test_service_%u.cfg", i+1);

			nlverify(CFile::copyFile(destCfg.c_str(), srcCfg.c_str(), false));

			// load the library file
			ServiceLib[i].loadLibrary(destDll, false, false, true);
		}
//_CrtCheckMemory();

		// Start the services
		for (uint i=0; i<NB_SERVICES; ++i)
		{
			TStartFunc *startFunc = *(TStartFunc**)(ServiceLib[i].getSymbolAddress("startService"));

			startFunc(	toString("test_service_%u", i+1).c_str(), 
						toString("TSTS%u", i+1).c_str(),
						8060+i+1);
		}

		// leave some time for services to start
//		nlSleep(2000);
//_CrtCheckMemory();

		// add the service in layer 5
		cmdFuncs[0] = *(TCommandFunc**)ServiceLib[0].getSymbolAddress("runCommand");
		cmdFuncs[0]("unifiedNetwork.addService test_service_2 (address=localhost:8062 external sendId)");
		cmdFuncs[0]("unifiedNetwork.addService test_service_3 (address=localhost:8063 external sendId)");

		cmdFuncs[1]= *(TCommandFunc**)ServiceLib[1].getSymbolAddress("runCommand");
		cmdFuncs[1]("unifiedNetwork.addService test_service_1 (address=localhost:8061 external sendId)");
		cmdFuncs[1]("unifiedNetwork.addService test_service_3 (address=localhost:8063 external sendId)");

		cmdFuncs[2]= *(TCommandFunc**)ServiceLib[2].getSymbolAddress("runCommand");
		cmdFuncs[2]("unifiedNetwork.addService test_service_1 (address=localhost:8061 external sendId)");
		cmdFuncs[2]("unifiedNetwork.addService test_service_2 (address=localhost:8062 external sendId)");
//_CrtCheckMemory();

		// leave some time to establish connections
//		nlSleep(5000);
	}

	void tear_down()
	{
		nlSleep(5000);
		for (uint i=0; i<NB_SERVICES; ++i)
		{
//_CrtCheckMemory();
			TStopFunc *stopFunc = *(TStopFunc**)ServiceLib[i].getSymbolAddress("stopService");

//_CrtCheckMemory();
			stopFunc();
//_CrtCheckMemory();
		}
		for (uint i=0; i<NB_SERVICES; ++i)
		{
//_CrtCheckMemory();
			ServiceLib[i].freeLibrary();
//_CrtCheckMemory();
		}

		CPath::setCurrentPath(_RestorePath.c_str() );

	}
};

Test::Suite *createServiceAndModuleTS(const std::string &workingPath)
{
	return new CServiceAndModuleTS(workingPath);
}

