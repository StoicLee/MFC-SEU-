#pragma once
class CListNode
{
public:
    CPoint point;
    CString data;
    CListNode* pNext;
    bool highlight;  // ���ڱ���Ƿ������ʾ

    CListNode(CPoint pt, CString str)
        : point(pt), data(str), pNext(nullptr), highlight(false) {}
};

