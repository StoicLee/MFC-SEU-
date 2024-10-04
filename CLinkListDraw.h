// CLinkListDraw.h
#pragma once
#include "CLinkList.h"

class CLinkListDraw
{
public:
    bool DrawLinkList(CDC* pDC, const CLinkList& linkList);
    bool DrawLinkNode(CListNode* pNode, CDC* pDC,int index);
    void DrawPolyLine(CPoint curPoint, CPoint nextPoint, CDC* pDC);
    void DrawArrow(CPoint startPoint, CPoint endPoint, CDC* pDC);
};


