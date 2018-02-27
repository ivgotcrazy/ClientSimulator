#ifndef __WGDI_FUNCTION_H
#define __WGDI_FUNCTION_H

namespace WBASELIB
{

#pragma comment(lib, "msimg32.lib") 

static void GradientFillRect(HDC hDC, const RECT &rcFill, BOOL bVertical, COLORREF crLeftTop, COLORREF crRightBottom)
{
    FS_UINT32 nMode = GRADIENT_FILL_RECT_H;
    if (bVertical)
        nMode = GRADIENT_FILL_RECT_V;

    COLOR16 r = (COLOR16)((crLeftTop & 0x000000FF) << 8);
    COLOR16 g = (COLOR16)(crLeftTop & 0x0000FF00);
    COLOR16 b = (COLOR16)((crLeftTop & 0x00FF0000) >> 8);

    TRIVERTEX        vert[2];
    GRADIENT_RECT    gRect;
    vert[0].x = rcFill.left;
    vert[0].y = rcFill.top;
    vert[0].Red = r;
    vert[0].Green = g;
    vert[0].Blue = b;
    vert[0].Alpha = 0x0000;

    r = (COLOR16)((crRightBottom & 0x000000FF) << 8);
    g = (COLOR16)(crRightBottom & 0x0000FF00);
    b = (COLOR16)((crRightBottom & 0x00FF0000) >> 8);

    vert[1].x = rcFill.right;
    vert[1].y = rcFill.bottom;
    vert[1].Red = r;
    vert[1].Green = g;
    vert[1].Blue = b;
    vert[1].Alpha = 0x0000;

    gRect.UpperLeft = 0;
    gRect.LowerRight = 1;

    GradientFill(hDC, vert, 2, &gRect, 1, nMode);
}

//ɾ������ķָ���
static void	CleanMenuSeparator(HMENU hMenu)
{
    FS_INT32		nCount = GetMenuItemCount(hMenu);
    BOOL	bIsSeparator = FALSE;
    BOOL	bPrevIsSeparator = FALSE;
    FS_INT32		nIndex = 0;
    FS_UINT32	nState = 0;
    while (nIndex < nCount)
    {

        HMENU hSubMenu = GetSubMenu(hMenu, nIndex);
        FS_INT32	  nSubCount = 0;
        if (hSubMenu)
        {

            nSubCount = GetMenuItemCount(hSubMenu);
            BOOL	bSubIsSeparator = FALSE;
            BOOL	bSubPrevIsSeparator = FALSE;
            FS_INT32		nSubIndex = 0;
            while (nSubIndex < nSubCount)
            {
                nState = GetMenuState(hSubMenu, nSubIndex, MF_BYPOSITION);
                bSubIsSeparator = nState&MF_SEPARATOR;
                if (bSubIsSeparator && (bSubPrevIsSeparator ||
                    nSubIndex == 0 || nSubIndex == nSubCount - 1))
                {
                    DeleteMenu(hSubMenu, nSubIndex, MF_BYPOSITION);
                    --nSubCount;
                }
                else
                {
                    ++nSubIndex;
                    bSubPrevIsSeparator = bSubIsSeparator;
                }
            }
        }
        nState = GetMenuState(hMenu, nIndex, MF_BYPOSITION);
        bIsSeparator = nState&MF_SEPARATOR && NULL == hSubMenu;
        //����ǵ����˵������Ӳ˵�Ϊ�գ�Ҳɾ��
        bIsSeparator |= (hSubMenu && nSubCount == 0);
        if (bIsSeparator && (bPrevIsSeparator ||
            nIndex == 0 || nIndex == nCount - 1))
        {
            DeleteMenu(hMenu, nIndex, MF_BYPOSITION);
            --nCount;
        }
        else
        {
            ++nIndex;
            bPrevIsSeparator = bIsSeparator;
        }
    }
    //���δβ�����������ָ���ʱ����һ������ɾ��
    nCount = GetMenuItemCount(hMenu);
    nState = GetMenuState(hMenu, nCount - 1, MF_BYPOSITION);
    if (nState&MF_SEPARATOR)
    {
        DeleteMenu(hMenu, nCount - 1, MF_BYPOSITION);
    }
}

static void   TransparentBlt2(HDC   hdc0, //Ŀ��DC   
    FS_INT32   nX0, FS_INT32   nY0, FS_INT32   nW0, FS_INT32   nH0,//Ŀ��������,Ŀ���߿�   
    HDC   hdc1, //ԴDC   
    FS_INT32   nX1, FS_INT32   nY1, FS_INT32   nW1, FS_INT32   nH1,//Դ�������,Դ��߿�   
    FS_UINT32   Tcol) //͸��ɫ,COLORREF����   
{
    HBITMAP hBMP = CreateCompatibleBitmap(hdc0, nW0, nH0); //����λͼ�ڴ�   
    HBITMAP mBMP = CreateBitmap(nW0, nH0, 1, 1, NULL); //������ɫ����λͼ   
    HDC hDC = CreateCompatibleDC(hdc0); //�����豸���   
    HDC mDC = CreateCompatibleDC(hdc0); //�����豸���   
    HBITMAP oldBMP = (HBITMAP)SelectObject(hDC, hBMP);
    HBITMAP oldmBMP = (HBITMAP)SelectObject(mDC, mBMP);
    //   ��ԴDC�е�λͼ��������ʱDC��   
    if (nW0 == nW1&&nH0 == nH1)
        BitBlt(hDC, 0, 0, nW0, nH0, hdc1, nX1, nY1, SRCCOPY);
    else
        StretchBlt(hDC, 0, 0, nW0, nH0, hdc1, nX1, nY1, nW1, nH1, SRCCOPY);
    SetBkColor(hDC, Tcol);//   ����͸��ɫ   
    BitBlt(mDC, 0, 0, nW0, nH0, hDC, 0, 0, SRCCOPY);//����͸������Ϊ��ɫ,��������Ϊ��ɫ������λͼ   

    SetBkColor(hDC, RGB(0, 0, 0)); //����͸������Ϊ��ɫ,�������򱣳ֲ����λͼ   
    SetTextColor(hDC, RGB(255, 255, 255)); //��ɫ   
    BitBlt(hDC, 0, 0, nW0, nH0, mDC, 0, 0, SRCAND);
    SetBkColor(hdc0, RGB(255, 255, 255)); //͸�����ֱ�����Ļ����,�������ֱ�ɺ�ɫ   
    SetTextColor(hdc0, RGB(0, 0, 0)); //��ɫ   

    BitBlt(hdc0, nX0, nY0, nW0, nH0, mDC, 0, 0, SRCAND);     //"��"����,��hdc0������ģ   
    BitBlt(hdc0, nX0, nY0, nW0, nH0, hDC, 0, 0, SRCPAINT);//"��"����,��������͸��Ч��   

    SelectObject(hDC, oldBMP);
    SelectObject(mDC, oldmBMP);
    DeleteDC(hDC);
    DeleteDC(mDC);
    DeleteObject(hBMP);
    DeleteObject(mBMP);
}

static void   DrawAlphaBlend(HDC   hdc, RECT   rcDes, HBITMAP   bmp, RECT   rcBmp, COLORREF   cTranColor, BYTE   blend)
{
    HDC BkDC = CreateCompatibleDC(hdc);
    HBITMAP bit = CreateCompatibleBitmap(hdc, rcDes.right - rcDes.left, rcDes.bottom - rcDes.top);

    SelectObject(BkDC, bit);
    BitBlt(BkDC, 0, 0, rcDes.right - rcDes.left, rcDes.bottom - rcDes.top, hdc, rcDes.left, rcDes.top, SRCCOPY);

    HDC memdc;
    memdc = CreateCompatibleDC(hdc);
    SelectObject(memdc, bmp);
    TransparentBlt2(BkDC, rcBmp.left, rcBmp.top, rcBmp.right - rcBmp.left, rcBmp.bottom - rcBmp.top,
        memdc, 0, 0, rcBmp.right - rcBmp.left, rcBmp.bottom - rcBmp.top, cTranColor);

    BLENDFUNCTION   rBlend; //��͸��   
    rBlend.BlendOp = AC_SRC_OVER; //   
    rBlend.BlendFlags = 0; //   
    rBlend.AlphaFormat = 0; //   
    rBlend.SourceConstantAlpha = blend;
    AlphaBlend(hdc, rcDes.left, rcDes.top, rcDes.right - rcDes.left, rcDes.bottom - rcDes.top, BkDC, 0, 0, rcDes.right - rcDes.left, rcDes.bottom - rcDes.top, rBlend);

    DeleteObject(BkDC);
    DeleteObject(bit);
    DeleteObject(memdc);
}
}

#endif