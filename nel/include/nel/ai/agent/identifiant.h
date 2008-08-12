/** \file identifiant.h
 * Sevral class for identification an objects fonctionality.
 *
 * $Id: identifiant.h,v 1.10 2006/07/12 14:37:21 boucher Exp $
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


#ifndef NL_IDENTIFIANT_H
#define NL_IDENTIFIANT_H
#include <stdlib.h>
#include "nel/ai/e/ia_exception.h" 
#include "nel/ai/agent/agent_string.h"

namespace NLAIAGENT
{	
	class IRefrence;

	

#ifndef _MAX__INDEX_DEFINED
		const sint32 maxIndex = 2;
		#define _MAX__INDEX_DEFINED
#else
		extern const sint32 maxIndex;
#endif

	/**	
	  This class is a basic hi nomber manipulation. An index variant is an maxIndex*64 bit number.
	
	  The resolution of the number is define by the template argument indexMax. By default the number is initialed with a 128 bits resolution.
	  * \author Chafik sameh
	  * \author Robert Gabriel
	  * \author Nevrax France
	  * \date 2000
	*/
	template<sint32 indexMax = maxIndex>
	class CIndexVariant
	{		
	private:
		///_Id is a table were is store the number.
		uint64 _Id[indexMax];
	private:

		/**
		This fonction increment the _Id number by one. It's call from the ++ operator.
		\param n The first index to increment.
		*/		

		void inc(int n)/// throw (NLAIE::CExceptionIndexError)
		{
			if (n == getMaxIndex())
			{
				// The highest Number as been reach.
				throw NLAIE::CExceptionIndexError();
			}

			if (_Id[n] == (uint64)-1)
			{
				// If an index is max, we increment the next index.
				inc(n+1);
				_Id[n] = 0;
			}
			else _Id[n]++;
		}
	public:		


		///Copy contructor
		CIndexVariant(const CIndexVariant &a)
		{
			memcpy(_Id,a._Id,getMaxIndex()*sizeof(uint64));
		}

		///fill with a table.
		CIndexVariant(const uint64 *id)
		{
			for(sint32 i = 0; i < getMaxIndex(); i ++) 
			{
				_Id[i] = id[i];
			}
		}

		///fill a number
		CIndexVariant(uint64 n)
		{
			for(sint32 i = 0; i < getMaxIndex(); i ++) 
			{
				_Id[i] = n;
			}
		}


		///fill from read stream.
		CIndexVariant(NLMISC::IStream &is)
		{
			load(is);
		}

		///increment the number.
		const CIndexVariant &operator ++(int)/// throw (NLAIE::CExceptionIndexError)
		{
			try
			{
				inc(0);
			}
			catch(NLAIE::IException &e)
			{
				throw e;
			}
			return *this;
		}

		///\name comparison of two CIndexVariant.
		//@{
		bool operator == (const CIndexVariant &a) const
		{
			if(getMaxIndex() != a.getMaxIndex()) return false;
			for(sint32 i = 0; i < getMaxIndex(); i ++)
			{
				if(_Id[i] != a._Id[i]) return false;
			}
			
			return true;
		}


		bool operator < (const CIndexVariant &a) const
		{
			if(getMaxIndex() <= a.getMaxIndex())
			{
				for(sint32 i = getMaxIndex()-1; i >= 0; i --)
				{
					if(_Id[i] < a._Id[i]) return true;
				}
			}
			else
			{
				for(sint32 i = a.getMaxIndex()-1; i >= 0; i --)
				{
					if(_Id[i] < a._Id[i]) return true;
				}			

			}
			return false;
		}

		bool operator > (const CIndexVariant &a) const
		{
			if(getMaxIndex() <= a.getMaxIndex())
			{
				for(sint32 i = getMaxIndex()-1; i >= 0; i --)
				{
					if(_Id[i] > a._Id[i]) return true;
				}
			}
			else
			{
				for(sint32 i = a.getMaxIndex()-1; i >= 0; i --)
				{
					if(_Id[i] > a._Id[i]) return true;
				}
			}
			return false;
		}
		//@}


		
		///saving the nomber in an output stream.
		void save(NLMISC::IStream &os)
		{			
			sint32 i;
			i = getMaxIndex();
			os.serial(i);
			for(i = 0; i < getMaxIndex(); i ++)
			{
				uint64 n = _Id[i];				
				os.serial(n);				
			}
		}

		///loading the nomber from an input stream.
		void load(NLMISC::IStream &is)
		{
			sint32 max,i;

			is.serial(max);
			/*if(max != getMaxIndex()) 
			{
				throw(NLAIE::CExceptionIndexError());
			}*/

			for(i = 0; i < getMaxIndex(); i ++)
			{		
				uint64 num;
				is.serial(num);
				_Id[i] = num;
			}

		}
		///Have a debug string.
		void getDebugString(char *str) const 
		{			
			char num[200];

			strcpy(str,"id:[");

			sint32 i;
			
			for(i = 0; i < getMaxIndex() - 1; i ++)
			{
				//_itoa(_Id[i],num,10);
				sprintf(num,"%d",_Id[i]);
				strcat(str,num);
				strcat(str,",");

			}
			sprintf(num,"%d",_Id[i]);
			strcat(str,num);
			strcat(str,"]");
		}
		

		sint32 getMaxIndex() const
		{
			return indexMax;
		}
	};

	/**
	Generator of unique ident for objects.
	
	* \author Chafik sameh
	* \author Nevrax France
	* \date 2000
	*/
	class CNumericIndex
	{
	public:		
		///_I is a static IndexVariant were he have 0 at the initial time.
		static CIndexVariant<maxIndex> _I;
	private:
		CIndexVariant<maxIndex> _Id;
	public:
		///The constructor creat a new number by increment the _I numbre.
		CNumericIndex():_Id (CIndexVariant<maxIndex>(_I++))
		{
		}

		///copy constructor.
		CNumericIndex(const CIndexVariant<maxIndex> &i):_Id (i)
		{
		}

		///construct from a stream.
		CNumericIndex(NLMISC::IStream &is): _Id(is)
		{
		}

		///\name comparison of two CIndexVariant.
		//@{
		bool operator == (const CNumericIndex &a) const
		{
			return _Id == a._Id;
		}

		bool operator < (const CNumericIndex &a) const
		{
			return _Id < a._Id;
		}
	
		bool operator > (const CNumericIndex &a) const
		{
			return _Id > a._Id;
		}
		//@}

		///saving the nomber in an output stream.
		void save(NLMISC::IStream &os)
		{
			_Id.save(os);
		}

		///loading the nomber from an input stream.
		void load(NLMISC::IStream &is)
		{
			_Id.load(is);
		}
		
		void getDebugString(char *str) const
		{
			_Id.getDebugString(str);
		}

	};

	/**
		This class is the ident use in the Agent implementation. Not that an agent have IRefrence class as our base class and this class encapsulat an 		This class is the ident use in the Agent implementation. Not that an agent have IRefrence class as our base class and 
		this class encapsulat an IWordNumRef as an ident reference. So an agent have a pointer to an unique id same as IWordNumRef and the IWordNumRef class have a pointer to its own agent.

		This implementation allow us to share the creation of agent in an map whos is contane all agent created. This technic make simple the save, 
		load or serial procedure, because we have a method to save the pointer reference between agent.

		* \author Chafik sameh
		* \author Nevrax France
		* \date 2000
	*/
	class IWordNumRef: public NLAIC::IBasicInterface
	{
	public:
		IWordNumRef()
		{
		}

		IWordNumRef(IWordNumRef &)
		{
		}
		
		virtual operator const IRefrence *() const = 0;

		virtual ~IWordNumRef()
		{
		}

	};	

	/**
		This is an local version of the IWordNumRef.

		This class share agent in a static map.

		* \author Chafik sameh
		* \author Nevrax France
		* \date 2000
	*/
	class CLocWordNumRef: public IWordNumRef
	{
	

	private:
		/// internal class use for the std::map fonctionality
		class CRootDico
		{
		private:
			const IRefrence *_Ref;
		public:

			void setRef(const IRefrence *ref)
			{
				_Ref = ref;
			}

			CRootDico(const IRefrence *ref): _Ref(ref)
			{
			}

			CRootDico(const CRootDico &ref): _Ref(ref._Ref)
			{
			}

			operator const IRefrence *() const
			{
				return _Ref;
			}			
		};

	private:		
		///The map use an CNumericIndex as a key for the internal tree.
		typedef std::map<CNumericIndex ,CRootDico> TMapRef;
		static TMapRef *_LocRefence;

	private:
		
		///The iden of the class.
		CNumericIndex _Id;

		///_Stock define the cross reference between agent and this class.
		CRootDico _Stock;

	public:
		///The class factory ident of the class.
		static const NLAIC::CIdentType IdLocWordNumRef;

	public:
		///Construct object for an IRefrence agents objects.
		CLocWordNumRef(const IRefrence &ref):_Stock(&ref)
		{
			_LocRefence->insert(TMapRef::value_type(_Id,&ref));			
		}
		
		/**
		Construct object with an CNumericIndex objects.

		This constroctor allow to reload an IRefrence defined with the CNumericIndex &ref.

		Exception: throw (NLAIE::CExceptionIndexHandeledError)
		*/
		CLocWordNumRef(const CNumericIndex &ref) :_Id(ref),_Stock(NULL)
		{			
			TMapRef::iterator Itr = _LocRefence->find(_Id);
			if(Itr != _LocRefence->end())
			{				
				_Stock.setRef((*Itr).second);
			}
			else throw NLAIE::CExceptionIndexHandeledError();
		}

		/**
		Copy Constructor.
		Exception: throw (NLAIE::CExceptionIndexHandeledError)
		*/
		CLocWordNumRef(const CLocWordNumRef &l) throw (NLAIE::CExceptionIndexHandeledError):/*_Id(l._Id),*/_Stock(NULL)
		{						
			TMapRef::iterator itr = _LocRefence->find(_Id);
			if(itr != _LocRefence->end())
			{
				_Stock.setRef((*itr).second);
			}
			else throw NLAIE::CExceptionIndexHandeledError();
		}
		
		/**
		Copy Constructor.
		Exception: throw (NLAIE::CExceptionIndexHandeledError)
		*/

		CLocWordNumRef(NLMISC::IStream &is) :_Stock(NULL)
		{						
			load(is);			
		}

		CLocWordNumRef():_Stock(NULL)
		{
		}

		void getDebugString(char *t) const
		{
			char i[256*8];
			_Id.getDebugString(i);
			sprintf(t,"CLocWordNumRef<%d>: _Id <%s>",this,i);
		}

		/// \name IBasicInterface method.
		//@{
		virtual const NLAIC::CIdentType &getType() const;		
		virtual const NLAIC::IBasicType *clone() const
		{
			NLAIC::IBasicInterface *m = new CLocWordNumRef(*this);
			m->incRef();
			return m;
		}		
		virtual const NLAIC::IBasicType *newInstance() const
		{
			NLAIC::IBasicInterface *m = new CLocWordNumRef();
			m->incRef();
			return m;
		}
		virtual void save(NLMISC::IStream &os)
		{
			_Id.save(os);
		}
		///Exception: throw (NLAIE::CExceptionIndexHandeledError)
		virtual void load(NLMISC::IStream &is)
		{			
			_Id.load(is);
			TMapRef::iterator Itr = _LocRefence->find(_Id);
			if(Itr != _LocRefence->end())
			{
				_Stock.setRef((*Itr).second);
			}
			else throw NLAIE::CExceptionIndexHandeledError();
		}
		//@}

		virtual operator const IRefrence *() const
		{
			return (const IRefrence *)_Stock;
		}

		virtual ~CLocWordNumRef()
		{
		}

	public:
		
		/// \name Map fonctionality method.		
		//@{

		/// Clear the map.
		static void clear()
		{			
			if(_LocRefence )
			{
				delete _LocRefence;
				_LocRefence = NULL;
			}
		}		

		/// Init the map.
		static void Init()
		{
			if(_LocRefence == NULL) _LocRefence = new CLocWordNumRef::TMapRef;
		}

		/**
		Saving the mapping objects in the word.

		Saving mapping is to save all CNumericIndex shared in the map and its IRefrence class factory ident type.
		*/
		static void saveMapping(ostream &);
		/**
		Load the mapping objects in the word
		*/
		static bool loadMapping(NLMISC::IStream &);
		//@}
	};
	
	///Global method proghrammer have to call this function to initialise the word map reference.
	void initAgentLib();

	///Global method proghrammer have to call this function to release the word map reference.
	void releaseAgentLib();
}


#endif

