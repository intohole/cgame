// GameOfProjectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GameOfProject.h"
#include "GameOfProjectDlg.h"
#include "GameSnake.h"
#include "GameFlyControl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "ManToHellControl.h"
#include "SeaWarControl.h"
#include "GameTools.h"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGameOfProjectDlg 对话框




CGameOfProjectDlg::CGameOfProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameOfProjectDlg::IDD, pParent)
	, m_strScore(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGameOfProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SCORE_EDIT, m_strScore);
	DDX_Control(pDX, IDC_COMBO1, m_GameListBox);

}

BEGIN_MESSAGE_MAP(CGameOfProjectDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_PAUSE_BUTTON, &CGameOfProjectDlg::OnBnClickedPauseButton)
	ON_BN_CLICKED(IDC_END_BUTTON, &CGameOfProjectDlg::OnBnClickedEndButton)
	ON_BN_CLICKED(IDC_START_BUTTON, &CGameOfProjectDlg::OnBnClickedStartButton)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_RESTART_BUTTON, &CGameOfProjectDlg::OnBnClickedRestartButton)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CGameOfProjectDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CGameOfProjectDlg 消息处理程序

BOOL CGameOfProjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	gameFather = NULL;
	CString strPathName ="" ;
	strPathName = CGameTools::GetIniPathName() +"11.ini";
	iniRead=new MYIniReadTools(strPathName);
	vector<CString> vSave;
	iniRead->GetAllSection(vSave);
	InitChoice(vSave);
	InitGameFather();
	vector<INIKEYINFO> vIni;
	iniRead->GetAllValueAndKey("123",vIni);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGameOfProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGameOfProjectDlg::OnPaint()
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
		CDC *pDc=GetDC();
		
		gameFather->GameOnPaint(pDc);
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGameOfProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGameOfProjectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	gameFather->GameOnLButtonDown(nFlags,point);
	

	CDialog::OnLButtonDown(nFlags, point);
}

// void CGameOfProjectDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
// {
// 	// TODO: 在此添加消息处理程序代码和/或调用默认值
// 	
// 	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
// }

void CGameOfProjectDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//Invalidate(false);
	if(gameFather->OnGameTimer(nIDEvent)==-2)
	{
		MessageBox("努力吧！！！！！","提示",MB_OK);
	}
	gameFather->SetScore(m_strScore);
	UpdateData(FALSE);
	
	CDialog::OnTimer(nIDEvent);
}

void CGameOfProjectDlg::OnBnClickedButton1()
{
	
	
	// TODO: 在此添加控件通知处理程序代码
}

void CGameOfProjectDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	gameFather->GameOnKeyDown(nChar,nRepCnt,nFlags);
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}
BOOL CGameOfProjectDlg::PreTranslateMessage(MSG* pMsg)
{
	gameFather->PreTranslateMessage(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}
void CGameOfProjectDlg::OnBnClickedPauseButton()
{
	// TODO: 在此添加控件通知处理程序代码
	bPause=!bPause;
	if (!bPause)
	{
		GetDlgItem(IDC_PAUSE_BUTTON)->SetWindowText("继续");
	}
	else
	{
		GetDlgItem(IDC_PAUSE_BUTTON)->SetWindowText("暂停");
	}
	gameFather->PauseGame(bPause);
}

void CGameOfProjectDlg::OnBnClickedEndButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

void CGameOfProjectDlg::OnBnClickedStartButton()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_START_BUTTON)->EnableWindow(FALSE);
	Sleep(3000);
	gameFather->StartGame();
}

void CGameOfProjectDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	gameFather->GameOnLButtonUp(nFlags,point);
	CDialog::OnLButtonUp(nFlags, point);
}

void CGameOfProjectDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	gameFather->GameOnMouseMove(nFlags,point);
	CDialog::OnMouseMove(nFlags, point);
}

void CGameOfProjectDlg::OnBnClickedRestartButton()
{
	// TODO: 在此添加控件通知处理程序代码
	
	gameFather->ReStartGame();
}

void CGameOfProjectDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CString str;
	m_GameListBox.GetLBText(m_GameListBox.GetCurSel(),str);
	switchGame(str);
	InitGameFather();
	Invalidate(FALSE);
}
void CGameOfProjectDlg::InitChoice(vector<CString> vSave)
{
	m_GameListBox.ResetContent();
	for (int i=0;i<vSave.size();i++)
	{
		m_GameListBox.AddString(vSave[i]);
	}
	m_GameListBox.SetCurSel(0);
	CString str;
	m_GameListBox.GetLBText(0,str);
	switchGame(str);
}
void CGameOfProjectDlg::switchGame(CString str)
{
	if (gameFather!=NULL)
	{
		gameFather->KillAllTimer();
		delete gameFather;
		gameFather = NULL;
	}
	GetDlgItem(IDC_START_BUTTON)->EnableWindow(TRUE);
	ShowCursor(TRUE);
	if (str.CompareNoCase("贪吃蛇")==0)
	{
		gameFather = new CGameSnake;
	
		return ;
	}
	if (str.CompareNoCase("男人就下100s")==0)
	{
		gameFather=new CManToHellControl;
		return ;
	}
	if (str.CompareNoCase("潜艇大战") == 0)
	{
		gameFather = new CSeaWarControl; 
		return;
	}
	if (str.CompareNoCase("小鸟快飞")==0)
	{
		gameFather = new CGameFlyControl;
		return;
	}

	MessageBox("配置文件出错!","提示",MB_OK);

}
void CGameOfProjectDlg::InitGameFather() 
{
	CDC *pDc=GetDC();
	gameFather->SetCDC(pDc);
	gameFather->SetHWnd(m_hWnd);
	m_strScore="";
	gameFather->SetScore(m_strScore);
	gameFather->SetGameBkColor(RGB(40,150,40));
	// TODO: 在此添加额外的初始化代码
	bPause=FALSE;
}
