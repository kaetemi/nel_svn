/** \file sample_bank.h
 * CSampleBank: a set of samples
 */

/* Copyright, 2001 Nevrax Ltd.
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

#ifndef NL_SAMPLE_BANK_H
#define NL_SAMPLE_BANK_H

#include "nel/misc/types_nl.h"
#include "nel/misc/stream.h"
#include "nel/misc/string_mapper.h"
#include "nel/georges/u_form_elm.h"
#include "nel/sound/u_source.h"
#include "audio_mixer_user.h"
#include <string>

namespace NLSOUND {


class ISoundDriver;
class IBuffer;
class CSampleBank;

/*
// Comparision for const char*
struct eqname
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) == 0;
  }
};
*/

/// Sample names hash map
//typedef std::hash_map<std::string, IBuffer*> TSampleTable;
typedef CHashMap<NLMISC::TStringId, IBuffer*, NLMISC::CStringIdHashMapTraits> TSampleTable;


/**
 * A set of samples.
 * \author Peter Hanappe
 * \author Nevrax France
 * \date 2001
 */
class CSampleBank : public CAudioMixerUser::IMixerUpdate
{
public:

	/** Initialise the sample bank with the mixer config file.
	*/
	static void			init(NLGEORGES::UFormElm *mixerConfig);

	/// Return an existing bank for the given file name, NULL if no bank for this file.
	static CSampleBank *findSampleBank(const NLMISC::TStringId &filename);

	/// Return the name corresponding to a name. The sample is searched
	// in all the loaded sample banks.
	static IBuffer*		get(const NLMISC::TStringId &name);

	/// Reload all the sample bank.
	static void			reload(bool async);

	/// Return the total loaded samples size.
	static uint			getTotalByteSize()				{	return _LoadedSize; };

	/// Fill a vector with current loaded sample banks.
	static void			getLoadedSampleBankInfo(std::vector<std::pair<std::string, uint> > &result);



	/// Constructor
	CSampleBank(const std::string& name, ISoundDriver *sd);

	/// Destructor
	virtual ~CSampleBank();


	/** Load all the samples.
	 *
	 * Can throw EPathNotFound or ESoundFileNotFound (check Exception)
	 * \param async If true, the samples are loaded in background.
	 */
	void				load(bool async);

	/** Unload all the samples in this bank. Return false is unload can't be done (if an async
	 *	loading is not terminated.
	 */
	bool				unload();


	/// Returns true if the samples in this bank have been loaded.
	bool				isLoaded();

	/// Return a samples corresponding to a name.
	IBuffer				*getSample(const NLMISC::TStringId &name);

	/// Return the number of samples in this bank.
	uint				countSamples();

	/// Return the size of this bank in bytes.
	uint				getSize();

	/// Return the filename
//	const std::string&	getPath() const						{ return _Path; }

	/// Return the name (must be unique)
	const NLMISC::TStringId	getName() const						{ return _Name; }

	/// Delete all the loaded banks.
	static	void		releaseAll();


private:
	/// The update method. Used when waiting for async sample loading.
	void onUpdate();

//	typedef std::hash_map<std::string, CSampleBank*>				TSampleBankContainer;
	typedef CHashMap<NLMISC::TStringId, CSampleBank*, NLMISC::CStringIdHashMapTraits>			TSampleBankContainer;

	// The map off all loaded sample banks
	static TSampleBankContainer			_Banks;
	// The total size of loaded samples.
	static	uint						_LoadedSize;

	// Sound driver
	ISoundDriver		*_SoundDriver;

	// Hashtable with samples
	TSampleTable		_Samples;

	// Sample bank name and path
//	std::string			_Path;
	NLMISC::TStringId	_Name;

	// Did we load the buffers.
	bool				_Loaded;
	// Is the async load is done ?
	bool				_LoadingDone;
	// The size of the samples in the bank
	uint				_ByteSize;

	/// Flag for splitted load.
	bool				_SplitLoadDone;

	/// List of sample that need to be loaded asynchronously.
	std::list<std::pair<IBuffer *, NLMISC::TStringId> >	_LoadList;

	struct TFilteredBank
	{
		uint32				Filter;
		NLMISC::TStringId	BankName;
	};

	/// List of virtual sample bank.
	typedef CHashMap<NLMISC::TStringId, std::vector<TFilteredBank>, NLMISC::CStringIdHashMapTraits>	TVirtualBankCont;
	static TVirtualBankCont		_VirtualBanks;

};


/**
 * ESoundFileNotFound
 */

class ESampleBankNotFound : public NLMISC::Exception
{
public:
	ESampleBankNotFound( const std::string filename ) :
	  NLMISC::Exception( (std::string("Sample bank not found: ")+filename).c_str() ) {}
};

} // NLSOUND


#endif // NL_SAMPLE_BANK_H

/* End of sound.h */

