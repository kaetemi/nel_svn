/** \file module_message.cpp
 * module message implementation
 *
 * $Id: module_message.cpp,v 1.3 2006/05/31 12:03:17 boucher Exp $
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


#include "stdnet.h"
#include "nel/net/module_message.h"

// a stupid function to remove some more stupid visual warnings
void foo_module_message() {};

namespace NLNET
{
//	CModuleMessage::CModuleMessage(const CMessage &messageBody)
//		: MessageType(mt_invalid),
//		SenderModuleId(INVALID_MODULE_ID),
//		AddresseeModuleId(INVALID_MODULE_ID),
//		MessageBody(const_cast<CMessage&>(messageBody))
//	{
//
//	}
//
//
//	void CModuleMessage::serial(NLMISC::IStream &s)
//	{
//		nlassert(mt_num_types < 0xFF);
//		nlassert(MessageType != mt_invalid);
//
//		s.serialBitField8(reinterpret_cast<uint8&>(MessageType));
//		s.serial(SenderModuleId);
//		s.serial(AddresseeModuleId);
//		MessageBody.serialMessage()
//	}


} // namespace NLNET
