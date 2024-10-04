#include "pch.h"
#include "CLinkList.h"
#include "afxwin.h"

void CLinkList::AddNode(CPoint vPoint, CString vString) {
    CListNode* newNode = new CListNode(vPoint, vString);

    // 如果链表为空，设置为头和尾节点
    if (m_pHead == nullptr) {
        m_pHead = newNode;
        m_pTail = newNode;
    }
    else {
        // 添加到尾部
        m_pTail->pNext = newNode;
        m_pTail = newNode;
    }
    m_count++;
    UpdateNodePositions();  // 更新所有节点的位置
}

void CLinkList::InsertNode(CPoint vPoint, int vPos, CString vString) {
    if (vPos < 0 || vPos > m_count) {
        AfxMessageBox(_T("无效的插入位置"));
        return;
    }

    CListNode* newNode = new CListNode(vPoint, vString);  // 创建新节点

    if (vPos == 0) {
        // 插入到链表头部
        newNode->pNext = m_pHead;
        m_pHead = newNode;
        if (m_pTail == nullptr) m_pTail = newNode;  // 如果链表为空，更新尾指针
    }
    else {
        // 插入到链表中指定的位置
        CListNode* pCur = m_pHead;
        for (int i = 0; i < vPos - 1; i++) {
            pCur = pCur->pNext;
        }
        newNode->pNext = pCur->pNext;
        pCur->pNext = newNode;
        if (newNode->pNext == nullptr) m_pTail = newNode;  // 如果插入到尾部，更新尾指针
    }

    m_count++;  // 更新链表节点计数
    UpdateNodePositions();  // 插入后更新所有节点的位置
}


void CLinkList::DeleteNode(int vPos) {
    if (vPos < 0 || vPos >= m_count) {
        AfxMessageBox(_T("无效的删除位置"));
        return;
    }

    CListNode* pCur = m_pHead;
    if (vPos == 0) {
        // 删除头节点
        m_pHead = m_pHead->pNext;
        delete pCur;
        if (m_pHead == nullptr) {
            m_pTail = nullptr;
        }
    }
    else {
        // 找到前一个节点并跳过要删除的节点
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
    UpdateNodePositions();  // 删除后更新剩余节点的位置
}

BOOL CLinkList::Search(CString vString) const {
    CListNode* pCur = m_pHead;
    while (pCur != nullptr) {
        if (pCur->data == vString) {
            return TRUE;  // 找到目标节点
        }
        pCur = pCur->pNext;
    }
    return FALSE;  // 没有找到
}

void CLinkList::UpdateNodePositions() {
    // 更新所有节点的位置，间距为100
    CListNode* pCur = m_pHead;
    int index = 0;
    while (pCur != nullptr) {
        pCur->point.x = 100 + index * 100;
        pCur = pCur->pNext;
        index++;
    }
}
