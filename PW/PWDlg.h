
// PWDlg.h : header file
//

#pragma once


// CPWDlg dialog
class CPWDlg : public CDialogEx
{
// Construction
public:
	CPWDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PW_DIALOG };
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
private:
	CEdit m_sec;
	CEdit m_newname;
	CListBox m_pl;
	CButton m_ap;
	CButton m_dp;
	CButton m_hide;
	CButton m_exit;

public:
	afx_msg void OnBnClickedButton4();


private:
	void Clear();
	void DisapleALL();
	void AddProcess();
	void DeleteProcess();
	void Hide();
	void Exit();
	bool Save();
	void Preparing();

private:
	HANDLE hMutex{ 0 };
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
