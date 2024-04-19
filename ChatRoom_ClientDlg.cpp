
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
#include "thread"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// CChatRoomClientDlg 对话框

//定义对话框指针变量
CChatRoomClientDlg* g_ChatRoomClientDlg;


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
	DDX_Control(pDX, IDC_CONNECT_STATUS, m_ConnectStatus);
}

BEGIN_MESSAGE_MAP(CChatRoomClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CChatRoomClientDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_SERVER_SETTING, &CChatRoomClientDlg::OnBnClickedServerSetting)
	ON_BN_CLICKED(IDC_SIGNUP, &CChatRoomClientDlg::OnBnClickedSignup)
	ON_BN_CLICKED(IDC_SIGNIN, &CChatRoomClientDlg::OnBnClickedSignin)
	ON_MESSAGE(WM_CONNECT, &CChatRoomClientDlg::OnConnect)
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
	g_ChatRoomClientDlg = this;
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
	if (m_text_send.IsEmpty())
	{
		MessageBox("发送内容不可为空");
		return;
	}
	//MessageBox("Enter message: ");
	//getline(cin, message);
	send(clientSocket, m_text_send, m_text_send.GetLength(), 0); // 发送消息到服务器
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
		MessageBox("账号字符串非法");
		return;
	}
	if (!CheckPassword(m_password))
	{
		MessageBox("密码字符串非法");
		return;
	}
	if (connectStatus == TRUE)
	{
		CString login;
		login.Format("IIDD:%s", m_username);
		send(clientSocket, login, login.GetLength(), 0); // 发送消息到服务器
		return;
	}
	else 
	{
		MessageBox("未连接至服务器");
		return;
	}
	return;
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
	//TerminateThread(recvMessageThread.native_handle(),recvMessageThread.get_id())
	//连接服务器
	//初始化套接字
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(ServerSettingDlg.m_port));
	inet_pton(AF_INET, ServerSettingDlg.m_ip.GetString(), &(serverAddr).sin_addr);
	
	//设置连接超时
	//int connectTimeout = 30;
	//setsockopt(sock, IPPROTO_TCP, TCP_CONNECTIONTIMEOUT, (char*)&connectTimeout, sizeof(connectTimeout));
	
	if (connect(g_ChatRoomClientDlg->clientSocket, reinterpret_cast<sockaddr*>(&(g_ChatRoomClientDlg->serverAddr)), sizeof(g_ChatRoomClientDlg->serverAddr)) == SOCKET_ERROR)
	{
		MessageBox("Error connecting to server.");
		closesocket(g_ChatRoomClientDlg->clientSocket);
		connectStatus = FALSE;

		//修改服务器连接状态值 连接->断开
		m_ConnectStatus.SetWindowTextA("断开");

		return true;
	}
	MessageBox("正常连接至服务器");
	connectStatus = TRUE;

	//修改服务器连接状态值 断开->连接
	m_ConnectStatus.SetWindowTextA("连接");

	//closesocket(g_ChatRoomClientDlg->clientSocket);

	//创建接收服务器消息的线程
	AfxBeginThread((AFX_THREADPROC)receiveMessages, (LPVOID)this);
	return true;
}

BOOL CChatRoomClientDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	g_recvMessageThread = TRUE;
	closesocket(g_ChatRoomClientDlg->clientSocket);
	WSACleanup();
	return CDialogEx::DestroyWindow();
}


// 接收服务器消息的线程函数
DWORD WINAPI CChatRoomClientDlg::receiveMessages(PVOID param)
{
	char buffer[102400]; // 用于接收消息的缓冲区
	int bytesReceived;
	while (g_ChatRoomClientDlg->g_recvMessageThread == FALSE)
	{
		// 接收服务器消息
		bytesReceived = recv(g_ChatRoomClientDlg->clientSocket, buffer, sizeof(buffer), 0);

		// 如果接收到的字节数小于等于0，表示与服务器断开连接
		if (bytesReceived <= 0)
		{
			g_ChatRoomClientDlg->MessageBox("Disconnected from server.");
			g_ChatRoomClientDlg->g_recvMessageThread = TRUE;
			break;
		}

		//溢出漏洞---------------------------------溢出漏洞----------------------------------溢出漏洞
		buffer[bytesReceived] = '\0'; // 添加字符串结束符
		//溢出漏洞---------------------------------溢出漏洞----------------------------------溢出漏洞

		//将下一条消息加入CString
		g_ChatRoomClientDlg->g_Message.Insert(g_ChatRoomClientDlg->g_Message.GetLength(), buffer);

		//添加消息间的换行符
		g_ChatRoomClientDlg->g_Message += "\r\n\r\n";

		//显示到窗口
		g_ChatRoomClientDlg->GetDlgItem(IDC_MESSAGE)->SetWindowText(g_ChatRoomClientDlg->g_Message);

		//将编辑框自动滚动到最下方
		g_ChatRoomClientDlg->SendDlgItemMessage(IDC_MESSAGE, WM_VSCROLL, SB_BOTTOM, 0);
	}
	closesocket(g_ChatRoomClientDlg->clientSocket);
	g_ChatRoomClientDlg->connectStatus = FALSE;
	return 0;
}


