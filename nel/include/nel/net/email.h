/** \file email.h
 * send email
 *
 * $Id: email.h,v 1.2 2002/11/29 09:10:46 lecroart Exp $
 */

/* Copyright, 2002 Nevrax Ltd.
 *
 * This file is part of NEVRAX NeL Network Services.
 * NEVRAX NeL Network Services is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX NeL Network Services is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NeL Network Services; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#ifndef NL_EMAIL_H
#define NL_EMAIL_H

#include <string>

#include "nel/misc/report.h"


namespace NLNET {

/** Send an email
 * \param smtpServer must be a smtp email server.
 * \param from must be a valid email address. If empty, create a fake email address with anonymous@<ipaddress>.com
 * \param to must be a valid email address.
 * \param subject subject of the email. Can be empty.
 * \param body body of the email. Can be empty.
 * \param attachedFile a filename that will be send with the email. Can be empty.
 * \param onlyCheck If true, It'll not send the mail but only check if it could be send.
 */

bool sendEmail (const std::string &smtpServer, const std::string &from, const std::string &to, const std::string &subject, const std::string &body, const std::string &attachedFile = "", bool onlyCheck = false);

/**  If you call this function, the default from (when from is "") used in the sendEmail will be the one
 * you set by this function
 */
void setDefaultEmailParams (const std::string &smtpServer, const std::string &from, const std::string &to);

} // NLNET


#endif // NL_EMAIL_H

/* End of email.h */
