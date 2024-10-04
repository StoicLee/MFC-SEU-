#include "pch.h"
#include "CLinkListCtrl.h"
#include "MFCApplicationDlg.h"
// CLinkListCtrl.cpp

CLinkListCtrl::CLinkListCtrl()
    : m_pLinkList(nullptr), m_pLinkListDraw(nullptr), m_pParentWnd(nullptr)
{
}

CLinkListCtrl::~CLinkListCtrl()
{
}

void CLinkListCtrl::Initialize(CWnd* pParentWnd, CLinkList* pLinkList, CLinkListDraw* pLinkListDraw)
{
    m_pParentWnd = pParentWnd;
    m_pLinkList = pLinkList;
    m_pLinkListDraw = pLinkListDraw;
}


void CLinkListCtrl::AddNode(CPoint vPoint, CString vString) {
    if (m_pLinkList) {
        // 获取当前链表节点数，动态计算新节点的位置
        int nodeCount = m_pLinkList->GetCount();
        int spacing = 120;

        // 动态计算新节点的位置
        vPoint.x = 100 + nodeCount * spacing;  // 根据链表长度调整X坐标
        vPoint.y = 100;  // Y轴保持固定

        // 调用链表的AddNode方法进行尾插法操作
        m_pLinkList->AddNode(vPoint, vString);

        // 确保窗口重绘以显示更新后的链表
        m_pParentWnd->Invalidate();  // 触发重绘
    }
}



void CLinkListCtrl::InsertNode(CPoint vPoint, int vPos, CString vString) {
    if (m_pLinkList) {
        int nodeCount = m_pLinkList->GetCount();
        int spacing = 120;  // 设置更大的节点间距为120像素

        // 判断插入位置是否有效
        if (vPos < 0 || vPos > nodeCount) {
            AfxMessageBox(_T("无效的插入位置"));
            return;
        }

        // 更新插入位置后的所有节点位置
        CListNode* pCur = m_pLinkList->GetHead();
        int index = 0;
        while (pCur != nullptr) {
            if (index >= vPos) {
                pCur->point.x += spacing;  // 后移所有插入位置后的节点
            }
            pCur = pCur->pNext;
            index++;
        }

        // 插入新节点
        vPoint.x = 100 + vPos * spacing;  // 新节点的位置
        vPoint.y = 100;  // Y轴固定
        m_pLinkList->InsertNode(vPoint, vPos, vString);

        // 确保窗口重新绘制
        m_pParentWnd->Invalidate();  // 触发重绘
    }
}



void CLinkListCtrl::DeleteNode(int vPos)
{
    if (m_pLinkList)
    {
        m_pLinkList->DeleteNode(vPos);
        m_pParentWnd->Invalidate();  // 触发重绘
    }
}

BOOL CLinkListCtrl::Search(CString vString, int vPos) {
    if (m_pLinkList) {
        CListNode* pCur = m_pLinkList->GetHead();
        while (pCur != nullptr) {
            pCur->highlight = false;  // 重置所有节点高亮状态
            pCur = pCur->pNext;
        }

        // 查找目标节点并设置高亮
        pCur = m_pLinkList->GetHead();
        int index = 0;
        while (pCur != nullptr) {
            // 同时匹配数据和位置
            if (pCur->data == vString && index == vPos) {
                CDC* pDC = m_pParentWnd->GetDC();
                CBrush highlightBrush(RGB(255, 0, 0));
                CBrush* pOldBrush = pDC->SelectObject(&highlightBrush);

                pDC->Ellipse(pCur->point.x - 15, pCur->point.y - 15, pCur->point.x + 15, pCur->point.y + 15);

                pDC->SelectObject(pOldBrush);
                pCur->highlight = true;  // 设置高亮
                m_pParentWnd->ReleaseDC(pDC);

                // 设置定时器，延迟清除高亮状态，3000毫秒后清除（3秒）
                m_pParentWnd->SetTimer(1, 30000, NULL);
                return TRUE;  // 找到目标节点
            }
            pCur = pCur->pNext;
            index++;
        }

        AfxMessageBox(_T("节点未找到"));
        m_pParentWnd->Invalidate();  // 清除上次的高亮
    }
    return FALSE;
   
}



void CLinkListCtrl::Draw(CDC* pDC)
{
    if (m_pLinkListDraw && m_pLinkList)
    {
        m_pLinkListDraw->DrawLinkList(pDC, *m_pLinkList);
    }
}
