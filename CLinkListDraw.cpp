#include "pch.h"
#include "CLinkListDraw.h"
#include "afxwin.h"

bool CLinkListDraw::DrawLinkList(CDC* pDC, const CLinkList& linkList)
{
    CPen pen(PS_SOLID, 3, RGB(0, 0, 0));  // 加粗线条
    CBrush nodeBrush(RGB(0, 150, 255));   // 节点填充颜色
    CFont font;
    font.CreatePointFont(120, _T("Arial"));  // 字体

    // 选择画笔和字体
    CPen* pOldPen = pDC->SelectObject(&pen);
    CBrush* pOldBrush = pDC->SelectObject(&nodeBrush);
    CFont* pOldFont = pDC->SelectObject(&font);

    CListNode* pCur = linkList.GetHead();
    int index = 0;  // 用于显示第几号节点

    while (pCur != nullptr) {
        DrawLinkNode(pCur, pDC, index);  // 绘制当前节点

        if (pCur->pNext != nullptr) {
            // 在当前节点和下一个节点之间绘制箭头
            DrawArrow(pCur->point, pCur->pNext->point, pDC);
        }

        pCur = pCur->pNext;
        index++;  // 更新索引
    }

    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
    pDC->SelectObject(pOldFont);

    return true;
}


bool CLinkListDraw::DrawLinkNode(CListNode* pNode, CDC* pDC,int index) {
    if (!pNode || !pDC) return false;

    // 定义画笔和矩形区域
    CBrush brush(RGB(0, 0, 255));  // 蓝色节点
    CBrush* pOldBrush = pDC->SelectObject(&brush);

    // 绘制节点矩形框
    CRect nodeRect(pNode->point.x - 20, pNode->point.y - 20, pNode->point.x + 20, pNode->point.y + 20);
    pDC->Rectangle(nodeRect);
    CFont fontData;
    fontData.CreateFont(
        24,                        // 字体高度
        0,                         // 字体宽度
        0,                         // 文字倾斜角度
        0,                         // 基线方向
        FW_BOLD,                   // 字体粗细
        FALSE,                     // 是否斜体
        FALSE,                     // 是否下划线
        0,                         // 字符集
        ANSI_CHARSET,              // 字符集
        OUT_DEFAULT_PRECIS,        // 输出精度
        CLIP_DEFAULT_PRECIS,       // 剪辑精度
        DEFAULT_QUALITY,           // 输出质量
        DEFAULT_PITCH | FF_SWISS,  // 字符间距和字体族
        _T("Arial"));              // 字体名称
    CFont* pOldFont = pDC->SelectObject(&fontData);
    // 绘制节点数据（假设节点的 data 是 CString 类型）
    CString strValue = pNode->data;  // 如果 data 是 CString 类型，直接使用
    pDC->TextOutW(pNode->point.x - 10, pNode->point.y - 10, strValue);  // 在节点中央显示数据
    // 创建自定义字体用于绘制索引
    CFont fontIndex;
    fontIndex.CreateFont(
        18,                        // 字体高度
        0,                         // 字体宽度
        0,                         // 文字倾斜角度
        0,                         // 基线方向
        FW_BOLD,                   // 字体粗细
        FALSE,                     // 是否斜体
        FALSE,                     // 是否下划线
        0,                         // 字符集
        ANSI_CHARSET,              // 字符集
        OUT_DEFAULT_PRECIS,        // 输出精度
        CLIP_DEFAULT_PRECIS,       // 剪辑精度
        DEFAULT_QUALITY,           // 输出质量
        DEFAULT_PITCH | FF_SWISS,  // 字符间距和字体族
        _T("Arial"));              // 字体名称
    pDC->SelectObject(&fontIndex);

    // 绘制节点索引（第几号节点）
    CString strPosition;
    strPosition.Format(_T("Index: %d"),index);  // 显示节点的索引
    pDC->TextOutW(pNode->point.x - 30, pNode->point.y + 30, strPosition);  // 在节点下方显示索引

    // 恢复画刷
    pDC->SelectObject(pOldBrush);
    pDC->SelectObject(pOldFont);
    return true;
}




void CLinkListDraw::DrawArrow(CPoint startPoint, CPoint endPoint, CDC* pDC) {
    // 计算箭头起点和终点（假设节点的宽度为40）
    CPoint arrowStart(startPoint.x + 20, startPoint.y);  // 当前节点右边
    CPoint arrowEnd(endPoint.x - 20, endPoint.y);  // 下一个节点左边

    // 绘制从箭头起点到终点的直线
    pDC->MoveTo(arrowStart);
    pDC->LineTo(arrowEnd);

    // 箭头的角度计算
    double angle = atan2((double)(arrowEnd.y - arrowStart.y), (double)(arrowEnd.x - arrowStart.x));
    double arrowLen = 10.0;  // 箭头长度
    double arrowAngle = 0.5;  // 箭头两边的夹角

    // 计算箭头两侧点的位置
    CPoint arrow1, arrow2;
    arrow1.x = arrowEnd.x - (int)(arrowLen * cos(angle - arrowAngle));
    arrow1.y = arrowEnd.y - (int)(arrowLen * sin(angle - arrowAngle));

    arrow2.x = arrowEnd.x - (int)(arrowLen * cos(angle + arrowAngle));
    arrow2.y = arrowEnd.y - (int)(arrowLen * sin(angle + arrowAngle));

    // 绘制箭头两侧
    pDC->MoveTo(arrowEnd);
    pDC->LineTo(arrow1);
    pDC->MoveTo(arrowEnd);
    pDC->LineTo(arrow2);
}






