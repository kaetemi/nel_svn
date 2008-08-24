/** \file singleton.h
 * This class is used to create singleton class following the singleton design pattern
 */

/* Copyright, 2004 Nevrax Ltd.
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

#ifndef NL_SINGLETON_H
#define NL_SINGLETON_H

#include "nel/misc/common.h"
#include "nel/misc/debug.h"
#include "nel/misc/thread.h"
#include "nel/misc/app_context.h"

namespace NLMISC
{

	/**
	 * Example:
	 * \code
		struct CFooSingleton : public CSingleton<CFooSingleton>
		{
			void foo() { nlinfo("foo!"); }
		};

		// call the foo function:
		CFooSingleton::getInstance().foo();

	 * \endcode
	 * \author Vianney Lecroart
	 * \author Nevrax France
	 * \date 2004
	 */

	template<class T>
	class CSingleton
	{
	public:
		virtual ~CSingleton() {}

		/// returns a reference and not a pointer to be sure that the user
		/// doesn't have to test the return value and can directly access the class
		static T &getInstance()
		{
			if(!Instance)
			{
				Instance = new T;
				nlassert(Instance);
			}
			return *Instance;
		}

		/// shorter version of getInstance()
		static T &instance() { return getInstance(); }

		static void releaseInstance()
		{
			if(Instance)
			{
				delete Instance;
				Instance = NULL;
			}
		}

	protected:
		/// no public ctor to be sure that the user can't create an instance
		CSingleton()
		{
		}

		static T *Instance;
	};

	template <class T>
	T* CSingleton<T>::Instance = 0;



	/** A variant of the singleton, not fully compliant with the standard design pattern
	 *	It is more appropriate for object built from a factory but that must
	 *	be instanciate only once.
	 *	The singleton paradigm allow easy access to the unique instance but
	 *	I removed the automatic instanciation of getInstance().
	 *
	 *	Consequently, the getInstance return a pointer that can be NULL
	 *	if the singleton has not been build yet.
	 *
	 * Example:
	 * \code
		struct CFooSingleton : public CManualSingleton<CFooSingleton>
		{
			void foo() { nlinfo("foo!"); }
		};

		// create an instance by any mean
		CFooSingleton	mySingleton

		// call the foo function:
		CFooSingleton::getInstance()->foo();

  		// create another instance is forbiden
		CFooSingleton	otherInstance;		// ASSERT !


	 * \endcode
	 * \author Boris 'sonix' Boucher
	 * \author Nevrax France
	 * \date 2005
	 */

	template <class T>
	class CManualSingleton
	{
		static T *&_instance()
		{
			static T *instance = NULL;

			return instance;
		}

	protected:


		CManualSingleton()
		{
			nlassert(_instance() == NULL);
			_instance() = static_cast<T*>(this);
		}

		~CManualSingleton()
		{
			nlassert(_instance() == this);
			_instance() = NULL;
		}

	public:

		static bool isInitialized()
		{
			return _instance() != NULL;
		}

		static T* getInstance()
		{
			nlassert(_instance() != NULL);

			return _instance();
		}
	};


	/** A macro for safe global variable value.
	 *	Concept : global initialized variable value are inherently unsafe because the order of
	 *	initialisation if undefined. If some init code use static value, you
	 *	may encounter hazardous error, depending on you compiler will, when you
	 *	read the value of a global, you may read it before it is initialized.
	 *	This little class is a workaround that allow a safe global value.
	 *	A drawback is that the value is enclosed inside a function and thus not
	 *	accessible in the debugger.
	 *	use getGlobal_<name>() to retrieve a reference to the value.
	 */
#define NL_MISC_SAFE_GLOBAL(type, name, value)	\
	type &getGlobal_##name() \
	{ \
		static type	theVar = (value); \
		return theVar; \
	} \

#define NL_MISC_SAFE_CLASS_GLOBAL(type, name, value)	\
	static type &getGlobal_##name() \
	{ \
		static type	theVar = (value); \
		return theVar; \
	} \



} // NLMISC

#endif // NL_SINGLETON_H

/* End of singleton.h */
