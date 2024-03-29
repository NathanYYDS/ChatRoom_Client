﻿
// ChatRoom_ClientDlg.h: 头文件
//

#pragma once

#define WM_CONNECT (WM_USER+100)

#include "CServerSettingDlg.h"

// CChatRoomClientDlg 对话框
class CChatRoomClientDlg : public CDialogEx
{
// 构造
public:
	CChatRoomClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATROOM_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnConnect(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedSend();
	// 将要发出的信息字符串
	CString m_text_send;
	// 用户名（最长15个字符）
	CString m_username;
	// 密码（最长20个字符）
	CString m_password;
	afx_msg void OnBnClickedServerSetting();
	afx_msg void OnBnClickedSignup();
	afx_msg void OnBnClickedSignin();
	// // 检查账号字符串是否合法
//	static bool CheckUsername(Cstring* p);
//	static bool CheckUsername(CString* s);
	static bool CheckUsername(CString s);
	static bool CheckPassword(CString s);
private:
	CServerSettingDlg ServerSettingDlg;
};
