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
        // ��ȡ��ǰ����ڵ�������̬�����½ڵ��λ��
        int nodeCount = m_pLinkList->GetCount();
        int spacing = 120;

        // ��̬�����½ڵ��λ��
        vPoint.x = 100 + nodeCount * spacing;  // ���������ȵ���X����
        vPoint.y = 100;  // Y�ᱣ�̶ֹ�

        // ���������AddNode��������β�巨����
        m_pLinkList->AddNode(vPoint, vString);

        // ȷ�������ػ�����ʾ���º������
        m_pParentWnd->Invalidate();  // �����ػ�
    }
}



void CLinkListCtrl::InsertNode(CPoint vPoint, int vPos, CString vString) {
    if (m_pLinkList) {
        int nodeCount = m_pLinkList->GetCount();
        int spacing = 120;  // ���ø���Ľڵ���Ϊ120����

        // �жϲ���λ���Ƿ���Ч
        if (vPos < 0 || vPos > nodeCount) {
            AfxMessageBox(_T("��Ч�Ĳ���λ��"));
            return;
        }

        // ���²���λ�ú�����нڵ�λ��
        CListNode* pCur = m_pLinkList->GetHead();
        int index = 0;
        while (pCur != nullptr) {
            if (index >= vPos) {
                pCur->point.x += spacing;  // �������в���λ�ú�Ľڵ�
            }
            pCur = pCur->pNext;
            index++;
        }

        // �����½ڵ�
        vPoint.x = 100 + vPos * spacing;  // �½ڵ��λ��
        vPoint.y = 100;  // Y��̶�
        m_pLinkList->InsertNode(vPoint, vPos, vString);

        // ȷ���������»���
        m_pParentWnd->Invalidate();  // �����ػ�
    }
}



void CLinkListCtrl::DeleteNode(int vPos)
{
    if (m_pLinkList)
    {
        m_pLinkList->DeleteNode(vPos);
        m_pParentWnd->Invalidate();  // �����ػ�
    }
}

BOOL CLinkListCtrl::Search(CString vString, int vPos) {
    if (m_pLinkList) {
        CListNode* pCur = m_pLinkList->GetHead();
        while (pCur != nullptr) {
            pCur->highlight = false;  // �������нڵ����״̬
            pCur = pCur->pNext;
        }

        // ����Ŀ��ڵ㲢���ø���
        pCur = m_pLinkList->GetHead();
        int index = 0;
        while (pCur != nullptr) {
            // ͬʱƥ�����ݺ�λ��
            if (pCur->data == vString && index == vPos) {
                CDC* pDC = m_pParentWnd->GetDC();
                CBrush highlightBrush(RGB(255, 0, 0));
                CBrush* pOldBrush = pDC->SelectObject(&highlightBrush);

                pDC->Ellipse(pCur->point.x - 15, pCur->point.y - 15, pCur->point.x + 15, pCur->point.y + 15);

                pDC->SelectObject(pOldBrush);
                pCur->highlight = true;  // ���ø���
                m_pParentWnd->ReleaseDC(pDC);

                // ���ö�ʱ�����ӳ��������״̬��3000����������3�룩
                m_pParentWnd->SetTimer(1, 30000, NULL);
                return TRUE;  // �ҵ�Ŀ��ڵ�
            }
            pCur = pCur->pNext;
            index++;
        }

        AfxMessageBox(_T("�ڵ�δ�ҵ�"));
        m_pParentWnd->Invalidate();  // ����ϴεĸ���
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
