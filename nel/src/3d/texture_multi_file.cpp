/** \file texture_multi_file.cpp
 * TODO: File description
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

#include "nel/3d/texture_multi_file.h"
#include "nel/3d/texture_file.h"


namespace NL3D
{

static std::string DummyTexName("CTextureMultiFile:Dummy");

///===========================================================
CTextureMultiFile::CTextureMultiFile(uint numTexs /* = 0 */) : _CurrSelectedTexture(0), _FileNames(numTexs)
{
}


///===========================================================
void CTextureMultiFile::setNumTextures(uint numTexs)
{
	_FileNames.resize(numTexs);
	_CurrSelectedTexture = (uint) std::min((sint) _CurrSelectedTexture, std::min((sint) 0, (sint) (numTexs - 1)));
}


///===========================================================
void CTextureMultiFile::setFileName(uint index, const char *fileName)
{
	_FileNames[index] = fileName;
	if (index == _CurrSelectedTexture) touch();

}


///===========================================================
sint CTextureMultiFile::getTexIndex(uint index) const
{
	if (_FileNames.empty())
	{
		return -1;
	}
	sint usedTexture = index >= _FileNames.size() ? 0 : index;
	if (_FileNames[usedTexture].empty())
	{
		return (usedTexture != 0 && !_FileNames[0].empty()) ? 0 : -1;
	}
	return usedTexture;
}


///===========================================================
void CTextureMultiFile::doGenerate(bool async)
{
	sint usedTexture = getTexIndex(_CurrSelectedTexture);
	if (usedTexture == -1)
	{
		makeDummy();
	}
	else
	{
		CTextureFile::buildBitmapFromFile(*this, _FileNames[usedTexture], async);
	}
}

///===========================================================
void	CTextureMultiFile::serial(NLMISC::IStream &f) throw(NLMISC::EStream)
{
	(void)f.serialVersion(0);

	// serial the base part of ITexture.
	ITexture::serial(f);

	f.serialCont(_FileNames);
	f.serial(_CurrSelectedTexture);

	if(f.isReading())
		touch();
}


///===========================================================
const std::string &CTextureMultiFile::getTexNameByIndex(uint index) const
{
	sint usedTexture = getTexIndex(index);
	return usedTexture == -1 ? DummyTexName : _FileNames[usedTexture];
}


///===========================================================
std::string		CTextureMultiFile::getShareName() const
{
	return getTexNameByIndex(_CurrSelectedTexture);
}

///===========================================================
void CTextureMultiFile::selectTexture(uint index)
{
	if (index != _CurrSelectedTexture)
	{
		_CurrSelectedTexture = index;
		touch();
	}
}


///===========================================================
ITexture *CTextureMultiFile::buildNonSelectableVersion(uint index)
{
	CTextureFile *tf = new CTextureFile(getTexNameByIndex(index));
	// copy tex parameters
	(ITexture &) *tf = (ITexture &) *this; // invoke ITexture = op for basics parameters
	//
	return tf;
}


} // NL3D
