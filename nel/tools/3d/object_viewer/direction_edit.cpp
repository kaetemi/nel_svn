/** \file direction_edit.cpp
 * a dialog to choose a direction (normalized vector).
 *
 * $Id: direction_edit.cpp,v 1.5 2004/06/17 08:14:41 vizerie Exp $
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
#include "std_afx.h"
#include "object_viewer.h"
#include "direction_edit.h"
#include "direction_attr.h"
#include "popup_notify.h"

#include "nel/misc/vector.h"

/////////////////////////////////////////////////////////////////////////////
// CDirectionEdit dialog


CDirectionEdit::CDirectionEdit(IPSWrapper<NLMISC::CVector> *wrapper) 
: _Wrapper(wrapper), _MouseState(CDirectionEdit::Wait)

{
	nlassert(wrapper);
	//{{AFX_DATA_INIT(CDirectionEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDirectionEdit::init(IPopupNotify *pn, CWnd *pParent)
{
	Create(IDD_DIRECTION_EDIT, pParent);
	_Parent = pn;
	ShowWindow(SW_SHOW);
}


void CDirectionEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirectionEdit)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDirectionEdit, CDialog)
	//{{AFX_MSG_MAP(CDirectionEdit)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// private : draw a basis with the given letters
static void DrawBasis(CDC &dc, sint x, sint y, sint size, const char *xStr, const char *yStr)
{
	dc.FillSolidRect(x, y,  size, size, 0xffffff);

	CPen p;
	p.CreatePen(PS_SOLID, 1, (COLORREF) 0);

	CPen *oldPen = dc.SelectObject(&p);

	dc.MoveTo(x + 5, y + size / 2);
	dc.LineTo(x + size - 5, y + size / 2);
	dc.MoveTo(x + size / 2, y + 5);
	dc.LineTo(x + size / 2, y + size - 5);

	dc.TextOut(x + size - 20, y + size / 2 - 18, CString(xStr));
	dc.TextOut(x + 5 + size / 2,  y + 5, CString(yStr));

	dc.SelectObject(oldPen);
}


/// private : draw a vector in a basis  
static void DrawVector(CDC &dc, float vx, float vy, sint x, sint y, sint size)
{
	CPen p;
	p.CreatePen(PS_SOLID, 1, (COLORREF) 0xff);
	CPen *oldPen = dc.SelectObject(&p);

	dc.MoveTo(x + size / 2, y + size / 2);
	dc.LineTo(int(x + size / 2 + vx * 0.9f * size / 2), int(y + size / 2 - vy * 0.9f * size / 2));	

	dc.SelectObject(oldPen);
	
}

// size in pixel of the basis that is drawn in the dialog
const uint32 BasisSize = 120;

// the gap between 2 basis on the screen
const uint32 BasisGap = 20;

// the distance to the upper left corner for the basis drawing
const uint CornerDist = 10;




/// private get back a screen coord (pox, py) to a part of a vector. The basis of click is (x, y) - (x + size, y + size)
static void ScreenToVect(float &vx, float &vy, sint px, sint py, sint x, sint y, sint size)
{
	vx = (px - (x + size / 2)) / 0.9f;
	vy = ((y + size / 2) - py) / 0.9f;
}

void CDirectionEdit::OnPaint() 
{
	CPaintDC dc(this); 

	// get the current vector;
	NLMISC::CVector v = _Wrapper->get();


	// draw a white square, and draw the vector in it
	
	DrawBasis(dc, CornerDist, CornerDist, BasisSize, "X", "Z");
	DrawVector(dc, v.x, v.z, CornerDist, CornerDist, BasisSize);

	DrawBasis(dc, CornerDist, CornerDist + BasisGap + BasisSize, BasisSize, "Y", "Z");	
	DrawVector(dc, v.y, v.z, CornerDist, CornerDist + BasisGap + BasisSize, BasisSize);
	
}

void CDirectionEdit::selectNewVect(const CPoint &point)
{
	const float epsilon = 10E-3f;
	NLMISC::CVector v = _Wrapper->get();
	if (point.x > CornerDist && point.y > CornerDist && point.x < (CornerDist + BasisSize) && point.y < (CornerDist + BasisSize))
	{		
		ScreenToVect(v.x, v.z, point.x, point.y, CornerDist, CornerDist, BasisSize);	
		float d = v.x * v.x + v.z * v.z;
		float f; 
		if (fabsf(d > epsilon))
		{
			f = sqrtf((1.f - v.y * v.y) / d);
		}
		else
		{
			f = 1;
		}

		v.x *= f;
		v.z *= f;
	}

	if (point.x > CornerDist && point.y > (BasisGap + BasisSize + CornerDist) && point.x < (CornerDist + BasisSize) && point.y < (CornerDist + BasisGap + 2 * BasisSize))
	{		
		ScreenToVect(v.y, v.z, point.x, point.y, CornerDist, CornerDist + BasisGap + BasisSize, BasisSize);	
		float d = v.y * v.y + v.z * v.z;
		float f; 
		if (fabsf(d > epsilon))
		{
			f = sqrtf((1.f - v.x * v.x) / d);
		}
		else
		{
			f = 1;
		}

		v.y *= f;
		v.z *= f;
	}

	v.normalize();
	_Wrapper->setAndUpdateModifiedFlag(v);

	Invalidate();

}

void CDirectionEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	selectNewVect(point);
	_MouseState = Drag;
	CDialog::OnLButtonDown(nFlags, point);
}

void CDirectionEdit::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (_MouseState == Drag)
	{
			selectNewVect(point);

	}
	CDialog::OnMouseMove(nFlags, point);
}

void CDirectionEdit::OnLButtonUp(UINT nFlags, CPoint point) 
{
	_MouseState = Wait;	
	CDialog::OnLButtonUp(nFlags, point);
}


void CDirectionEdit::OnClose() 
{	
	nlassert(_Parent);	
	CDialog::OnClose();
	_Parent->childPopupClosed(this);
}
