#pragma once
#include "afxdialogex.h"


// CSignUpDlg 对话框

class CSignUpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSignUpDlg)

public:
	CSignUpDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSignUpDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIGNUP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
