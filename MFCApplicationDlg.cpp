
// MFCApplicationDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication.h"
#include "MFCApplicationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplicationDlg 对话框



CMFCApplicationDlg::CMFCApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_POS, m_editPos);
	DDX_Control(pDX, IDC_EDIT_DATA, m_editData);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BUTTON_INSERT, m_btnInsert);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_btnSearch);
}

BEGIN_MESSAGE_MAP(CMFCApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMFCApplicationDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CMFCApplicationDlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMFCApplicationDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CMFCApplicationDlg::OnBnClickedButtonSearch)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCApplicationDlg 消息处理程序

BOOL CMFCApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	m_editPos.SetFocus();
	// TODO: 在此添加额外的初始化代码

	m_linkListCtrl.Initialize(this, &m_linkList, &m_linkListDraw);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplicationDlg::OnPaint()
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
		CPaintDC dc(this);
		m_linkListCtrl.Draw(&dc); // 调用控制器的绘制方法
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CMFCApplicationDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strPos;
    m_editPos.GetWindowText(strPos);  // 获取插入位置
    int vPos = _ttoi(strPos);  // 转换为整数

    CString strData;
    m_editData.GetWindowText(strData);  // 获取节点数据

    CPoint vPoint(0, 100);  // 假设一个默认点

    // 调用 InsertNode 来根据插入位置插入节点
    m_linkListCtrl.AddNode(vPoint,strData);
}


void CMFCApplicationDlg::OnBnClickedButtonInsert()
{
	CString strPos, strData;
	m_editPos.GetWindowText(strPos);
	m_editData.GetWindowText(strData);

	// 获取位置和数据
	int pos = _ttoi(strPos);
	if (strData.IsEmpty() || pos < 0)
	{
		AfxMessageBox(_T("请输入有效的位置和数据"));
		return;
	}

	// 设置节点位置
	CPoint point(100 + pos * 100, 100);  // 假设每个节点的间距是100
	m_linkListCtrl.InsertNode(point, pos, strData);
}

void CMFCApplicationDlg::OnBnClickedButtonDelete()
{
	CString strPos;
	m_editPos.GetWindowText(strPos);

	// 获取用户输入的删除位置
	int pos = _ttoi(strPos);
	if (pos < 0)
	{
		AfxMessageBox(_T("请输入有效的位置"));
		return;
	}

	// 删除链表中指定位置的节点
	m_linkListCtrl.DeleteNode(pos);
}



void CMFCApplicationDlg::OnBnClickedButtonSearch()
{
	CString strData;
	m_editData.GetWindowText(strData);  // 获取输入的字符串
	CString strPos;
	m_editPos.GetWindowText(strPos);  // 获取要查找的节点位置
	int vPos = _ttoi(strPos);  // 将位置转换为整数
	if (strData.IsEmpty()) {
		AfxMessageBox(_T("请输入要查找的节点数据"));
		m_editData.SetFocus();  // 如果输入为空，设置输入框焦点
		return;
	}

	// 查找节点
	BOOL found = m_linkListCtrl.Search(strData,vPos);
	if (found) {
		AfxMessageBox(_T("节点已找到"));
		m_editData.SetFocus();  // 设置光标在搜索框
	}
	else {
		AfxMessageBox(_T("节点未找到"));
		m_editData.SetFocus();  // 设置光标在搜索框
	}
}




void CMFCApplicationDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1) {
		AfxMessageBox(_T("定时器触发"));  // 调试信息，确保定时器触发
		// 清除高亮状态的逻辑...
		// 定时器触发，清除所有节点的高亮状态
		CListNode* pCur = m_linkList.GetHead();
		while (pCur != nullptr) {
			pCur->highlight = false;  // 清除高亮状态
			pCur = pCur->pNext;
		}

		KillTimer(1);  // 停止定时器
		Invalidate();  // 触发重绘
	}
	CDialogEx::OnTimer(nIDEvent);
}
