// CServerSettingDlg.cpp: 实现文件
//

#include "pch.h"
#include "ChatRoom_Client.h"
#include "afxdialogex.h"
#include "CServerSettingDlg.h"


// CServerSettingDlg 对话框

IMPLEMENT_DYNAMIC(CServerSettingDlg, CDialogEx)

CServerSettingDlg::CServerSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVER_SETTING_DIALOG, pParent)
{

}

CServerSettingDlg::~CServerSettingDlg()
{
}

void CServerSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CServerSettingDlg, CDialogEx)
END_MESSAGE_MAP()


// CServerSettingDlg 消息处理程序
