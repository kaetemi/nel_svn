/** \file di_keyboard_device.h
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

#ifndef NL_DI_KEYBOARD_H
#define NL_DI_KEYBOARD_H

#include "nel/misc/types_nl.h"

#ifdef NL_OS_WINDOWS

#include "nel/misc/input_device_server.h"
#include "nel/misc/keyboard_device.h"
#include "nel/misc/di_event_emitter.h"
#include "nel/misc/bit_set.h"





namespace NLMISC
{

class CWinEventEmitter;

//
struct EDirectInputNoKeyboard : public EDirectInput
{
	EDirectInputNoKeyboard() : EDirectInput("No keyboard found") {}
};


struct CKeyConv;

/**
 * Direct Input implementation of a keyboard.
 * \see CDIEventEmitter
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 2002
 */
class CDIKeyboard : public IKeyboardDevice
{
public:
	bool					ShiftPressed, CtrlPressed, AltPressed;
public:
	///\name Object
	//@{
		/** Create a keyboard device, that must then be deleted by the caller
		  * An optionnal WinEventEmiter can be provided, so that its flags can be in sync
		  * with a win32 keyboard flags (shift, ctrl, and alt)
		  */
		static CDIKeyboard *createKeyboardDevice(IDirectInput8 *di8,
												 HWND hwnd,
												 CDIEventEmitter *diEventEmitter,
												 CWinEventEmitter *we = NULL
												) throw(EDirectInput);
		// dtor
		virtual ~CDIKeyboard();
	//@}

	///\name From IInputDevice
	//@{
		virtual bool		setBufferSize(uint size);
		virtual uint		getBufferSize() const;
	//@}

	///\name From IInputDevice
	//@{
		uint getKeyRepeatDelay() const { return _RepeatDelay; }
		void setKeyRepeatDelay(uint delay) { nlassert(delay > 0); _RepeatDelay = delay; }
		uint getKeyRepeatPeriod() const { return _RepeatPeriod; }
		void setKeyRepeatPeriod(uint period) { nlassert(period > 0); _RepeatPeriod = period; }
		void disableRepetition(const TKey *keyTab, uint numKey);
		uint getNumDisabledRepetition() const;
		void getDisabledRepetitions(TKey *destTab) const;
	//@}

	TMouseButton	buildKeyboardFlags() const;
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	//
	bool						_CapsLockToggle; // true if caps lock off is triggered by caps lock, false if it toggled by shift
	uint						_RepeatDelay; // the delay before a key is repeated (in ms)
	uint						_RepeatPeriod; // The period for key repetitions (in ms)
	//
	LPDIRECTINPUTDEVICE8		_Keyboard;
	uint						_KeyboardBufferSize;
	// virtual code state
	uint8						_VKKeyState[NumKeys];
	// tells for which keys repetition is disabled
	CBitSet						_RepetitionDisabled;
	// The date at which the last key pressed has been pressed (not using 64 bits since note handled by Direct Input)
	uint32						_FirstPressDate;
	// The last date at which key repetition occured (not using 64 bits since note handled by Direct Input)
	uint32						_LastEmitDate;
	// The system date at which the last polling occured (not using 64 bits since note handled by Direct Input)
	uint32						_PollTime;
	uint						_LastDIKeyPressed;
	CWinEventEmitter			*_WE;
	HWND						_hWnd;
	HKL							_KBLayout;
	//
	CDIEventEmitter				*_DIEventEmitter;
	//
	static const CKeyConv *DIKeyToNelKeyTab[NumKeys];
private:
	/// ctor
	CDIKeyboard(CWinEventEmitter	*we, HWND hwnd);
	/** Convert a direct input scancode to a virtual key. Note that DirectInput scancodes do not always match system scan codes.
	  * Repeatable has a meaning only for extended keys
	  */
	TKey			DIKeyToNelKey(uint diKey, bool &extKey, bool &repeatable);
	/** This update virtual key state table.
	  * \param keyValue contains the value to send to a EventKeyDown or EventKeyUp message.
	  * \param charValue contains the value that must be used for Unicode conversion (which generate EventChar messages)
	  */
	void			updateVKKeyState(uint diKey, bool pressed, TKey &keyValue, TKey &charValue);
	// Use the given virtual key code and the current keyb state to produce Unicode
	void			sendUnicode(TKey vkey, uint dikey, CEventServer *server, bool pressed);
	// Build a TKeyButton value from the state of shift, ctrl and alt
	TKeyButton		buildKeyButtonsFlags() const;
	// Update the state of this object and send the appropriate message when a direct / input key has been pressed / released
	void			keyTriggered(bool pressed, uint key, CEventServer *server, uint32 date);
	// The same as buildKeyButtonsFlags(), but the return is a TMouseButtonValue (with no mouse value setupped)
	TMouseButton	buildKeyboardButtonFlags() const;
	// setup the state of the Ctrl, Alt and Shift key from the state in the _VKKeyState buffer
	void			updateCtrlAltShiftValues();
	/// Repeat the current key, and create events
	void			repeatKey(uint32 currentDate, CEventServer *server);
	/// Build a date by using an event time stamp, or generate one if NULL
	uint32			buildDateFromEvent(const IInputDeviceEvent *deviceEvent);

	///\name From IInputDevice
	//@{
		virtual void		poll(CInputDeviceServer *dev);
		virtual void		submit(IInputDeviceEvent *deviceEvent, CEventServer *server);
		virtual void		transitionOccured(CEventServer *server, const IInputDeviceEvent *nextMessage);
	//@}
};


} // NLMISC


#endif // NL_OS_WINDOWS

#endif // NL_DI_KEYBOARD_H

/* End of di_keyboard.h */
