
// LotroBoxerDlg.h : header file
//

#pragma once

class CLotroBoxerDlgAutoProxy;


// CLotroBoxerDlg dialog
class CLotroBoxerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLotroBoxerDlg);
	friend class CLotroBoxerDlgAutoProxy;

// Construction
public:
	CLotroBoxerDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CLotroBoxerDlg();

// Dialog Data
	enum { IDD = IDD_LOTROBOXER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CLotroBoxerDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedbtnlaunch();
	afx_msg void OnBnClickedbtnfindhandles();
	
};
