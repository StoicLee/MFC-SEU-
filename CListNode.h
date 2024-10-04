#pragma once
class CListNode
{
public:
    CPoint point;
    CString data;
    CListNode* pNext;
    bool highlight;  // 用于标记是否高亮显示

    CListNode(CPoint pt, CString str)
        : point(pt), data(str), pNext(nullptr), highlight(false) {}
};

