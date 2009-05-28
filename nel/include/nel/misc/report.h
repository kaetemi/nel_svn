/** \file report.h
 * This function display a custom message box to report something.
 * It is used in the debug system
 */

/* Copyright, 2002 Nevrax Ltd.
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

#ifndef NL_REPORT_H
#define NL_REPORT_H

#include "types_nl.h"

namespace NLMISC {

/** Display a custom message box.
 *
 * \param title set the title of the report. If empty, it'll display "NeL report".
 * \param header message displayed before the edit text box. If empty, it displays the default message.
 * \param body message displayed in the edit text box. This string will be sent by email.
 * \param debugButton 0 for disabling it, 1 for enable with default behaviors (generate a breakpoint), 2 for enable with no behavior
 *
 *
 *
 * \return the button clicked or error
 */

enum TReportResult { ReportDebug, ReportIgnore, ReportQuit, ReportError };

TReportResult report (const std::string &title, const std::string &header, const std::string &subject, const std::string &body, bool enableCheckIgnore, uint debugButton, bool ignoreButton, sint quitButton, bool sendReportButton, bool &ignoreNextTime, const std::string &attachedFile = "");

/** call this in the main of your appli to enable email: setReportEmailFunction (sendEmail);
 */
void setReportEmailFunction (void *emailFunction);

} // NLMISC

#endif // NL_REPORT_H

/* End of report.h */
