#ifndef _DES_H
#define _DES_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef uint8
#define uint8  FS_UINT8
#endif

#ifndef uint32
#define uint32 FS_UINT32
#endif

    typedef struct
    {
        uint32 esk[32];     /* DES encryption subkeys */
        uint32 dsk[32];     /* DES decryption subkeys */
    }
    des_context;

    typedef struct
    {
        uint32 esk[96];     /* Triple-DES encryption subkeys */
        uint32 dsk[96];     /* Triple-DES decryption subkeys */
    }
    des3_context;

    FS_INT32  des_set_key(des_context *ctx, uint8 key[8]);
    void des_encrypt(des_context *ctx, uint8 input[8], uint8 output[8]);
    void des_decrypt(des_context *ctx, uint8 input[8], uint8 output[8]);

    FS_INT32  des3_set_2keys(des3_context *ctx, uint8 key1[8], uint8 key2[8]);
    FS_INT32  des3_set_3keys(des3_context *ctx, uint8 key1[8], uint8 key2[8],
        uint8 key3[8]);

    void des3_encrypt(des3_context *ctx, uint8 input[8], uint8 output[8]);
    void des3_decrypt(des3_context *ctx, uint8 input[8], uint8 output[8]);
    void Des3_EncryptString(des3_context* ctx, const  CHAR *szInput, FS_INT32 nInputLen, CHAR *szOutput, FS_INT32* pOutputLen);
    void Des3_DecryptString(des3_context* ctx, const  CHAR *szInput, FS_INT32 nInputLen, CHAR *szOutput, FS_INT32* pOutputLen);


#ifdef __cplusplus
}
#endif
#endif /* des.h */
