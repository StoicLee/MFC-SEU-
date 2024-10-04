// CLinkListCtrl.h
#pragma once
#include "CLinkList.h"
#include "CLinkListDraw.h"

class CLinkListCtrl
{
public:
    CLinkListCtrl();
    ~CLinkListCtrl();

    void Initialize(CWnd* pParentWnd, CLinkList* pLinkList, CLinkListDraw* pLinkListDraw);
    void AddNode(CPoint vPoint, CString vString);
    void InsertNode(CPoint vPoint, int vPos, CString vString);
    void DeleteNode(int vPos);
    BOOL Search(CString vString,int vPos);

    void Draw(CDC* pDC);

private:
    CLinkList* m_pLinkList;
    CLinkListDraw* m_pLinkListDraw;
    CWnd* m_pParentWnd;
};

