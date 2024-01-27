#pragma once
#include "afxdialogex.h"


// CServerSettingDlg 对话框

class CServerSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CServerSettingDlg)

public:
	CServerSettingDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CServerSettingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER_SETTING_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
