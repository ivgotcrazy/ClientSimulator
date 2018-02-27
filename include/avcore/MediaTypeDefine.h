#ifndef MEDIA_TYPEDEFINE_H
#define MEDIA_TYPEDEFINE_H

#ifdef _WIN32
#include <mmsystem.h>
#endif

#include "wbasetype.h"

#define FOURCC_XVID mmioFOURCC('X','V','I','D')
#define FOURCC_DIVX mmioFOURCC('D','I','V','X')
#define FOURCC_DIV3 mmioFOURCC('D','I','V','3')
#define FOURCC_DX50 mmioFOURCC('D','X','5','0')

#define FOURCC_xvid mmioFOURCC('x','v','i','d')
#define FOURCC_dx50 mmioFOURCC('d','x','5','0')
#define FOURCC_divx mmioFOURCC('d','i','v','x')
#define FOURCC_div3 mmioFOURCC('d','i','v','3')

#define FOURCC_mp4v	mmioFOURCC('m','p','4','v')
#define FOURCC_MP4V mmioFOURCC('M','P','4','V')

#define FOURCC_RIVC	mmioFOURCC('R','I','V','C')
#define FOURCC_rivc mmioFOURCC('r','i','v','c')

//uncompressed
#define FOURCC_YUY2 mmioFOURCC('Y','U','Y','2')
#define FOURCC_V422 mmioFOURCC('V','4','2','2')
#define FOURCC_YV12 mmioFOURCC('Y','V','1','2')
#define FOURCC_YVYU mmioFOURCC('Y','V','Y','U')
#define FOURCC_UYVY mmioFOURCC('U','Y','V','Y')
#define FOURCC_YUYV mmioFOURCC('Y','U','Y','V')
#define FOURCC_I420 mmioFOURCC('I','4','2','0')
#define FOURCC_IYUV mmioFOURCC('I','Y','U','V')
#define FOURCC_444P mmioFOURCC('4','4','4','P')
#define FOURCC_422P mmioFOURCC('4','2','2','P')
#define FOURCC_411P mmioFOURCC('4','1','1','P')
#define FOURCC_410P mmioFOURCC('4','1','0','P')
#define FOURCC_RGB2 mmioFOURCC('R','G','B','2')
#define FOURCC_RGB3 mmioFOURCC('R','G','B','3')
#define FOURCC_RGB5 mmioFOURCC('R','G','B','5')
#define FOURCC_RGB6 mmioFOURCC('R','G','B','6')
#define FOURCC_CLJR mmioFOURCC('C','L','J','R')
#define FOURCC_MJPG mmioFOURCC('M','J','P','G')
#define FOURCC_NV12 mmioFOURCC('N','V','1','2')
#define FOURCC_NV21 mmioFOURCC('N','V','2','1')
#define FOURCC_RGBA	mmioFOURCC('R','G','B','A')
#define FOURCC_HDYC mmioFOURCC('H','D','Y','C')
#define FOURCC_BGRA mmioFOURCC('B','G','R','A')

#define FOURCC_BGRA mmioFOURCC('B','G','R','A')

#define ISRGBFOURCC(fourcc)     ((fourcc)==BI_RGB||(fourcc)==BI_BITFIELDS||(fourcc)==FOURCC_RGB5||(fourcc)==FOURCC_RGB6)

#define DEFINE_FOURCC_GUID(FOURCC) \
	DEFINE_GUID(MEDIASUBTYPE_##FOURCC, FOURCC_##FOURCC, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

DEFINE_FOURCC_GUID(XVID)
DEFINE_FOURCC_GUID(xvid)
DEFINE_FOURCC_GUID(DX50)
DEFINE_FOURCC_GUID(dx50)
DEFINE_FOURCC_GUID(DIVX)
DEFINE_FOURCC_GUID(divx)
DEFINE_FOURCC_GUID(DIV3)
DEFINE_FOURCC_GUID(div3)
DEFINE_FOURCC_GUID(I420)
DEFINE_FOURCC_GUID(MP4V)
DEFINE_FOURCC_GUID(mp4v)
DEFINE_FOURCC_GUID(RIVC)
DEFINE_FOURCC_GUID(rivc)

#endif
