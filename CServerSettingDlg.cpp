// CServerSettingDlg.cpp: 实现文件
//

#include "pch.h"
#include "ChatRoom_ClientDlg.h"
#include "ChatRoom_Client.h"
#include "afxdialogex.h"
#include "CServerSettingDlg.h"


// CServerSettingDlg 对话框

IMPLEMENT_DYNAMIC(CServerSettingDlg, CDialogEx)

CServerSettingDlg::CServerSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVER_SETTING_DIALOG, pParent)
	, m_port(_T(""))
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
	DDX_Control(pDX, IDC_PASSWD, m_password);
	DDX_Text(pDX, IDC_PORT, m_port);
	//  DDX_IPAddress(pDX, IDC_IPADDRESS, m_ip);
	//  DDX_Control(pDX, IDC_IPADDRESS, m_ip);
}


BEGIN_MESSAGE_MAP(CServerSettingDlg, CDialogEx)
	ON_BN_CLICKED(ID_CONNECT_APPLY, &CServerSettingDlg::OnBnClickedConnectApply)
	ON_BN_CLICKED(ID_CONNECT_TEST, &CServerSettingDlg::OnBnClickedConnectTest)
END_MESSAGE_MAP()


// CServerSettingDlg 消息处理程序


void CServerSettingDlg::OnBnClickedConnectApply()
{
	// 应用并返回
	UpdateData(true);
	GetDlgItemText(IDC_IPADDRESS, m_ip);
	
	CServerSettingDlg::ShowWindow(SW_HIDE);
	HWND parhwnd = GetParent()->m_hWnd;//取得父窗口句柄
	::SendMessage(parhwnd, WM_CONNECT, NULL, NULL);//向父窗口发消息
}


BOOL CServerSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CServerSettingDlg::OnBnClickedConnectTest()
{
	// 测试服务器设置是否有效

	UpdateData(true);
}
