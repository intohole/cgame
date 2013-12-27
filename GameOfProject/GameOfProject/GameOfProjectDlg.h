// GameOfProjectDlg.h : 头文件
//

#pragma once
#include "gamefather.h"
#include "MYIniReadTools.h"
#include "StructSet.h"
#include "afxwin.h"
// CGameOfProjectDlg 对话框
class CGameOfProjectDlg : public CDialog
{
// 构造
public:
	CGameOfProjectDlg(CWnd* pParent = NULL);	// 标准构造函数.h

// 对话框数据
	enum { IDD = IDD_GAMEOFPROJECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	CGameFather *gameFather;
	BOOL bPause;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedPauseButton();
	afx_msg void OnBnClickedEndButton();
	afx_msg void OnBnClickedStartButton();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedRestartButton();
	afx_msg void OnCbnSelchangeCombo1();

	void InitGameFather();



private:
	void switchGame(CString str);
	void InitChoice(vector<CString> vSave);
	CString m_strScore;
	MYIniReadTools *iniRead;
public:
	CComboBox m_GameListBox;

};
