// ImageReSize.h: interface for the ImageReSize class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGERESIZE_H__104DF4C2_31AC_4BC3_9C10_0C56CEE0BD88__INCLUDED_)
#define AFX_IMAGERESIZE_H__104DF4C2_31AC_4BC3_9C10_0C56CEE0BD88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define BYTE unsigned char
class ImageReSize  
{
public:

	/*two interface functions for the following:176*144->352*288;352*288->176*144;352*288->88*72;176*144->88*72*/
    /*note:update for anysize image transformations is fited for this two function                             */
    //magnify:
	void MagnifyImageAnySize(unsigned char* pSrc, unsigned char* pDes, int oldWidth, int oldHeight, int newWidth, int newHeight);
    //shrink:
	void ShrinkImageAnySize(unsigned char* pSrc, unsigned char* pDes, int oldWidth, int oldHeight, int newWidth, int newHeight);
	 
	
	ImageReSize();
	virtual ~ImageReSize();
private:
	/*Subtract image function*/
    int YUV12Subtract(unsigned char* pSrc, unsigned char* pDes, int oldWidth, int oldHeight, int newWidth, int newHeight, double xFactor, double yFactor);
	/*children's function*/
	void EnlargeImageY(unsigned char* image, unsigned char* newimage, int lWidth, int lHeight, int lNewWidth, int lNewHeight);
	void EnlargeImageUV(unsigned char* image, unsigned char* newimage,int lWidth, int lHeight, int lNewWidth, int lNewHeight);
	void EnlargeImageYnew(unsigned char* image, unsigned char* newimage, int lWidth, int lHeight, int lNewWidth, int lNewHeight);
	void StrechYPixels(unsigned char* src_pixel, unsigned char* dest_pixel, int N1W, int N1H, int N2W, int N2H);
	void StrechUVPixels(unsigned char* src_pixel, unsigned char* dest_pixel, int N1W, int N1H, int N2W, int N2H);
	void Stretch_Linear(BYTE * aSrc, BYTE * aDest, int oldWidth, int oldHeight, int newWidth, int newHeight);
	void Stretch_LinearIPP(BYTE * aSrc, BYTE * aDest, int oldWidth, int oldHeight, int newWidth, int newHeight,double widthFactor,double heightFactor);
	void Stretch_LinearUVIPP(BYTE * aSrc, BYTE * aDest, int oldWidth, int oldHeight, int newWidth, int newHeight,double widthFactor,double heightFactor);


};

#endif // !defined(AFX_IMAGERESIZE_H__104DF4C2_31AC_4BC3_9C10_0C56CEE0BD88__INCLUDED_)
