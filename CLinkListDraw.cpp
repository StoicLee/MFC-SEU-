#include "pch.h"
#include "CLinkListDraw.h"
#include "afxwin.h"

bool CLinkListDraw::DrawLinkList(CDC* pDC, const CLinkList& linkList)
{
    CPen pen(PS_SOLID, 3, RGB(0, 0, 0));  // �Ӵ�����
    CBrush nodeBrush(RGB(0, 150, 255));   // �ڵ������ɫ
    CFont font;
    font.CreatePointFont(120, _T("Arial"));  // ����

    // ѡ�񻭱ʺ�����
    CPen* pOldPen = pDC->SelectObject(&pen);
    CBrush* pOldBrush = pDC->SelectObject(&nodeBrush);
    CFont* pOldFont = pDC->SelectObject(&font);

    CListNode* pCur = linkList.GetHead();
    int index = 0;  // ������ʾ�ڼ��Žڵ�

    while (pCur != nullptr) {
        DrawLinkNode(pCur, pDC, index);  // ���Ƶ�ǰ�ڵ�

        if (pCur->pNext != nullptr) {
            // �ڵ�ǰ�ڵ����һ���ڵ�֮����Ƽ�ͷ
            DrawArrow(pCur->point, pCur->pNext->point, pDC);
        }

        pCur = pCur->pNext;
        index++;  // ��������
    }

    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
    pDC->SelectObject(pOldFont);

    return true;
}


bool CLinkListDraw::DrawLinkNode(CListNode* pNode, CDC* pDC,int index) {
    if (!pNode || !pDC) return false;

    // ���廭�ʺ;�������
    CBrush brush(RGB(0, 0, 255));  // ��ɫ�ڵ�
    CBrush* pOldBrush = pDC->SelectObject(&brush);

    // ���ƽڵ���ο�
    CRect nodeRect(pNode->point.x - 20, pNode->point.y - 20, pNode->point.x + 20, pNode->point.y + 20);
    pDC->Rectangle(nodeRect);
    CFont fontData;
    fontData.CreateFont(
        24,                        // ����߶�
        0,                         // ������
        0,                         // ������б�Ƕ�
        0,                         // ���߷���
        FW_BOLD,                   // �����ϸ
        FALSE,                     // �Ƿ�б��
        FALSE,                     // �Ƿ��»���
        0,                         // �ַ���
        ANSI_CHARSET,              // �ַ���
        OUT_DEFAULT_PRECIS,        // �������
        CLIP_DEFAULT_PRECIS,       // ��������
        DEFAULT_QUALITY,           // �������
        DEFAULT_PITCH | FF_SWISS,  // �ַ�����������
        _T("Arial"));              // ��������
    CFont* pOldFont = pDC->SelectObject(&fontData);
    // ���ƽڵ����ݣ�����ڵ�� data �� CString ���ͣ�
    CString strValue = pNode->data;  // ��� data �� CString ���ͣ�ֱ��ʹ��
    pDC->TextOutW(pNode->point.x - 10, pNode->point.y - 10, strValue);  // �ڽڵ�������ʾ����
    // �����Զ����������ڻ�������
    CFont fontIndex;
    fontIndex.CreateFont(
        18,                        // ����߶�
        0,                         // ������
        0,                         // ������б�Ƕ�
        0,                         // ���߷���
        FW_BOLD,                   // �����ϸ
        FALSE,                     // �Ƿ�б��
        FALSE,                     // �Ƿ��»���
        0,                         // �ַ���
        ANSI_CHARSET,              // �ַ���
        OUT_DEFAULT_PRECIS,        // �������
        CLIP_DEFAULT_PRECIS,       // ��������
        DEFAULT_QUALITY,           // �������
        DEFAULT_PITCH | FF_SWISS,  // �ַ�����������
        _T("Arial"));              // ��������
    pDC->SelectObject(&fontIndex);

    // ���ƽڵ��������ڼ��Žڵ㣩
    CString strPosition;
    strPosition.Format(_T("Index: %d"),index);  // ��ʾ�ڵ������
    pDC->TextOutW(pNode->point.x - 30, pNode->point.y + 30, strPosition);  // �ڽڵ��·���ʾ����

    // �ָ���ˢ
    pDC->SelectObject(pOldBrush);
    pDC->SelectObject(pOldFont);
    return true;
}




void CLinkListDraw::DrawArrow(CPoint startPoint, CPoint endPoint, CDC* pDC) {
    // �����ͷ�����յ㣨����ڵ�Ŀ��Ϊ40��
    CPoint arrowStart(startPoint.x + 20, startPoint.y);  // ��ǰ�ڵ��ұ�
    CPoint arrowEnd(endPoint.x - 20, endPoint.y);  // ��һ���ڵ����

    // ���ƴӼ�ͷ��㵽�յ��ֱ��
    pDC->MoveTo(arrowStart);
    pDC->LineTo(arrowEnd);

    // ��ͷ�ĽǶȼ���
    double angle = atan2((double)(arrowEnd.y - arrowStart.y), (double)(arrowEnd.x - arrowStart.x));
    double arrowLen = 10.0;  // ��ͷ����
    double arrowAngle = 0.5;  // ��ͷ���ߵļн�

    // �����ͷ������λ��
    CPoint arrow1, arrow2;
    arrow1.x = arrowEnd.x - (int)(arrowLen * cos(angle - arrowAngle));
    arrow1.y = arrowEnd.y - (int)(arrowLen * sin(angle - arrowAngle));

    arrow2.x = arrowEnd.x - (int)(arrowLen * cos(angle + arrowAngle));
    arrow2.y = arrowEnd.y - (int)(arrowLen * sin(angle + arrowAngle));

    // ���Ƽ�ͷ����
    pDC->MoveTo(arrowEnd);
    pDC->LineTo(arrow1);
    pDC->MoveTo(arrowEnd);
    pDC->LineTo(arrow2);
}






