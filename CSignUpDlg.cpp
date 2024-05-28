// CSignUpDlg.cpp: 实现文件
//

#include "pch.h"
#include "ChatRoom_Client.h"
#include "ChatRoom_ClientDlg.h"
#include "afxdialogex.h"
#include "CSignUpDlg.h"
//
#include "stdio.h"
#include "framework.h"
#include "CServerSettingDlg.h"
#include "thread"

extern CChatRoomClientDlg* g_ChatRoomClientDlg;

// CSignUpDlg 对话框

IMPLEMENT_DYNAMIC(CSignUpDlg, CDialogEx)

CSignUpDlg::CSignUpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIGNUP_DIALOG, pParent)
	, m_user(_T(""))
	, m_pass2(_T(""))
	, m_pass1(_T(""))
{

}

CSignUpDlg::~CSignUpDlg()
{
}

void CSignUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SIGNUP_USERNAME, m_user);
	DDX_Text(pDX, IDC_SIGNUP_PASSWORD2, m_pass2);
	DDX_Text(pDX, IDC_SIGNUP_PASSWORD1, m_pass1);
}


BEGIN_MESSAGE_MAP(CSignUpDlg, CDialogEx)
	ON_BN_CLICKED(ID_SIGNUP_CONFIRM, &CSignUpDlg::OnBnClickedSignupConfirm)
END_MESSAGE_MAP()

// 用户名（最长15个字符）
CString m_Registerusername;
// 密码（最长20个字符）
CString m_Registerpassword;
//检查密码
CString m_checkRegisterpassword;
// CSignUpDlg 消息处理程序

//检查账号合法性
bool CheckUsername(CString s)
{
	short len = CStringA(s).GetLength();
	if (len == 0)
		return false;
	unsigned char c;
	for (int i = 0; i != len; i++)
	{
		c = s[i];
		if (!((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a') || (c <= '9' && c >= '0') || c == '_'))
			return false;
	}
	return true;
}


//检查密码合法性
bool CheckPassword(CString s)
{
	short len = CStringA(s).GetLength();
	if (len == 0)
		return false;
	unsigned char c;
	for (int i = 0; i != len; i++)
	{
		c = s[i];
		if (!((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9')
			|| (c >= 33 && c <= 47) //特殊字符
			|| (c >= 58 && c <= 64)
			|| (c >= 91 && c <= 96)
			|| (c >= 123 && c <= 126)))
			return false;
	}
	return true;
}

//注册功能
void CSignUpDlg::OnBnClickedSignupConfirm()
{
	char buffer[10240]; // 用于接收消息的缓冲区
	int bytesReceived;

	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); // 更新UI控件数据到成员变量

	//检查账号密码合法性
	if (!CheckUsername(m_user))
	{
		MessageBox("账号字符串非法");
		return;
	}
	if (!CheckPassword(m_pass1)|| !CheckPassword(m_pass2))
	{
		MessageBox("密码字符串非法");
		return;
	}

	//检查两次密码是否一致
	if (strcmp(m_pass1, m_pass2) != 0)
	{
		MessageBox("两次密码输入不一致");
		return;
	}
	else
	{
		// 构建请求字符串 ACTION|USERNAME|PASSWORD
		CString request = "REGISTER|" + m_user + "|" + m_pass1;

		// 等待并接收服务器响应
		char response[100];
		send(g_ChatRoomClientDlg->clientSocket, request, strlen(request), 0);

		// 接收服务器消息
//		bytesReceived = recv(g_ChatRoomClientDlg->clientSocket, buffer, sizeof(buffer), 0);

		//if (bytesReceived <= 0)
		//{
		//	MessageBox("请先连接至服务器");
		//}
		//else
		//{
		//	buffer[bytesReceived] = '\0';

		//	if (bytesReceived > 0 )
		//	{
		//		if (strcmp(buffer, "REGISTER_SUCCESS"))
		//		{
		//			MessageBox("注册成功");
		//		}
		//		else
		//		{
		//			sprintf_s(buffer, "注册失败，原因：%s", buffer);
		//			MessageBox(buffer);
		//		}
		//	}
		//}


		return;

	}


	closesocket(g_ChatRoomClientDlg->clientSocket);
}
