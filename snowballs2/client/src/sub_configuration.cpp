/** \file sub_configuration.h * 
 * CSubConfiguration
 */

#include <nel/misc/types_nl.h>
#include "sub_configuration.h"

using namespace std;
using namespace NLMISC;

namespace SBCLIENT {

void CSubConfiguration::setConfigFile(const std::string &configFile, const std::string &configPrefix)
{
	setConfigFile();
	_ConfigPrefix = configPrefix;
	_ConfigPrefixD = configPrefix + "_";
	ConfigFile = new CConfigFile();
	_ConfigFileCreated = true;
	ConfigFile->load(configFile);
	tryConfigFile();
}

void CSubConfiguration::setConfigFile(NLMISC::CConfigFile *configFile, const std::string &configPrefix)
{
	setConfigFile();
	_ConfigPrefix = configPrefix;
	_ConfigPrefixD = configPrefix + "_";
	ConfigFile = configFile;
	tryConfigFile();
}

void CSubConfiguration::tryConfigFile()
{
	if (exists("ConfigFile"))
	{
		std::string configFile = getVar("ConfigFile").asString();
		std::string configPrefix = _ConfigPrefix;
		setConfigFile(configFile, configPrefix);
	}
}

void CSubConfiguration::setConfigFile()
{
	if (_ConfigFileCreated)
	{
		if (ConfigFile->exists("SaveConfig") && ConfigFile->getVar("SaveConfig").asBool())
			ConfigFile->save();
		_ConfigFileCreated = false;
		delete ConfigFile;
	}
}

float CSubConfiguration::getValue(const string &varName, float defaultValue)
{
	if (exists(varName)) return getVar(varName).asFloat();
	CConfigFile::CVar varToCopy;
	varToCopy.forceAsDouble((double)defaultValue);	
	ConfigFile->insertVar(_ConfigPrefixD + varName, varToCopy);
	return defaultValue;
}

double CSubConfiguration::getValue(const string &varName, double defaultValue)
{
	if (exists(varName)) return getVar(varName).asDouble();
	CConfigFile::CVar varToCopy;
	varToCopy.forceAsDouble(defaultValue);	
	ConfigFile->insertVar(_ConfigPrefixD + varName, varToCopy);
	return defaultValue;
}

int CSubConfiguration::getValue(const string &varName, int defaultValue)
{
	if (exists(varName)) return getVar(varName).asInt();
	CConfigFile::CVar varToCopy;
	varToCopy.forceAsInt(defaultValue);	
	ConfigFile->insertVar(_ConfigPrefixD + varName, varToCopy);
	return defaultValue;
}

std::string CSubConfiguration::getValue(const string &varName, const string &defaultValue)
{
	if (exists(varName)) return getVar(varName).asString();
	CConfigFile::CVar varToCopy;
	varToCopy.forceAsString(defaultValue);
	ConfigFile->insertVar(_ConfigPrefixD + varName, varToCopy);
	return defaultValue;
}

bool CSubConfiguration::getValue(const string &varName, bool defaultValue)
{
	if (exists(varName)) return getVar(varName).asBool();
	CConfigFile::CVar varToCopy;
	varToCopy.forceAsInt(defaultValue ? 1 : 0);	
	ConfigFile->insertVar(_ConfigPrefixD + varName, varToCopy);
	return defaultValue;
}

CConfigFile::CVar &CSubConfiguration::getVar(const std::string &varName)
{
	return ConfigFile->getVar(_ConfigPrefixD + varName);
}

bool CSubConfiguration::exists(const std::string &varName)
{
	return ConfigFile->exists(_ConfigPrefixD + varName);
}

void CSubConfiguration::setCallback(const std::string &varName, void (*cb)(CConfigFile::CVar &, void *, void *), void *context, void *state)
{
	std::string fullName = _ConfigPrefixD + varName;
	if (cb == NULL)
	{
		std::map<std::string, CConfigCallback>::iterator
			it = _CVarStates.find(fullName);
		if (it != _CVarStates.end()) _CVarStates.erase(it);
		ConfigFile->setCallback(fullName, NULL);
	}
	else
	{
		_CVarStates[fullName] = CConfigCallback(cb, context, state);
		ConfigFile->setCallback(fullName, callback);
	}
}

void CSubConfiguration::setCallback(const string &varName, void (*cb)(CConfigFile::CVar &))
{
	ConfigFile->setCallback(_ConfigPrefixD + varName, cb);
}

std::map<std::string, CSubConfiguration::CConfigCallback> CSubConfiguration::_CVarStates;

void CSubConfiguration::callback(CConfigFile::CVar &var)
{
	_CVarStates[var.Name].Callback(var, _CVarStates[var.Name].Context, _CVarStates[var.Name].State);
}

CSubConfiguration::CSubConfiguration() : _ConfigFileCreated(false)
{

}

CSubConfiguration::~CSubConfiguration()
{
	setConfigFile();
}

}

