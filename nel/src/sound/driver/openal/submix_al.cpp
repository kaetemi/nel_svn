/**
 * \file submix_al.cpp
 * \brief CSubmixAl
 * \date 2008-09-15 23:09GMT
 * \author Jan Boon (Kaetemi)
 * CSubmixAl
 */

/* 
 * Copyright (C) 2008  by authors
 * 
 * This file is part of NEVRAX NEL.
 * NEVRAX NEL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 2 of the License,
 * or (at your option) any later version.
 * 
 * NEVRAX NEL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NEL; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 */

#include "stdopenal.h"
#include "submix_al.h"

// STL includes

// NeL includes
// #include <nel/misc/debug.h>

// Project includes
#include "effect_al.h"
#include "sound_driver_al.h"

using namespace std;
// using namespace NLMISC;

namespace NLSOUND {

CSubmixAl::CSubmixAl(ALuint alEfxObject) : _AlAuxEffectSlot(alEfxObject), _Effect(NULL)
{
	
}

CSubmixAl::~CSubmixAl()
{
	
}

void CSubmixAl::setEffect(IEffect *effect)
{
	if (_Effect) if (_Effect->getType() == IEffect::Reverb)
	{
		alAuxiliaryEffectSloti(_AlAuxEffectSlot, AL_EFFECTSLOT_AUXILIARY_SEND_AUTO, AL_FALSE); // auto only for reverb!
	}
	if (!effect)
	{
		alAuxiliaryEffectSloti(_AlAuxEffectSlot, AL_EFFECTSLOT_EFFECT, AL_EFFECT_NULL);
		_Effect = NULL;
	}
	else switch (effect->getType())
	{
		case IEffect::Reverb:
		{
			CReverbEffectAl *reverb = static_cast<CReverbEffectAl *>(effect);
			alAuxiliaryEffectSloti(_AlAuxEffectSlot, AL_EFFECTSLOT_EFFECT, reverb->getAlEfxObject()); alTestError();
			alAuxiliaryEffectSloti(_AlAuxEffectSlot, AL_EFFECTSLOT_AUXILIARY_SEND_AUTO, AL_TRUE); alTestError(); // auto only for reverb!
			_Effect = effect;
			break;
		}
		default:
		{
			nlwarning("AL: Unknown effect type");
			alAuxiliaryEffectSloti(_AlAuxEffectSlot, AL_EFFECTSLOT_EFFECT, AL_EFFECT_NULL); alTestError();
			_Effect = NULL;
			break;
		}
	}
}

void CSubmixAl::setGain(float gain)
{
	
}

} /* namespace NLSOUND */

/* end of file */
