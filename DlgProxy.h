
// DlgProxy.h: header file
//

#pragma once

class CLotroBoxerDlg;


// CLotroBoxerDlgAutoProxy command target

class CLotroBoxerDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CLotroBoxerDlgAutoProxy)

	CLotroBoxerDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CLotroBoxerDlg* m_pDialog;

// Operations
public:

// Overrides
	public:
	virtual void OnFinalRelease();

// Implementation
protected:
	virtual ~CLotroBoxerDlgAutoProxy();

	// Generated message map functions

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CLotroBoxerDlgAutoProxy)

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

