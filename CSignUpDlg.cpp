// CSignUpDlg.cpp: 实现文件
//

#include "pch.h"
#include "ChatRoom_Client.h"
#include "afxdialogex.h"
#include "CSignUpDlg.h"


// CSignUpDlg 对话框

IMPLEMENT_DYNAMIC(CSignUpDlg, CDialogEx)

CSignUpDlg::CSignUpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIGNUP_DIALOG, pParent)
{

}

CSignUpDlg::~CSignUpDlg()
{
}

void CSignUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SIGNUP_USERNAME, m_user);
}


BEGIN_MESSAGE_MAP(CSignUpDlg, CDialogEx)
	ON_BN_CLICKED(ID_SIGNUP_CONFIRM, &CSignUpDlg::OnBnClickedSignupConfirm)
END_MESSAGE_MAP()


// CSignUpDlg 消息处理程序


void CSignUpDlg::OnBnClickedSignupConfirm()
{
	// TODO: 在此添加控件通知处理程序代码
}
