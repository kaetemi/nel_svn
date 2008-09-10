
#include "nel/misc/mutex.h"
#include "nel/net/service.h"
#include "nel/net/module_manager.h"
#include "nel/net/module.h"
#include "nel/net/module_builder_parts.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

// This library intentionally has it's own CApplicationContext, 
// because you can only have one IService instance in one application.

bool	stopServiceRq = false;

IThread	*serviceThread = NULL; 

NLMISC::CMutex	mutex;

list<string>	commands;


class CTestService : public IService
{
public:

	virtual void			init ()
	{
	}

	virtual bool			update () 
	{
//		nldebug("Service '%s' update", getServiceLongName().c_str());
		// process commands
		mutex.enter();

		// run 1 command at a time
		if (!commands.empty())
		{
			CCommandRegistry::getInstance().execute(commands.front(), *DebugLog);
			commands.pop_front();
		}
		mutex.leave();


		return !stopServiceRq;
	}

	/// Finalization. Release the service. For example, this function frees all allocations made in the init() function.
	virtual void			release () 
	{
	}

};

class CServiceRunnable : public IRunnable
{
	std::string _ServiceName;
	std::string _ServiceShortName;
	uint16		_ListenPort;
public:

	CServiceRunnable (const std::string &serviceName, const std::string &serviceShortName, uint16 listenPort)
		: _ServiceName(serviceName),
		_ServiceShortName(serviceShortName),
		_ListenPort(listenPort)
	{

	}

	virtual void run()
	{
_CrtCheckMemory();
		// do the job
		createDebug();
		CTestService *scn = new CTestService;
		scn->setArgs (0, NULL);
//		scn->setCallbackArray (__ServiceCallbackArray, sizeof(__ServiceCallbackArray)/sizeof(__ServiceCallbackArray[0])); 
_CrtCheckMemory();
		sint retval = scn->main (	_ServiceShortName.c_str(), 
									_ServiceName.c_str(), 
									_ListenPort, 
									"", 
									"", 
									__DATE__" "__TIME__);
_CrtCheckMemory();
		delete scn;
_CrtCheckMemory();
	}
};


void startServiceImp(const char *serviceName, const char *serviceShortName, uint16 listenPort)
{
	serviceThread = IThread::create(new CServiceRunnable(serviceName, serviceShortName, listenPort));
	serviceThread->start();
}

void runCommandImp(const char *commandString)
{
	if (serviceThread == NULL)
		return;
	
	mutex.enter();
	commands.push_back(commandString);
	mutex.leave();

	for (;;)
	{
		nlSleep(0);
		mutex.enter();
		if (commands.empty() 
			|| !serviceThread->isRunning())
			break;
		mutex.leave();
	}
	mutex.leave();
}

void stopServiceImp()
{
//_CrtMemDumpAllObjectsSince(NULL);

	stopServiceRq = true;


	serviceThread->wait();

//	delete serviceThread->getRunnable();

	delete serviceThread;
	serviceThread = NULL;
}

typedef void (TStartFunc)(const char *serviceName, const char *serviceShortName, uint16 listenPort); 
typedef void (TCommandFunc)(const char *commandString); 
typedef void (TStopFunc)(); 

NL_LIB_EXPORT_SYMBOL(startService, TStartFunc, startServiceImp);
NL_LIB_EXPORT_SYMBOL(runCommand, TCommandFunc, runCommandImp);
NL_LIB_EXPORT_SYMBOL(stopService, TStopFunc, stopServiceImp);


