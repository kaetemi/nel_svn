/** \file hls_texture_manager.cpp
 * TODO: File description
 *
 * $Id: hls_texture_manager.cpp,v 1.4 2005/02/22 10:19:10 besson Exp $
 */

/* Copyright, 2000-2002 Nevrax Ltd.
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

#include "std3d.h"
#include "nel/3d/hls_texture_manager.h"
#include "nel/misc/common.h"
#include "nel/misc/algo.h"

using namespace std;
using namespace NLMISC;

namespace NL3D {


// ***************************************************************************
CHLSTextureManager::CHLSTextureManager()
{
}

// ***************************************************************************
CHLSTextureManager::~CHLSTextureManager()
{
	reset();
}

// ***************************************************************************
void			CHLSTextureManager::reset()
{
	// delete instances.
	contReset(_Instances);

	// delete banks.
	for(uint i=0;i<_Banks.size();i++)
	{
		delete _Banks[i];
	}
	contReset(_Banks);
}

// ***************************************************************************
void			CHLSTextureManager::addBank(CHLSTextureBank *bank)
{
	// add the bank to the list
	_Banks.push_back(bank);

	// Add the bank instance list to the main.
	bank->fillHandleArray(_Instances);

	// then re-sort this array.
	sort(_Instances.begin(), _Instances.end());
}


// ***************************************************************************
sint			CHLSTextureManager::findTexture(const std::string &name) const
{
	// empty?
	if(_Instances.empty())
		return -1;

	// Build a valid key.
	string	nameLwr= toLower(name);
	CHLSTextureBank::CTextureInstance		textKey;
	CHLSTextureBank::CTextureInstanceHandle	textKeyHandle;
	textKey.buildAsKey(nameLwr.c_str());
	textKeyHandle.Texture= &textKey;

	// logN search it in the array
	uint	id= searchLowerBound(_Instances, textKeyHandle);
	// verify if really same name (index must exist since 0 if error, and not empty here)
	CHLSTextureBank::CTextureInstance		&textInst= *_Instances[id].Texture;
	if( textInst.sameName(nameLwr.c_str()) )
		return id;
	else
		return -1;
}

// ***************************************************************************
bool			CHLSTextureManager::buildTexture(sint textId, NLMISC::CBitmap &out) const
{
	if(textId<0 || textId>=(sint)_Instances.size())
		return false;
	else
	{
		// Ok. build the bitmap
		CHLSTextureBank::CTextureInstance		&textInst= *_Instances[textId].Texture;
		textInst.buildColorVersion(out);
		return true;
	}
}


// ***************************************************************************
const char		*CHLSTextureManager::getTextureName(uint i) const
{
	nlassert(i<_Instances.size());
	return _Instances[i].Texture->getName();
}


} // NL3D
