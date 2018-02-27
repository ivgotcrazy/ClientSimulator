/* MDHash.H - header file for MDHash.cpp
 */

//See internet RFC 1321, "The MD5 Message-Digest Algorithm"

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.
*/

#ifndef _MDHashCONTEXT_H
#define _MDHashCONTEXT_H

#include "stdafx.h"

namespace WBASELIB
{

/* POINTER defines a generic pointer type */
typedef FS_UINT8 *POINTER;

/* UINT2 defines a two byte word */
typedef FS_UINT16 UINT2;

/* UINT4 defines a four byte word */
typedef FS_UINT32 UINT4;

typedef struct
{
    UINT4 state[4];                                   /* state (ABCD) */
    UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
    FS_UINT8 buffer[64];                         /* input buffer */
}MDHash_CONTEXT, MD5_CONTEXT;

void MDHashInit(MDHash_CONTEXT *);
void MDHashUpdate(MDHash_CONTEXT *, void*, FS_UINT32);
void MDHashFinal(MDHash_CONTEXT *, FS_UINT8[16]);
void GetMDHash(void *, FS_UINT32, FS_UINT8[16]);
FS_UINT32 MDHashFinal4(MDHash_CONTEXT *pmc);
};

#endif