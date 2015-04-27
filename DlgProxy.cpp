
// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "LotroBoxer.h"
#include "DlgProxy.h"
#include "LotroBoxerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLotroBoxerDlgAutoProxy

IMPLEMENT_DYNCREATE(CLotroBoxerDlgAutoProxy, CCmdTarget)

CLotroBoxerDlgAutoProxy::CLotroBoxerDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CLotroBoxerDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CLotroBoxerDlg)))
		{
			m_pDialog = reinterpret_cast<CLotroBoxerDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CLotroBoxerDlgAutoProxy::~CLotroBoxerDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CLotroBoxerDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CLotroBoxerDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLotroBoxerDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// Note: we add support for IID_ILotroBoxer to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {37885EAA-CB6F-4FDA-BE8B-219ADA6F186C}
static const IID IID_ILotroBoxer =
{ 0x37885EAA, 0xCB6F, 0x4FDA, { 0xBE, 0x8B, 0x21, 0x9A, 0xDA, 0x6F, 0x18, 0x6C } };

BEGIN_INTERFACE_MAP(CLotroBoxerDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CLotroBoxerDlgAutoProxy, IID_ILotroBoxer, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {4027CE69-721C-48E8-A921-0D83487E5F2C}
IMPLEMENT_OLECREATE2(CLotroBoxerDlgAutoProxy, "LotroBoxer.Application", 0x4027ce69, 0x721c, 0x48e8, 0xa9, 0x21, 0xd, 0x83, 0x48, 0x7e, 0x5f, 0x2c)


// CLotroBoxerDlgAutoProxy message handlers
