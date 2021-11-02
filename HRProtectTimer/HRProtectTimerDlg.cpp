
// HRProtectTimerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "HRProtectTimer.h"
#include "HRProtectTimerDlg.h"

#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHRProtectTimerDlg 对话框



CHRProtectTimerDlg::CHRProtectTimerDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_HRPROTECTTIMER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHRProtectTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHRProtectTimerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CHRProtectTimerDlg::OnBnClickedGenerate)
END_MESSAGE_MAP()


// CHRProtectTimerDlg 消息处理程序

BOOL CHRProtectTimerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码
	CString str("1、在左边的第一个文本框输入你想要保护的天数，然后"
		"点击生成十六进制的数字，复制。\r\n2、使用火绒剑，打开“HKEY_LOCAL_MACHINE\\"
		"SOFTWARE\\Huorong\\Sysdiag\\app”找到“InstallTime”，然后将复制到的数据填进去，保存（火绒剑默认输入的数据为16进制）。\r\n"
		"3、重启火绒就能见到效果了！");
	SetDlgItemTextW(IDC_EDIT3, str);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHRProtectTimerDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHRProtectTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHRProtectTimerDlg::OnBnClickedGenerate()
{	
	time_t ttime;
	time(&ttime);
	UINT protime = GetDlgItemInt(IDC_EDIT1);
	if (protime<=0)
	{
		MessageBoxW(TEXT("时间必须为正整数！"), TEXT("提示"), MB_ICONEXCLAMATION);
		return;
	}
	ttime -=(protime-1) * static_cast<time_t>(24 * 60 * 60);
	CHAR buffer[10];
	sprintf_s(buffer, sizeof(buffer), "%llx",ttime);
	SetDlgItemTextW(IDC_EDIT2, CString(buffer));	
}