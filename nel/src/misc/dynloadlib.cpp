//file misc/dynloadlib.cpp
/*
 * <dynloadlib.cpp>
 *
 * $Id: dynloadlib.cpp
 */

/* Copyright, 2000 Nevrax Ltd.
 *
 * This file is part of NEVRAX NEL.
 * NEVRAX NEL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX NEL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NEL; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#include "stdmisc.h"

#include "nel/misc/dynloadlib.h"
#include "nel/misc/path.h"

using namespace std;

namespace NLMISC
{

NL_LIB_HANDLE nlLoadLibrary(const std::string &libName)
{
#if defined NL_OS_WINDOWS
	return LoadLibrary(libName.c_str());
#elif defined (NL_OS_UNIX)
	return dlopen(libName.c_str(), RTLD_NOW);
#else
#error "You must define nlLoadLibrary for your platform"
#endif
}

bool nlFreeLibrary(NL_LIB_HANDLE libHandle)
{
#if defined NL_OS_WINDOWS
	return FreeLibrary(libHandle) > 0;
#elif defined (NL_OS_UNIX)
	return dlclose(libHandle) == 0;
#else
#error "You must define nlFreeLibrary for your platform"
#endif
}

void *nlGetSymbolAddress(NL_LIB_HANDLE libHandle, const std::string &procName)
{
#if defined (NL_OS_WINDOWS)
	return GetProcAddress(libHandle, procName.c_str());
#elif defined (NL_OS_UNIX)
	return dlsym(libHandle, procName.c_str());
#else
#error "You must define nlGetProcAddress for your platform"
#endif
}

// Again some OS specifics stuff
#if defined (NL_OS_WINDOWS)
  const string	NL_LIB_PREFIX;	// empty
  const string	NL_LIB_EXT(".dll");
#elif defined (NL_OS_UNIX)
  const string	NL_LIB_PREFIX("lib");
  const string	NL_LIB_EXT(".so");
#else
#error "You must define the default dynamic lib extention"
#endif

// Compilation mode specific suffixes
#if defined (NL_OS_WINDOWS)
 #ifdef NL_DEBUG_INSTRUMENT
  const string	NL_LIB_SUFFIX("_di");
 #elif defined (NL_DEBUG_FAST)
   const string	NL_LIB_SUFFIX("_df");
 #elif defined (NL_DEBUG)
   const string	NL_LIB_SUFFIX("_d");
 #elif defined (NL_RELEASE_DEBUG)
   const string	NL_LIB_SUFFIX("_rd");
 #elif defined (NL_RELEASE)
   const string	NL_LIB_SUFFIX("_r");
 #else
   #error "Unknown compilation mode, can't build suffix"
 #endif
#elif defined (NL_OS_UNIX)
   const string	NL_LIB_SUFFIX;	// empty
#else
 #error "Lib suffix not defined for your platform"
#endif

std::vector<std::string>	CLibrary::_LibPaths;


CLibrary::CLibrary (const CLibrary &other)
{
	// Nothing to do has it is forbidden.
	// Allowing copy require to manage reference count from CLibrary to the module resource.
	nlassert(false);
}

CLibrary &CLibrary::operator =(const CLibrary &other)
{
	// Nothing to do has it is forbidden.
	// Allowing assignment require to manage reference count from CLibrary to the module resource.
	nlassert(false);
	return *this;
}



std::string CLibrary::makeLibName(const std::string &baseName)
{
	return NL_LIB_PREFIX+baseName+NL_LIB_SUFFIX+NL_LIB_EXT;
}

std::string CLibrary::cleanLibName(const std::string &decoratedName)
{
	// remove path and extension
	string ret = CFile::getFilenameWithoutExtension(decoratedName);

	if (!NL_LIB_PREFIX.empty())
	{
		// remove prefix
		if (ret.find(NL_LIB_PREFIX) == 0)
			ret = ret.substr(NL_LIB_PREFIX.size());
	}
	if (!NL_LIB_SUFFIX.empty())
	{
		// remove suffix
		if (ret.substr(ret.size()-NL_LIB_SUFFIX.size()) == NL_LIB_SUFFIX)
			ret = ret.substr(0, ret.size() - NL_LIB_SUFFIX.size());
	}

	return ret;
}

void CLibrary::addLibPaths(const std::vector<std::string> &paths)
{
	for (uint i=0; i<paths.size(); ++i)
	{
		string newPath = CPath::standardizePath(paths[i]);

		// only add new path
		if (std::find(_LibPaths.begin(), _LibPaths.end(), newPath) == _LibPaths.end())
		{
			_LibPaths.push_back(newPath);
		}
	}
}

void CLibrary::addLibPath(const std::string &path)
{
	string newPath = CPath::standardizePath(path);

	// only add new path
	if (std::find(_LibPaths.begin(), _LibPaths.end(), newPath) == _LibPaths.end())
	{
		_LibPaths.push_back(newPath);
	}
}
	
CLibrary::CLibrary()
:	_LibHandle(NULL),
	_Ownership(true),
	_PureNelLibrary(NULL)
{
}

CLibrary::CLibrary(NL_LIB_HANDLE libHandle, bool ownership)
: _PureNelLibrary(NULL)
{
	_LibHandle = libHandle;
	_Ownership = ownership;
	_LibFileName = "unknown";
}

CLibrary::CLibrary(const std::string &libName, bool addNelDecoration, bool tryLibPath, bool ownership)
: _PureNelLibrary(NULL)
{
	loadLibrary(libName, addNelDecoration, tryLibPath, ownership);
	// Assert here !
	nlassert(_LibHandle != NULL);
}


CLibrary::~CLibrary()
{
	if (_LibHandle != NULL && _Ownership)
	{
		nlFreeLibrary(_LibHandle);
	}
}

bool CLibrary::loadLibrary(const std::string &libName, bool addNelDecoration, bool tryLibPath, bool ownership)
{
	_Ownership = ownership;
	string libPath = libName;

	if (addNelDecoration)
		libPath = makeLibName(libPath);

	if (tryLibPath)
	{
		// remove any directory spec
		string filename = CFile::getFilename(libPath);

		for (uint i=0; i<_LibPaths.size(); ++i)
		{
			string pathname = _LibPaths[i]+filename;
			if (CFile::isExists(pathname))
			{
				// we found it, replace libPath
				libPath = pathname;
				break;
			}
		}
	}

	nldebug("Loading dynamic library '%s'", libPath.c_str());
	// load the lib now
	_LibHandle = nlLoadLibrary(libPath);
	_LibFileName = libPath;
	// MTR: some new error handling. Just logs if it couldn't load the handle.
	if(_LibHandle == NULL) {
#ifdef NL_OS_UNIX
		char *errormsg=dlerror();
#else
		const char *errormsg="Verify DLL existence.";
#endif
		nlwarning("Loading library %s failed: %s", libPath.c_str(), errormsg);
	}
	else
	{
		// check for 'pure' nel library
		void *entryPoint = getSymbolAddress(NL_MACRO_TO_STR(NLMISC_PURE_LIB_ENTRY_POINT));
		if (entryPoint != NULL)
		{
			// rebuild the interface pointer
			_PureNelLibrary = *(reinterpret_cast<INelLibrary**>(entryPoint));
			// call the private initialisation method.
			_PureNelLibrary->_onLibraryLoaded(INelContext::getInstance());
		}
	}

	return _LibHandle != NULL;
}

void CLibrary::freeLibrary()
{
	if (_LibHandle)
	{
		nlassert(_Ownership);

		if (_PureNelLibrary)
		{
			// call the private finalisation method.
			_PureNelLibrary->_onLibraryUnloaded();
		}

		nldebug("Freeing dynamic library '%s'", _LibFileName.c_str());
		nlFreeLibrary(_LibHandle);

		_PureNelLibrary = NULL;
		_LibHandle = NULL;
		_Ownership = false;
		_LibFileName = "";
	}
}

void *CLibrary::getSymbolAddress(const std::string &symbolName)
{
	nlassert(_LibHandle != NULL);

	return nlGetSymbolAddress(_LibHandle, symbolName);
}

bool CLibrary::isLibraryLoaded()
{
	return _LibHandle != NULL;
}

bool CLibrary::isLibraryPure()
{
	return _LibHandle != NULL && _PureNelLibrary != NULL;
}

INelLibrary *CLibrary::getNelLibraryInterface()
{
	if (!isLibraryPure())
		return NULL;

	return _PureNelLibrary;
}


INelLibrary::~INelLibrary()
{
	// cleanup ram
	if (_LibContext != NULL)
		delete _LibContext;
}


void INelLibrary::_onLibraryLoaded(INelContext &nelContext)
{
	++_LoadingCounter;

	if (_LoadingCounter == 1)
	{
		// Linux relocates all symbols, so this is unnecessary.
#ifdef NL_OS_WINDOWS
		// initialise Nel context
		nlassert(!NLMISC::INelContext::isContextInitialised());
#endif // NL_OS_WINDOWS

		_LibContext = new CLibraryContext(nelContext);
	}
	else
	{
		nlassert(NLMISC::INelContext::isContextInitialised());
	}

	onLibraryLoaded(_LoadingCounter==1);
}

void INelLibrary::_onLibraryUnloaded()
{
	nlassert(_LoadingCounter > 0);
	
	onLibraryUnloaded(_LoadingCounter == 1);

	--_LoadingCounter;
}

uint32	INelLibrary::getLoadingCounter()
{
	return _LoadingCounter;
}



}	// namespace NLMISC
