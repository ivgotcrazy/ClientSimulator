// Ntlm.h: interface for the CNtlmAuth class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NTLM_H__6BEB659A_4299_45E1_BD1F_D4B10369033A__INCLUDED_)
#define AFX_NTLM_H__6BEB659A_4299_45E1_BD1F_D4B10369033A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define HOST_NAME_MAX_LEN 256
#define HOST_DOMAIN_MAX_LEN 256


struct stRequest
{
    char	protocol[8];
    FS_UINT32	type;        //顺序号
    FS_UINT32	flags;
    FS_UINT16	dom_len;    //域名长度
    FS_UINT16	dom_maxlen;	//域名最大长度
    FS_UINT32	dom_off;	//域名偏移
    FS_UINT16	host_len;   //主机名长度
    FS_UINT16	host_maxlen;//主机名最大长度
    FS_UINT32	host_off;   //主机名偏移

    stRequest()
    {
        memset(this, 0, sizeof(stRequest));
        strncpy(protocol, "NTLMSSP", SIZE_ARRAY(protocol));
        type = 1;
        flags = 0xb207;
        dom_len = dom_maxlen = 0;
        dom_off = 0;
        host_len = host_maxlen = 0;
        host_off = 0;
    }
};


struct stServerResponse
{
    char	protocol[8];
    FS_UINT32	type;			//顺序号，必须为2
    FS_UINT16	dom_len;		//域名长度
    FS_UINT16	dom_maxlen;		//域名最大长度
    FS_UINT32	dom_off;		//域名偏移
    FS_UINT32	flags;
    BYTE	challage[8];    //8字节挑战
    BYTE	RE[8];			//保留8字节，必须为0
    FS_UINT16	host_list_len;  //主机名列表长度
    FS_UINT16	host_list_maxlen;//主机名列表最大长度
    FS_UINT32	host_list_off;	//主机名列表偏移

    stServerResponse()
    {
        memset(this, 0, sizeof(stServerResponse));
        strncpy(protocol, "NTLMSSP", SIZE_ARRAY(protocol));
        type = 2;
    }
};


struct stClientResponse
{
    char	protocol[8];
    FS_UINT32	type;			//顺序号，必须为3
    FS_UINT16	lm_resp_len;	//LanManager response length (always 0x18)	
    FS_UINT16	lm_resp_maxlen;	//LanManager response length (always 0x18)	
    FS_UINT32	lm_resp_off;	//LanManager response offset	
    FS_UINT16	nt_resp_len;	//NT response length (always 0x18)
    FS_UINT16	nt_resp_maxlen; //NT response length (always 0x18)
    FS_UINT32	nt_resp_off;	//NT response offset

    FS_UINT16	dom_len;		//域名长度
    FS_UINT16	dom_maxlen;		//域名最大长度
    FS_UINT32	dom_off;		//域名偏移	
    FS_UINT16	user_len;		//用户名长度
    FS_UINT16	user_maxlen;	//用户名最大长度
    FS_UINT32	user_off;		//用户名偏移
    FS_UINT16	host_len;		//主机名长度
    FS_UINT16	host_maxlen;	//主机名最大长度
    FS_UINT32	host_off;		//主机名偏移

    FS_UINT16	rc4_ntlm_len;    //加密的RC4 NTLM散列长度
    FS_UINT16	rc4_ntlm_maxlen; //加密的RC4 NTLM散列最大长度
    FS_UINT32	rc4_ntlm_off;    //加密的RC4 NTLM散列偏移, 指到末尾

    FS_UINT32	flags;


    stClientResponse()
    {
        memset(this, 0, sizeof(stClientResponse));
        strncpy(protocol, "NTLMSSP", SIZE_ARRAY(protocol));
        type = 3;
        flags = 0xa2808205;
        lm_resp_len = 0x18;
        lm_resp_maxlen = 0x18;
        nt_resp_len = 0x18;
        nt_resp_maxlen = 0x18;
    }
};



class CNtlmAuth
{
public:
    CNtlmAuth();
    virtual ~CNtlmAuth();

public:

    FS_INT32 MakeRequest(char* pszDomain, FS_INT32 nDomainLen,
        char* pszHostName, FS_INT32 nHostNameLen,
        unsigned char* pBuffer, FS_INT32 nBufferLen);
    FS_INT32 MakeResponse(char* pszUserName, FS_INT32 nUserNameLen,
        char* pszPassWord, FS_INT32 nPassWordLen,
        char* pszDomain, FS_INT32 nDomainLen,
        char* pszHostName, FS_INT32 nHostNameLen,
        const char* pBuffIn, FS_INT32 nBuffInLen,
        unsigned char* pBuffOut, FS_INT32 nBuffOutLen);

private:
    FS_INT32 LmHash(const unsigned char* BuffIn, FS_INT32 nInLen, unsigned char* BuffOut, FS_INT32 nOutLen);
    FS_INT32 NtlmHash(const unsigned char* BuffIn, FS_INT32 nInLen, unsigned char* BuffOut, FS_INT32 nOutLen);

    /*
    * from The Samba Team 's source/libsmb/smbdes.c
    */
    void StrtoKey(const unsigned char *str, unsigned char *key);
    void CaculateResponse(unsigned char *keys, unsigned char *plaintext, unsigned char *results);
};

#endif // !defined(AFX_NTLM_H__6BEB659A_4299_45E1_BD1F_D4B10369033A__INCLUDED_)
