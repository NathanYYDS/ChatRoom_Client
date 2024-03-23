
// ChatRoom_ClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "stdio.h"
#include "framework.h"
#include "ChatRoom_Client.h"
#include "ChatRoom_ClientDlg.h"
#include "afxdialogex.h"
#include "CServerSettingDlg.h"
#include "CSignUpDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatRoomClientDlg 对话框



CChatRoomClientDlg::CChatRoomClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATROOM_CLIENT_DIALOG, pParent)
	, m_text_send(_T(""))
	, m_username(_T(""))
	, m_password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatRoomClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT_SEND, m_text_send);
	DDX_Text(pDX, IDC_USERNAME, m_username);
	DDV_MaxChars(pDX, m_username, 15);
	DDX_Text(pDX, IDC_PASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, 20);
}

BEGIN_MESSAGE_MAP(CChatRoomClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CChatRoomClientDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_SERVER_SETTING, &CChatRoomClientDlg::OnBnClickedServerSetting)
	ON_BN_CLICKED(IDC_SIGNUP, &CChatRoomClientDlg::OnBnClickedSignup)
	ON_BN_CLICKED(IDC_SIGNIN, &CChatRoomClientDlg::OnBnClickedSignin)
	ON_MESSAGE(WM_CONNECT,&CChatRoomClientDlg::OnConnect)
END_MESSAGE_MAP()


// CChatRoomClientDlg 消息处理程序

BOOL CChatRoomClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	ServerSettingDlg.Create(IDD_SERVER_SETTING_DIALOG, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatRoomClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChatRoomClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 发送按钮功能实现
void CChatRoomClientDlg::OnBnClickedSend()
{
	UpdateData(true);//更新控件中数据到关联变量
	//MessageBox(m_text_send);
}


//服务器设置按钮功能实现
void CChatRoomClientDlg::OnBnClickedServerSetting()
{
	ServerSettingDlg.ShowWindow(SW_SHOW);//弹出非模态对话框
	//MessageBox(ServerSettingDlg.m_ip);
}


//注册按钮功能实现
void CChatRoomClientDlg::OnBnClickedSignup()
{
	CSignUpDlg SignUpDlg;
	SignUpDlg.DoModal();//弹出模态对话框
}


void CChatRoomClientDlg::OnBnClickedSignin()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取账号和密码框的数据
	UpdateData(true);

	// 测试数据是否获取成功
	//MessageBox(m_username);
	//MessageBox(m_password);

	//检查账号密码合法性
	if (!CheckUsername(m_username))
	{
		MessageBox(L"账号字符串非法");
	}
	if (!CheckPassword(m_password))
	{
		MessageBox(L"密码字符串非法");
	}
}


//检查账号合法性
bool CChatRoomClientDlg::CheckUsername(CString s)
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
bool CChatRoomClientDlg::CheckPassword(CString s)
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


afx_msg LRESULT CChatRoomClientDlg::OnConnect(WPARAM wParam, LPARAM lParam)
{
	//连接服务器

	return true;
}