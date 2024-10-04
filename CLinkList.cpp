#include "pch.h"
#include "CLinkList.h"
#include "afxwin.h"

void CLinkList::AddNode(CPoint vPoint, CString vString) {
    CListNode* newNode = new CListNode(vPoint, vString);

    // �������Ϊ�գ�����Ϊͷ��β�ڵ�
    if (m_pHead == nullptr) {
        m_pHead = newNode;
        m_pTail = newNode;
    }
    else {
        // ��ӵ�β��
        m_pTail->pNext = newNode;
        m_pTail = newNode;
    }
    m_count++;
    UpdateNodePositions();  // �������нڵ��λ��
}

void CLinkList::InsertNode(CPoint vPoint, int vPos, CString vString) {
    if (vPos < 0 || vPos > m_count) {
        AfxMessageBox(_T("��Ч�Ĳ���λ��"));
        return;
    }

    CListNode* newNode = new CListNode(vPoint, vString);  // �����½ڵ�

    if (vPos == 0) {
        // ���뵽����ͷ��
        newNode->pNext = m_pHead;
        m_pHead = newNode;
        if (m_pTail == nullptr) m_pTail = newNode;  // �������Ϊ�գ�����βָ��
    }
    else {
        // ���뵽������ָ����λ��
        CListNode* pCur = m_pHead;
        for (int i = 0; i < vPos - 1; i++) {
            pCur = pCur->pNext;
        }
        newNode->pNext = pCur->pNext;
        pCur->pNext = newNode;
        if (newNode->pNext == nullptr) m_pTail = newNode;  // ������뵽β��������βָ��
    }

    m_count++;  // ��������ڵ����
    UpdateNodePositions();  // �����������нڵ��λ��
}


void CLinkList::DeleteNode(int vPos) {
    if (vPos < 0 || vPos >= m_count) {
        AfxMessageBox(_T("��Ч��ɾ��λ��"));
        return;
    }

    CListNode* pCur = m_pHead;
    if (vPos == 0) {
        // ɾ��ͷ�ڵ�
        m_pHead = m_pHead->pNext;
        delete pCur;
        if (m_pHead == nullptr) {
            m_pTail = nullptr;
        }
    }
    else {
        // �ҵ�ǰһ���ڵ㲢����Ҫɾ���Ľڵ�
        CListNode* pPrev = nullptr;
        for (int i = 0; i < vPos; ++i) {
            pPrev = pCur;
            pCur = pCur->pNext;
        }
        pPrev->pNext = pCur->pNext;
        if (pCur->pNext == nullptr) {
            m_pTail = pPrev;
        }
        delete pCur;
    }
    m_count--;
    UpdateNodePositions();  // ɾ�������ʣ��ڵ��λ��
}

BOOL CLinkList::Search(CString vString) const {
    CListNode* pCur = m_pHead;
    while (pCur != nullptr) {
        if (pCur->data == vString) {
            return TRUE;  // �ҵ�Ŀ��ڵ�
        }
        pCur = pCur->pNext;
    }
    return FALSE;  // û���ҵ�
}

void CLinkList::UpdateNodePositions() {
    // �������нڵ��λ�ã����Ϊ100
    CListNode* pCur = m_pHead;
    int index = 0;
    while (pCur != nullptr) {
        pCur->point.x = 100 + index * 100;
        pCur = pCur->pNext;
        index++;
    }
}
