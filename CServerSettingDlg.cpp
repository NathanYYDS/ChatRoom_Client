// CServerSettingDlg.cpp: 实现文件
//

#include "pch.h"
#include "ChatRoom_ClientDlg.h"
#include "ChatRoom_Client.h"
#include "afxdialogex.h"
#include "CServerSettingDlg.h"
#include "string.h"
//#include "iostream"

extern CChatRoomClientDlg* g_ChatRoomClientDlg;

// CServerSettingDlg 对话框

IMPLEMENT_DYNAMIC(CServerSettingDlg, CDialogEx)

CServerSettingDlg::CServerSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVER_SETTING_DIALOG, pParent)
	, m_port(_T(""))
	, m_password(_T(""))
{

	m_ip = _T("");
}

CServerSettingDlg::~CServerSettingDlg()
{
}

void CServerSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_IPADDRESS, m_ip);
	//  DDX_Control(pDX, IDC_PORT, m_port);
	//  DDX_Control(pDX, IDC_PASSWD, m_password);
	DDX_Text(pDX, IDC_PORT, m_port);
	//  DDX_IPAddress(pDX, IDC_IPADDRESS, m_ip);
	//  DDX_Control(pDX, IDC_IPADDRESS, m_ip);
	DDX_Text(pDX, IDC_PASSWD, m_password);
}


BEGIN_MESSAGE_MAP(CServerSettingDlg, CDialogEx)
	ON_BN_CLICKED(ID_CONNECT_APPLY, &CServerSettingDlg::OnBnClickedConnectApply)
	ON_BN_CLICKED(ID_CONNECT_TEST, &CServerSettingDlg::OnBnClickedConnectTest)
END_MESSAGE_MAP()


// CServerSettingDlg 消息处理程序

// 应用并返回
void CServerSettingDlg::OnBnClickedConnectApply()
{
	g_ChatRoomClientDlg->g_recvMessageThread = TRUE;
	//更新数据
	m_ip.Empty();
	UpdateData(true);
	GetDlgItemText(IDC_IPADDRESS, m_ip);

	//设置合法性检测
	if (!CheckSetting())
		return;

	//向主对话框发送可以连接的消息
	CServerSettingDlg::ShowWindow(SW_HIDE);
	HWND parhwnd = GetParent()->m_hWnd;//取得父窗口句柄
	g_ChatRoomClientDlg->g_recvMessageThread = FALSE;//启用线程循环
	::SendMessage(parhwnd, WM_CONNECT, NULL, NULL);//向父窗口发消息
}

//对话框初始化函数
BOOL CServerSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


//测试连接
void CServerSettingDlg::OnBnClickedConnectTest()
{
	// 获取并处理数据
	m_ip.Empty();
	UpdateData(true);
	GetDlgItemText(IDC_IPADDRESS, m_ip);

	//设置合法性检测
	if (!CheckSetting())
	{
		MessageBox("服务器设置不合法");
		return;
	}

	//初始化套接字
	g_ChatRoomClientDlg->clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	g_ChatRoomClientDlg->serverAddr.sin_family = AF_INET;
	g_ChatRoomClientDlg->serverAddr.sin_port = htons(atoi(m_port));
	inet_pton(AF_INET, m_ip.GetString(), &(g_ChatRoomClientDlg->serverAddr).sin_addr);

	//测试
	//MessageBox(m_ip.GetString());
	//MessageBox(m_port);

	// 创建一个新线程来接收服务器消息
    //thread receiveThread(receiveMessages, clientSocket);
	// 
	//设置连接超时
	//int connectTimeout = 30;
	//setsockopt(sock, IPPROTO_TCP, TCP_CONNECTIONTIMEOUT, (char*)&connectTimeout, sizeof(connectTimeout));

	// 连接到服务器
	if (connect(g_ChatRoomClientDlg->clientSocket, reinterpret_cast<sockaddr*>(&(g_ChatRoomClientDlg->serverAddr)), sizeof(g_ChatRoomClientDlg->serverAddr)) == SOCKET_ERROR)
	{
		MessageBox("Error connecting to server.");
		closesocket(g_ChatRoomClientDlg->clientSocket);
		return;
	}
	MessageBox("测试完成,连接正常");
	closesocket(g_ChatRoomClientDlg->clientSocket);
}


// 因为IP控件自带ip地址合法性检测，所以无需再次检测
//bool CServerSettingDlg::CheckIP(CString ip)
//{
	// TODO: 在此处添加实现代码.
	//MessageBox(*ip);
//	short len = ip.GetLength();
// ***************************************************************************
// CString与sscanf_s
//	char* s = (LPSTR)(LPCTSTR)ip;
//	short ipaddress[4] = {0};
//	sscanf_s(s, "%hd.%hd.%hd.%hd", &ipaddress[0], &ipaddress[1], &ipaddress[2], &ipaddress[3]);
// ****************************************************************************
//	if (ipaddress[0] <= 255 || ipaddress[1] <= 255 || ipaddress[2] <= 255 || ipaddress[3] <= 255)
//	{
//		MessageBox("IP地址不合法");
//		return false;
//	}
	//CString abcd;
	//abcd.Format("%hd+%hd+%hd+%hd", ipaddress[0], ipaddress[1], ipaddress[2], ipaddress[3]);
	//MessageBox(abcd);
//	return true;
//}



// 检查服务器设置合法性
bool CServerSettingDlg::CheckSetting()
{
	//判断是否为空
	if (m_ip == "0.0.0.0" || m_port.IsEmpty() || m_password.IsEmpty())
	{
		MessageBox("有必填项为空");
		return false;
	}

	//因为IP控件自带ip地址合法性检测，所以无需再次检测
	//CheckIP(m_ip);

	//端口合法性检测
	char* s = (LPSTR)(LPCTSTR)m_port;
	int len = m_port.GetLength();
	for (int i = 0; i < len; i++)
	{
		if (s[i] < '0' || s[i] > '9')
		{
			MessageBox("端口需为整数");
			return false;
		}
	}
	short port;
	sscanf_s(s, "%hd", &port);
	if (port < 1 || port > 65535)
	{
		MessageBox("端口号应在1~65536之间");
		return false;
	}


	//密码合法性检测
	if (!CChatRoomClientDlg::CheckPassword(m_password))
	{
		MessageBox("密码不合法");
		return false;
	}

	return true;
}
