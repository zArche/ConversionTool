
// ConversionToolDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CConversionToolDlg dialog
class CConversionToolDlg : public CDialogEx
{
// Construction
public:
	CConversionToolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONVERSIONTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonConversion();
	afx_msg void OnBnClickedButtonUrlRecovery();
	afx_msg void OnBnClickedButtonSqlRecovery();
	afx_msg void OnBnClickedButtonHexRecovery();
	afx_msg void OnBnClickedButtonSignleRecovery();
	afx_msg void OnBnClickedButtonBase64Recovery();
	afx_msg void OnEnChangeEditOriginContent();
	CEdit originContent;
	CEdit urlContent;
	CEdit sqlContent;
	CEdit hexContent;
	CEdit asciiContent;
	CEdit md532Content;
	CEdit md516Content;
	CEdit base64Content;
	CEdit base64RecoveryContent;
	CString orgin;
	CString url;
	CString sql;
	CString hex;
	CString ascii;
	CString md532;
	CString md516;
	CString base64;
	CString base64Recovery;

};
