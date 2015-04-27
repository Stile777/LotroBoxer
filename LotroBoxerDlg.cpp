
// LotroBoxerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LotroBoxer.h"
#include "LotroBoxerDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include <Windows.h>
#include <vector>
#include <Shlwapi.h>
#include <sstream>
#include <iostream>

using namespace std;

#pragma comment(lib, "shlwapi")

std::vector<HWND> vHwnd;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//----------------------------------------------------------------------------------------------------------------------
//  IS LOTRO WINDOW
//----------------------------------------------------------------------------------------------------------------------
bool is_lotro_window(HWND h)
{
	wchar_t aw[1024] = { 0 };

	if (0 == GetClassName(h, aw, ARRAYSIZE(aw)))
		return FALSE;

	return 0 == StrCmp(aw, L"Turbine Device Class") ? true : false;
}


//----------------------------------------------------------------------------------------------------------------------
//  OUR CALLBACK
//----------------------------------------------------------------------------------------------------------------------
BOOL CALLBACK our_callback(HWND h, LPARAM)
{
	if (is_lotro_window(h))
		vHwnd.emplace_back(h);

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
//  SHOW RESULTS
//----------------------------------------------------------------------------------------------------------------------
void show_results()
{
	

std::wostringstream ss;

//ss << L"We found " << vHwnd.size () << L" Lotro window " << ( 1 == vHwnd.size () ? L"handle." : L"handles." );

ss << L"We found " << vHwnd.size() << L" Lotro window " << endl << endl;
//<< L"Number 1 " << vHwnd.at(0) << endl; 
//<< L"Number 2 " << vHwnd.at(1) << endl << L"Number 3 " << vHwnd.at(2) << endl;

//for ( std::vector<HWND>::iterator i = vHwnd.begin (); i != vHwnd.end (); ++i ) ss << L"\n" << *i;

::MessageBox(NULL, ss.str().c_str(), L"Lotro", MB_OK);

}
//_______________________________________________________________________________________________________________________

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLotroBoxerDlg dialog


IMPLEMENT_DYNAMIC(CLotroBoxerDlg, CDialogEx);

CLotroBoxerDlg::CLotroBoxerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLotroBoxerDlg::IDD, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CLotroBoxerDlg::~CLotroBoxerDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CLotroBoxerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLotroBoxerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(btnLaunch, &CLotroBoxerDlg::OnBnClickedbtnlaunch)
	ON_BN_CLICKED(btnFindHandles, &CLotroBoxerDlg::OnBnClickedbtnfindhandles)
END_MESSAGE_MAP()


// CLotroBoxerDlg message handlers

BOOL CLotroBoxerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLotroBoxerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLotroBoxerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLotroBoxerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CLotroBoxerDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CLotroBoxerDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CLotroBoxerDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CLotroBoxerDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CLotroBoxerDlg::OnBnClickedbtnlaunch()
{
	// TODO: Add your control notification handler code here
	
	

		// CHANGE NEXT LINE TO MATCH LOTRO'S PATH ON YOUR COMPUTER
		const wchar_t pExePath[] = L"G:\\Games\\The Lord of the Rings Online\\TurbineLauncher.exe";

		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		BOOL iResult = CreateProcess(NULL,

			(LPWSTR)pExePath,

			NULL,

			NULL,

			FALSE,

			0,

			NULL,

			NULL,

			&si,

			&pi

			);

	
}


void CLotroBoxerDlg::OnBnClickedbtnfindhandles()
{
	// TODO: Add your control notification handler code here

	

	show_results();

//	


		
}


