//
//  AVConfig.h
//  AVCoreLib
//
//  Created by hst on 14-3-5.
//  Copyright (c) 2014骞?fastonz. All rights reserved.
//

#ifndef AVCoreLib_AVConfig_h
#define AVCoreLib_AVConfig_h

#ifdef _WIN32

#ifdef _WIN32_WCE
#define ARCH_X86                    0
#else
#define ARCH_X86                    1
#endif
#define USE_ENCRYPTDATA             1
#define USE_ALIGNEDMALLOC           1
#define USE_HASHMAP                 1
#define USE_STATICCOMPONENT         0
#define USE_2GNETWORK               0
#define USE_WAITINFINITE            1
#define USE_THREADMSG               1

#define DEFAULT_AUDIOCODECID        9
#define USE_CALAUDIOENERGY          1
#define USE_VOLUMECONTROL           1
#if _MSC_VER >= 1500
#define USE_SPEEXLIB                0
#define USE_WEBRTCLIB               1
#else
#define USE_SPEEXLIB                1
#define USE_WEBRTCLIB               0
#endif
#define USE_AMRENC                  1
#define USE_CPVEAUDIOENGINE         1
#define USE_SOUNDTOUCH				1

#define USE_EXTERNALVIDEOINPUT      0
#define USE_MSWMV9ENC               1
#define USE_MSWMV9DEC               1
#define USE_FFWMV9DEC               0
#define USE_DIVXCODEC               1
#define USE_XVIDCODEC               1
#define USE_X264ENC                 1
#define USE_FFH264DEC               1
#define USE_VPXVP9CODEC             1
#define USE_VPXVP8ENC               1
#define USE_VPXVP8DEC               1
#define USE_FFVP8DEC                0

#define USE_IMAGESHARPEN            1
#define USE_IMAGEDENOISE            1
#define USE_IMAGEDEINTERFACE        1

#define VFLIP_RGB                   0
#define USE_VIDEO_RORATE            0
#elif defined _FS_OS_LINUX

#define ARCH_X86                    1
#define USE_ENCRYPTDATA             0
#define USE_ALIGNEDMALLOC           0

#define USE_HASHMAP                 1
#define USE_STATICCOMPONENT         0

#define USE_2GNETWORK               0
#define USE_WAITINFINITE            0
#define USE_THREADMSG               0

#define DEFAULT_AUDIOCODECID        5
#define USE_CALAUDIOENERGY          0
#define USE_VOLUMECONTROL           0
#define USE_SPEEXLIB                0
// 先使用WEBRTC编译通过
#define USE_WEBRTCLIB               1
#define USE_AMRENC                  1
#define USE_CPVEAUDIOENGINE         0
#define USE_SOUNDTOUCH				0

#define USE_EXTERNALVIDEOINPUT      1
#define USE_MSWMV9ENC               0
#define USE_MSWMV9DEC               0
#define USE_FFWMV9DEC               1
#define USE_DIVXCODEC               0
#define USE_XVIDCODEC               0
#define USE_X264ENC                 1
#define USE_FFH264DEC               1
#define USE_VPXVP9CODEC             0

#define USE_VPXVP8ENC               1
#define USE_VPXVP8DEC               1
#define USE_FFVP8DEC                0

#define USE_IMAGESHARPEN            0
#define USE_IMAGEDENOISE            0
#define USE_IMAGEDEINTERFACE        0

#define VFLIP_RGB                   0
#define USE_VIDEO_RORATE            0
#else

#define ARCH_X86                    0

#define USE_ENCRYPTDATA             0
#define USE_ALIGNEDMALLOC           0
#ifdef ANDROID
#define USE_HASHMAP                 1
#define USE_STATICCOMPONENT         0
#endif
#ifdef _IOS
#define USE_HASHMAP                 0
#define USE_STATICCOMPONENT         1
#endif
#define USE_2GNETWORK               0
#define USE_WAITINFINITE            0
#define USE_THREADMSG               0

#define DEFAULT_AUDIOCODECID        5
#define USE_CALAUDIOENERGY          0
#define USE_VOLUMECONTROL           0
#define USE_SPEEXLIB                0
#define USE_WEBRTCLIB               1
#define USE_AMRENC                  0
#define USE_CPVEAUDIOENGINE         0
#define USE_SOUNDTOUCH				0

#define USE_EXTERNALVIDEOINPUT      1
#define USE_MSWMV9ENC               0
#define USE_MSWMV9DEC               0
#define USE_FFWMV9DEC               1
#define USE_DIVXCODEC               0
#define USE_XVIDCODEC               0
#define USE_X264ENC                 1
#define USE_FFH264DEC               1
#define USE_VPXVP9CODEC             0

#ifdef ANDROID
#define USE_VPXVP8ENC               1
#define USE_VPXVP8DEC               1
#define USE_FFVP8DEC                0
#define USE_VIDEO_RORATE            1 
#else
#define USE_VIDEO_RORATE            0 
#endif
#ifdef _IOS	
#define USE_VPXVP8ENC               0
#define USE_VPXVP8DEC               0
#define USE_FFVP8DEC                1
#define USE_H264IOSHDENC            1
#endif

#ifdef _FS_OS_MAC
#define ARCH_X86                    1
#define USE_HASHMAP                 0
#define USE_STATICCOMPONENT         1
#define USE_VPXVP8ENC               0
#define USE_VPXVP8DEC               0
#define USE_FFVP8DEC                1
#define USE_AMRENC                  1
#endif

#define USE_IMAGESHARPEN            0
#define USE_IMAGEDENOISE            0
#define USE_IMAGEDEINTERFACE        0

#define VFLIP_RGB                   1

#endif


#endif//?????
