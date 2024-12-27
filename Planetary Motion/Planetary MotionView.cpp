// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// Planetary MotionView.cpp : implementation of the CPlanetaryMotionView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Planetary Motion.h"
#endif

#include "Planetary MotionDoc.h"
#include "Planetary MotionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlanetaryMotionView

IMPLEMENT_DYNCREATE(CPlanetaryMotionView, CView)

BEGIN_MESSAGE_MAP(CPlanetaryMotionView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPlanetaryMotionView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CONTEXT_Start, &CPlanetaryMotionView::OnContextStart)
	ON_COMMAND(ID_BUTTON_PAUSE, &CPlanetaryMotionView::OnButtonPause)
	ON_COMMAND(ID_BUTTON_RESUME, &CPlanetaryMotionView::OnButtonResume)
END_MESSAGE_MAP()

// CPlanetaryMotionView construction/destruction

CPlanetaryMotionView::CPlanetaryMotionView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	x = 400;
	y = 200;
	x1 = 300 + 150 * cos(3);
	y1 = 200 + 150 * sin(3);
	m_iCounter = 0;
	x2 = 300 + 200 * cos(3);
	y2 = 200 + 200 * sin(3);
	x3 = 300 + 250 * cos(3);
	y3 = 200 + 250 * sin(3);
}

CPlanetaryMotionView::~CPlanetaryMotionView()
{
}

BOOL CPlanetaryMotionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPlanetaryMotionView drawing

void CPlanetaryMotionView::OnDraw(CDC* pDC)
{
	CPlanetaryMotionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	{
		CPen orbitPen;
		orbitPen.CreatePen(PS_SOLID, 2, RGB(100, 100, 255)); 
		CPen* pOldPen = pDC->SelectObject(&orbitPen);

		// Draw the orbit
		pDC->Ellipse(550, 400, 50, 0); 

		pDC->SelectObject(pOldPen);

		// Planet color (blue)
		CPen planetPen;
		planetPen.CreatePen(PS_SOLID, 3, RGB(0, 0, 255)); // Blue planet outline
		CBrush planetBrush(RGB(0, 0, 255));               // Blue fill
		CBrush* pOldBrush = pDC->SelectObject(&planetBrush);

		// Draw the planet
		pDC->Ellipse(x3 + 20, y3 + 20, x3 - 20, y3 - 20); 

		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);

		// Rings color (red)
		CPen ringPen;
		ringPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // Red rings
		pOldPen = pDC->SelectObject(&ringPen);

		// Draw rings (outer to inner)
		pDC->Ellipse(x3 + 30, y3 + 15, x3 - 30, y3 - 15); // Outer ring
		pDC->Ellipse(x3 + 25, y3 + 10, x3 - 25, y3 - 10); // Inner ring

		pDC->SelectObject(pOldPen);
	}

	{

		CPen green;

		green.CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
		CPen* p04dPen = pDC->SelectObject(&green);
		pDC->Ellipse(500, 400, 100, 0); //Outer ellipse
		pDC->Ellipse(x2 + 20, y2 + 20, x2 - 20, y2 - 20); //Outer planet ellipse

		pDC->SelectObject(p04dPen);
	}
	{
	;
		CPen cyan;

		cyan.CreatePen(PS_SOLID, 3, RGB(0, 204, 204));
		CPen* p02dPen = pDC->SelectObject(&cyan);
		pDC->Ellipse(450, 350, 150, 50); //Middle ellipse
		pDC->Ellipse(x1 + 20, y1 + 20, x1 - 20, y1 - 20); //Middle planet ellipse

		pDC->SelectObject(p02dPen);


	}
	{

		CPen red;

		red.CreatePen(PS_SOLID, 3, RGB(255, 51, 51));
		CPen* p03dPen = pDC->SelectObject(&red);
		pDC->Ellipse(400, 300, 200, 100); //Middle ellipse
		pDC->Ellipse(x + 20, y + 20, x - 20, y - 20); //Middle planet ellipse

		pDC->SelectObject(p03dPen);
	}
	{

		CPen yellow;

		yellow.CreatePen(PS_SOLID, 60, RGB(255, 255, 0));
		CPen* p01dPen = pDC->SelectObject(&yellow);
		pDC->Ellipse(330, 230, 270, 170); //Centre ellipse

		pDC->SelectObject(p01dPen);
	}

	// TODO: add draw code for native data here
}


// CPlanetaryMotionView printing


void CPlanetaryMotionView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPlanetaryMotionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPlanetaryMotionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPlanetaryMotionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPlanetaryMotionView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPlanetaryMotionView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPlanetaryMotionView diagnostics

#ifdef _DEBUG
void CPlanetaryMotionView::AssertValid() const
{
	CView::AssertValid();
}

void CPlanetaryMotionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlanetaryMotionDoc* CPlanetaryMotionView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlanetaryMotionDoc)));
	return (CPlanetaryMotionDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlanetaryMotionView message handlers


void CPlanetaryMotionView::OnContextStart()
{
	// TODO: Add your command handler code here
	m_pCurrentThread = AfxBeginThread(CPlanetaryMotionView::StartThread, this);
}


void CPlanetaryMotionView::OnButtonPause()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->SuspendThread();
}


void CPlanetaryMotionView::OnButtonResume()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->ResumeThread();
}


UINT CPlanetaryMotionView::StartThread(LPVOID Param)
{
	CPlanetaryMotionView* pView = (CPlanetaryMotionView*)Param;
	// TODO: Add your implementation code here.
	CPoint MyPoint(0, 0);
	int j = 0;
	while (1)
	{
		j = j + 6;
		pView->x = 300 + 100 * cos(j);
		pView->y = 200 + 100 * sin(j);
		pView->x1 = 300 + 150 * cos(j + 3);
		pView->y1 = 200 + 150 * sin(j + 3);
		pView->x2 = 300 + 200 * cos(j + 3);
		pView->y2 = 200 + 200 * sin(j + 3);
		pView->x3 = 300 + 250 * cos(j + 3);
		pView->y3 = 200 + 250 * sin(j + 3);

		pView->Invalidate();
		Sleep(400);

	}
	return 0;
}
