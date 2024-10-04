// CLinkList.h
#pragma once
#include "CListNode.h"

class CLinkList
{
private:
    CListNode* m_pHead;  // 头节点指针
    CListNode* m_pTail;  // 尾节点指针
    int m_count;         // 节点数量

public:
    CLinkList() : m_pHead(nullptr), m_pTail(nullptr), m_count(0) {}

    void AddNode(CPoint vPoint, CString vString);
    void InsertNode(CPoint vPoint, int vPos, CString vString);
    void DeleteNode(int vPos);
    BOOL Search(CString vString) const;
    bool IsEmpty() const { return m_pHead == nullptr; }
    CListNode* GetHead() const { return m_pHead; }
    CListNode* GetTail() const { return m_pTail; }
    int GetCount() const { return m_count; }
    void UpdateNodePositions();
};

