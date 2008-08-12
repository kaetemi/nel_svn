
#include "nel/net/module_manager.h"
#include "nel/net/module.h"
#include "nel/net/module_builder_parts.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

NLMISC_DECL_PURE_LIB(CNelModuleLibrary);


class CModuleType1 : public CModuleBase
{
public:

	CModuleType1()
	{
	}

	std::string			buildModuleManifest() const
	{
		return string();
	}

	void				onServiceUp(const std::string &serviceName, NLNET::TServiceId serviceId)
	{
	}
	/// A nel layer 5 service has stopped.
	void				onServiceDown(const std::string &serviceName, NLNET::TServiceId serviceId) 
	{
	}
	void				onModuleUpdate()
	{
	}
	/** The service main loop is terminating it job', all module while be
	 *	disconnected and removed after this callback.
	 */
	void				onApplicationExit() 
	{
	}

	void				onModuleUp(IModuleProxy *moduleProxy)
	{
	}
	/** Called by a socket to inform this module that another
	 *	module has been deleted OR has been no more accessible (due to
	 *	some gateway disconnection).
	 */
	virtual void	onModuleDown(IModuleProxy *moduleProxy)
	{
	}

	virtual bool	onProcessModuleMessage(IModuleProxy *senderModuleProxy, const CMessage &message)
	{
		return false;
	}

	virtual void	onModuleSecurityChange(IModuleProxy *moduleProxy)
	{
	}

	virtual void	onModuleSocketEvent(IModuleSocket *moduleSocket, TModuleSocketEvent eventType) 
	{
	}

};

NLNET_REGISTER_MODULE_FACTORY(CModuleType1, "ModuleType1");


class CModuleType2 : public CEmptyModuleServiceBehav<CEmptyModuleCommBehav<CEmptySocketBehav<CModuleBase> > >
{
};

NLNET_REGISTER_MODULE_FACTORY(CModuleType2, "ModuleType2");
