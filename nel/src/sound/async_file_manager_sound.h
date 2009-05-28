/** \file async_file_manager_sound.h
 * TODO: File description
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

#include "nel/misc/thread.h"

namespace NLSOUND
{

class IBuffer;


/**
 * CAsyncFileManagerSound is a class that manage sound file loading in a seperate thread
 * This class mostly depend on the CAsyncFileManager class for serializing async file
 * loas request.
 * \author Boris Boucher
 * \author Nevrax France
 * \date 2002
 */
class CAsyncFileManagerSound
{
	NLMISC_SAFE_SINGLETON_DECL(CAsyncFileManagerSound);
public:
//	static	CAsyncFileManagerSound &getInstance();
	static  void	terminate();


	void	loadWavFile(IBuffer *pdestBuffer, const std::string &filename);
	void	cancelLoadWaveFile(const std::string &filename);

	// Do not use these methods with the bigfile manager
	void loadFile (const std::string &fileName, uint8 **pPtr);
	void loadFiles (const std::vector<std::string> &vFileNames, const std::vector<uint8**> &vPtrs);

	void signal (bool *pSgn); // Signal a end of loading for a group of "mesh or file" added
	void cancelSignal (bool *pSgn);

private:
	/// Constructor
	CAsyncFileManagerSound() {}

	/// Singleton instance.
//	static CAsyncFileManagerSound	*_Singleton;


	/// A non exported class for load canceling purpose.
	friend class CCancelLoadWavFile;

	// Load task.
	class CLoadWavFile : public NLMISC::IRunnable
	{
		IBuffer		*_pDestbuffer;

	public:
		std::string	_Filename;

		CLoadWavFile (IBuffer *pdestBuffer, const std::string &filename);
		void run (void);
	};

};

} // NLSOUND
