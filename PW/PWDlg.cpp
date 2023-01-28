
// PWDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "PW.h"
#include "PWDlg.h"
#include "afxdialogex.h"
#include <vector>
#include "Settings.h"

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


// CPWDlg dialog



CPWDlg::CPWDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPWDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_sec);
	DDX_Control(pDX, IDC_EDIT1, m_newname);
	DDX_Control(pDX, IDC_LIST1, m_pl);
	DDX_Control(pDX, IDC_BUTTON1, m_ap);
	DDX_Control(pDX, IDC_BUTTON2, m_dp);
	DDX_Control(pDX, IDC_BUTTON3, m_hide);
	DDX_Control(pDX, IDC_BUTTON4, m_exit);
}

BEGIN_MESSAGE_MAP(CPWDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON4, &CPWDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CPWDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPWDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPWDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CPWDlg message handlers

BOOL CPWDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	Preparing();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPWDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPWDlg::OnPaint()
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
HCURSOR CPWDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPWDlg::OnBnClickedButton4()
{
	Exit();
	// TODO: Add your control notification handler code here
}


void CPWDlg::Clear()
{
	m_sec.SetWindowTextW(L"");
	m_newname.SetWindowTextW(L"");
	
}
void CPWDlg::DisapleALL()
{
	m_sec.EnableWindow(false);
	m_newname.EnableWindow(false);
	m_pl.EnableWindow(false);
	m_ap.EnableWindow(false);
	m_dp.EnableWindow(false);
	m_hide.EnableWindow(false);
	m_exit.EnableWindow(false);
	

}
void CPWDlg::AddProcess()
{
	CString name = 0;
	m_newname.GetWindowTextW(name);

	if (!(name.GetLength() > 0))
	{
		AfxMessageBox(L"OOPS, ENTER PROCESS NAME :(.", 0);
		return;
	}

	if ((name.GetLength() > 50))
	{
		AfxMessageBox(L"OOPS, ENTER CURRECT PROCESS NAME :(.", 0);
		return;
	}

	m_pl.AddString(name);
	m_pl.SetCurSel(m_pl.GetCount() - 1);
	m_newname.SetWindowTextW(L"");

}
void CPWDlg::DeleteProcess()
{
	int count = m_pl.GetCount();

	if (count > 0)
	{
		int index = 0;
		index = m_pl.GetCurSel();
		m_pl.DeleteString(index);
	}
}
void CPWDlg::Hide()
{
	if (Save())
	{
		this->EndDialog(0);
	}

}
void CPWDlg::Exit() {
	
	//PostMessage(WM_CLOSE);
	exit(0);
}
bool CPWDlg::Save()
{
	CString tmp;
	unsigned sec = 0;
	unsigned int count = 0;
	std::vector<std::wstring> l;
	////////////////////////

	m_sec.GetWindowTextW(tmp);
	sec = _wtoi(tmp);

	if (!(sec > 0))
	{
		AfxMessageBox(L"OOPS, ENTER TIME IN SECOND :(.", 0);
		return false;
	}

	if ((sec > 99999))
	{
		AfxMessageBox(L"OOPS, SECOND VALUE INCORRECT :(.", 0);
		return false;
	}

	count = m_pl.GetCount();
	
	if (!(count > 0))
	{
		AfxMessageBox(L"ENTER PROCESS NAME :(.", 0);
		return false;
	}

	for (int i = 0; i < count; i++)
	{
		std::wstring n;
		m_pl.GetText(i, tmp);
		n = tmp.GetBuffer(tmp.GetLength());
		l.push_back(n);
	}

	Param p(sec, l);
	return p.SaveToDisk();
}

void CPWDlg::Preparing()
{
	int count=0;
	CString tmp = L"";
	//////////////////
	DisapleALL();
	Clear();

	Param p;
	
	tmp.Format(L"%d", p.Second());
	m_sec.SetWindowTextW(tmp);

	count = p.Processes().size();
	if (count > 0)
	{
		for (int i = 0; i < count; i++)
		{
			tmp = p.Processes()[i].data();
			CString pn(tmp);
			m_pl.AddString(pn);
		}
	}

	m_sec.EnableWindow(true);
	m_newname.EnableWindow(true);
	m_pl.EnableWindow(true);
	m_ap.EnableWindow(true);
	m_dp.EnableWindow(true);
	m_hide.EnableWindow(true);
	m_exit.EnableWindow(true);

}





void CPWDlg::OnBnClickedButton1()
{
	AddProcess();
	// TODO: Add your control notification handler code here
}


void CPWDlg::OnBnClickedButton2()
{
	DeleteProcess();
	// TODO: Add your control notification handler code here
}


void CPWDlg::OnBnClickedButton3()
{
	Hide();
	// TODO: Add your control notification handler code here
}
