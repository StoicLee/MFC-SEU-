
// MFCApplicationDlg.h: 头文件
//

#pragma once
#include "CLinkList.h"
#include "CLinkListDraw.h"
#include "CLinkListCtrl.h"


// CMFCApplicationDlg 对话框
class CMFCApplicationDlg : public CDialogEx
{
// 构造
public:
	CMFCApplicationDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION_DIALOG };
#endif

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
	DECLARE_MESSAGE_MAP()
private:
	CLinkList m_linkList;
	CLinkListDraw m_linkListDraw;
	CLinkListCtrl m_linkListCtrl;

	CEdit m_editPos;
	CEdit m_editData;
	CButton m_btnAdd;
	CButton m_btnInsert;
	CButton m_btnDelete;
	CButton m_btnSearch;
public:

	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
