#ifndef __TIMAGE_FILTER_H
#define __TIMAGE_FILTER_H

#include "VideoDefine.h"

BOOL 	 TImage_GetBitmapInfoHeader( int csp,int nWidth,int nHeight,BITMAPINFOHEADER& bmi );

VOID     TImage_LineFilter_ProcessRGB( PBYTE pbData,int nWidth,int nHeight,int nBitCount );
VOID     TImage_LineFilter_ProcessYUV( PBYTE pbData,int nWidth,int nHeight );

HANDLE   TImage_Convert_Create();
BOOL     TImage_Convert_SetFormat( HANDLE hConvert,const BITMAPINFOHEADER &bmpIn,const BITMAPINFOHEADER &bmpOut,BOOL bVFlip = FALSE );
VOID     TImage_Convert_Convert( HANDLE hConvert,PBYTE pbSrc,UINT nSrcLen,int nSrcStride  );
VOID     TImage_Convert_Convert( HANDLE hConvert,PBYTE pbSrc,UINT nSrcLen,int nSrcStride,PBYTE pbDst,int nDstStride );
VOID     TImage_Convert_Destroy( HANDLE &hConvert );
BOOL     TImage_Convert_SupportFormat( const BITMAPINFOHEADER &bmp );

HANDLE   TImage_TextFilter_Create( );
VOID     TImage_TextFilter_SetFormat( HANDLE hTextFilter,const BITMAPINFOHEADER &bmpIn );
VOID     TImage_TextFilter_SetText( HANDLE hTextFilter,const WCHAR *wszText );
//dwColor		文字颜色
//nNum			字体大小与图象高度比例分子
//nDen			字体大小与图象高度比例分母
//xPos			文字位置X坐标,为正时表示文字左边与图象左边的像素距离,为负时表示文字右边与图象右边的像素距离
//yPos			文字位置Y坐标,为正时表示文字上边与图象上边的像素距离,为负时表示文字下边与图像下边的像素距离
VOID     TImage_TextFilter_SetText2( HANDLE hTextFilter,const WCHAR *wszText,DWORD dwColor,int nNum,int nDen,int xPos,int yPos );
VOID     TImage_TextFilter_DrawText( HANDLE hTextFilter,PBYTE pbSrc,int nSrcStride );
VOID     TImage_TextFilter_DrawText2( HANDLE hTextFilter,PBYTE pbSrc,int nSrcStride,int nXOffset,int nYOffset );
VOID     TImage_TextFilter_Destroy( HANDLE &hTextFilter );
BOOL	 TImage_TextFilter_IsSupportFormat( const BITMAPINFOHEADER& bmpIn,BITMAPINFOHEADER *pbiOut = NULL );

HANDLE	TImage_DenoiseFilter_Create();
BOOL	TImage_DenoiseFilter_SetFormat( HANDLE hFilter,const BITMAPINFOHEADER &bmpIn );
VOID	TImage_DenoiseFilter_SetStrength( HANDLE hFilter,int nStrength );//nStrength : 0 - 100
VOID	TImage_DenoiseFilter_Process( HANDLE hFilter,PBYTE pbSrc,UINT nSrcLen,int nSrcStride );
VOID	TImage_DenoiseFilter_Destroy( HANDLE hFilter );

HANDLE	TImage_SharpenFilter_Create();
BOOL	TImage_SharpenFilter_SetFormat( HANDLE hFilter,const BITMAPINFOHEADER &bmpIn );
VOID	TImage_SharpenFilter_Process( HANDLE hFilter,PBYTE pbSrc,UINT nSrcLen,int nSrcStride );
VOID	TImage_SharpenFilter_Destroy( HANDLE hFilter );

HANDLE	TImage_ColorEnhance_Create();
BOOL	TImage_ColorEnhance_SetFormat( HANDLE hFilter,const BITMAPINFOHEADER &bmpIn );
VOID	TImage_ColorEnhance_Process( HANDLE hFilter,PBYTE pbSrc,UINT nSrcLen,int nSrcStride );
VOID	TImage_ColorEnhance_Destroy( HANDLE hFilter );

void	*TFastMemcpy( void *dst,const void *src,size_t len );

#endif