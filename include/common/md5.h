//md5.h

#pragma once
#include <string>

typedef FS_UINT8    UINT1;
typedef FS_UINT8 *    POINTER;
typedef FS_UINT16    UINT2;
typedef FS_UINT32    UINT4;


/* MD5 context */
typedef struct
{
    UINT4    state[4];        // state (ABCD)
    UINT4    count[2];        // number of bit, modulo 2 ^ 64
    UINT1    buffer[64];        // input buffer
} MD5_CTX;

void MD5Init(MD5_CTX*);
void MD5Update(MD5_CTX *, UINT1 *, UINT4);
void MD5Final(UINT1[16], MD5_CTX *);
std::string MD5Result(UINT1[16]);
std::string MD5Encode(const char* src);

