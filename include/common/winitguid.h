#ifndef __INIT_GUID_H
#define __INIT_GUID_H

#undef 	DEFINE_GUID
#define DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8 ) \
			EXTERN_C const GUID name \
				= { l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8 }}

#endif