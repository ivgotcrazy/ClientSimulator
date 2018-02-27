// ShareRestrictedSD.h: interface for the CShareRestrictedSD class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHARERESTRICTEDSD_H__56DF94FA_06D9_4D29_A37A_FFB71315B5C9__INCLUDED_)
#define AFX_SHARERESTRICTEDSD_H__56DF94FA_06D9_4D29_A37A_FFB71315B5C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CShareRestrictedSD  
{
public:
	CShareRestrictedSD();
	virtual ~CShareRestrictedSD();
	SECURITY_ATTRIBUTES* GetSA();
protected:
	PVOID  ptr;
	SECURITY_ATTRIBUTES sa;
	SECURITY_DESCRIPTOR sd;
};

#endif // !defined(AFX_SHARERESTRICTEDSD_H__56DF94FA_06D9_4D29_A37A_FFB71315B5C9__INCLUDED_)
