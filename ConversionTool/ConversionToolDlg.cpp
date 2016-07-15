
// ConversionToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConversionTool.h"
#include "ConversionToolDlg.h"
#include "afxdialogex.h"
#include "Tool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CConversionToolDlg dialog



CConversionToolDlg::CConversionToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONVERSIONTOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConversionToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ORIGIN_CONTENT, originContent);
	DDX_Control(pDX, IDC_EDIT_URL_CONTENT, urlContent);
	DDX_Control(pDX, IDC_EDIT_SQL_CONTENT, sqlContent);
	DDX_Control(pDX, IDC_EDIT_HEX_CONTENT, hexContent);
	DDX_Control(pDX, IDC_EDIT_ASCII_CONTENT, asciiContent);
	DDX_Control(pDX, IDC_EDIT_MD5_32_CONTENT, md532Content);
	DDX_Control(pDX, IDC_EDIT_MD5_16_CONTENT, md516Content);
	DDX_Control(pDX, IDC_EDIT_BASE64_CONTENT, base64Content);
	DDX_Control(pDX, IDC_EDIT_BASE64_RECOVERY, base64RecoveryContent);
}

BEGIN_MESSAGE_MAP(CConversionToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONVERSION, &CConversionToolDlg::OnBnClickedButtonConversion)
	ON_BN_CLICKED(IDC_BUTTON_URL_RECOVERY, &CConversionToolDlg::OnBnClickedButtonUrlRecovery)
	ON_BN_CLICKED(IDC_BUTTON_SQL_RECOVERY, &CConversionToolDlg::OnBnClickedButtonSqlRecovery)
	ON_BN_CLICKED(IDC_BUTTON_HEX_RECOVERY, &CConversionToolDlg::OnBnClickedButtonHexRecovery)
	ON_BN_CLICKED(IDC_BUTTON_SIGNLE_RECOVERY, &CConversionToolDlg::OnBnClickedButtonSignleRecovery)
	ON_BN_CLICKED(IDC_BUTTON_BASE64_RECOVERY, &CConversionToolDlg::OnBnClickedButtonBase64Recovery)
END_MESSAGE_MAP()


// CConversionToolDlg message handlers

BOOL CConversionToolDlg::OnInitDialog()
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

void CConversionToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CConversionToolDlg::OnPaint()
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
HCURSOR CConversionToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CConversionToolDlg::OnBnClickedButtonConversion()
{
	// TODO: Add your control notification handler code here

	originContent.GetWindowTextW(orgin);
	url = Tool::urlEncode(orgin);
	sql = Tool::sqlEncode(orgin);
	hex = Tool::hexEncode(orgin);
	ascii = Tool::asciiEncode(orgin);
	md532 = Tool::md5Encode(orgin);
	md516 = md532.Mid(8,16);
	base64 = Tool::base64Encode(orgin);
	base64Recovery = " ";

	urlContent.SetWindowTextW(url);
	sqlContent.SetWindowTextW(sql);
	hexContent.SetWindowTextW(hex);
	asciiContent.SetWindowTextW(ascii);
	md532Content.SetWindowTextW(md532);
	md516Content.SetWindowTextW(md516);
	base64Content.SetWindowTextW(base64);
	base64RecoveryContent.SetWindowTextW(base64Recovery);


}


void CConversionToolDlg::OnBnClickedButtonUrlRecovery()
{
	// TODO: Add your control notification handler code here
	urlContent.GetWindowTextW(url);
	urlContent.SetWindowTextW(Tool::urlDecode(url));
}


void CConversionToolDlg::OnBnClickedButtonSqlRecovery()
{
	// TODO: Add your control notification handler code here
	sqlContent.GetWindowTextW(sql);
	sqlContent.SetWindowTextW(Tool::sqlDecode(sql));

}


void CConversionToolDlg::OnBnClickedButtonHexRecovery()
{
	// TODO: Add your control notification handler code here
	hexContent.GetWindowTextW(hex);
	hexContent.SetWindowTextW(Tool::hexDecode(hex));
}


void CConversionToolDlg::OnBnClickedButtonSignleRecovery()
{
	// TODO: Add your control notification handler code here
	asciiContent.GetWindowTextW(ascii);
	asciiContent.SetWindowTextW(Tool::asciiDecode(ascii));
}


void CConversionToolDlg::OnBnClickedButtonBase64Recovery()
{
	// TODO: Add your control notification handler code here
	base64Content.GetWindowTextW(base64Recovery);
	base64RecoveryContent.SetWindowTextW(Tool::base64Decode(base64Recovery));

}


