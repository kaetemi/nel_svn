/** \file sound_document_plugin.h
 * Georges plugin for sound documents
 *
 * $Id: sound_anim_view.h,v 1.1 2002/06/18 16:04:59 hanappe Exp $
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


#ifndef NL_SOUND_ANIM_VIEW
#define NL_SOUND_ANIM_VIEW

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSoundAnimDlg;
class CObjectViewer;
class CAnimationDlg;

namespace NLSOUND
{
	class CSoundAnimation;
	class CSoundAnimMarker;
}


/**
 *  CSoundAnimationHolder is a placeholder for the animations in current
 *  playlist of the object viewer. It point to the sound animation and
 *  keeps track of its start and end time.
 */

class CSoundAnimationHolder
{
public:

	// copy constructor
	CSoundAnimationHolder(const CSoundAnimationHolder& a) 
	{
		_Anim = a._Anim;
		_AnimStart = a._AnimStart;
		_AnimEnd = a._AnimEnd;
	}

	CSoundAnimationHolder(NLSOUND::CSoundAnimation* anim = 0, float start = 0.0f, float end = 0.0f)
		: _Anim(anim), _AnimStart(start), _AnimEnd(end) {}

	bool	inside(float time)		{ return (_AnimStart <= time) && (time <= _AnimEnd); }
	float	offset(float time)		{ return time - _AnimStart; }

	NLSOUND::CSoundAnimation*	_Anim;
	float						_AnimStart;
	float						_AnimEnd;
};


typedef std::vector<CSoundAnimationHolder>  CAnimationVector;



/**
 *  CSoundAnimView displays a time line of the current animation
 *  playlist. It shows the individual animations (name, start, end)
 *  and the markers of the animations. It offers functions to edit
 *  the markers.
 */

class CSoundAnimView : public CWnd
{
public:

	CSoundAnimView() : CWnd() {}
	virtual ~CSoundAnimView() {}

	virtual void			Create(CObjectViewer* objView, CAnimationDlg* animDlg, CSoundAnimDlg* parent, const RECT& rect);  

	void					setAnimTime(float animStart, float animEnd);
	void					zoomIn();
	void					zoomOut();
	void					mark();
	void					save();
	void					deleteMarker();
	void					refresh(BOOL update);
	void					updateCursor();
	void					changeScroll(uint curpos);

	
protected:

	static bool					registerClass();
	static bool					_Registered;
	static CString				_WndClass;
	static uint					_WndId;
	static const float			_Scale;       // conversion time to pixels: pixel = time * _Zoom * _Scale
	static const uint			_ZoomCount;
	static float				_ZoomValue[];
	static CBrush				_FillBrush;
	static CBrush				_MarkerBrush;
	static CBrush				_SelectBrush;
	static CFont				_Font;
	static CPen					_RedPen;

	sint32						timeToPixel(float time)		{ return (sint32) (time * _Zoom * _Scale); }
	float						pixelToTime(sint32 pixel)		{ return (float) pixel / _Zoom / _Scale; } 
	bool						getAnimationAt(CSoundAnimationHolder& holder, float time);
	NLSOUND::CSoundAnimMarker*	getMarkerAt(CPoint point);	
	void						insertMarkerAt(float time);	
	void						changeTimeScale();


	CObjectViewer				*_ObjView;
	CAnimationDlg				*_AnimationDlg;
	CSoundAnimDlg				*_SoundAnimDlg;
	CAnimationVector			_Animations;
	float						_Zoom;
	uint						_ZoomIndex;
	sint						_Cursor;
	CSoundAnimationHolder		_SelectedAnim;
	NLSOUND::CSoundAnimMarker	*_SelectedMarker;

	bool						_Dragging;
	CPoint						_DragStartPoint;
	float						_DragStartTime;
	
	float						_TimeStart;
	float						_TimeEnd;
	float						_TimeOffset;
	uint						_PixelsTotal;
	uint						_PixelsOffset;
	uint						_PixelsViewH;
	uint						_PixelsViewV;
	std::string					_StringBuffer;
	

// MFC crap
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoundAnimView)
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	DECLARE_DYNCREATE(CSoundAnimView)

	// Generated message map functions
	//{{AFX_MSG(CSoundAnimView)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // NL_SOUND_ANIM_VIEW
