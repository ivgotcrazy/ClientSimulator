#ifndef __TIXML_FUNCTION_H
#define __TIXML_FUNCTION_H

#include "tinyxml.h"

namespace WBASELIB
{

const char*		TiXmlGetValue(TiXmlElement* pElement, const char* szValueName);
const char*		TiXmlGetValue(TiXmlElement* pElement, const char* szValueName, CHAR* szValue, FS_UINT32 dwSize);
const char*		TiXmlGetNextValue(TiXmlElement* &pElement, const char* szValueName);
void			TiXmlSetValue(TiXmlElement* pElement, const char* szValueName, const char* szValue);
void			TiXmlAddValue(TiXmlElement* pElement, const char* szValueName, const char* szValue);

const CHAR*		TiXmlGetElementValue(TiXmlElement* pElement, const CHAR* szValueName, CHAR* szValue, FS_UINT32 dwSize);
const CHAR*		TiXmlGetElementValue(TiXmlElement* pElement, const CHAR* szValueName, WCHAR* wszValue, FS_UINT32 dwSize);
const CHAR*		TiXmlGetElementValue(TiXmlElement* pElement, const CHAR* szValueName, FS_INT32& nValue);
const CHAR*		TiXmlGetElementValue(TiXmlElement* pElement, const CHAR* szValueName, GUID& guid);
const CHAR*		TiXmlGetElementValue(TiXmlElement* pElement, const CHAR* szValueName, double& fValue);

void		TiXmlSetElementValue(TiXmlElement* pElement, const CHAR* szValueName, const CHAR* szValue);
void		TiXmlSetElementValue(TiXmlElement* pElement, const CHAR* szValueName, const WCHAR* wszValue);
void		TiXmlSetElementValue(TiXmlElement* pElement, const CHAR* szValueName, FS_INT32 nValue);
void		TiXmlSetElementValue(TiXmlElement* pElement, const CHAR* szValueName, const GUID& guid);
void		TiXmlSetElementValue(TiXmlElement* pElement, const CHAR* szValueName, double fValue);

void		TiXmlAddElementValue(TiXmlElement* pElement, const CHAR* szValueName, const CHAR* szValue);
void		TiXmlAddElementValue(TiXmlElement* pElement, const CHAR* szValueName, const WCHAR* wszValue);
void		TiXmlAddElementValue(TiXmlElement* pElement, const CHAR* szValueName, FS_INT32 nValue);
void		TiXmlAddElementValue(TiXmlElement* pElement, const CHAR* szValueName, const GUID& guid);
void		TiXmlAddElementValue(TiXmlElement* pElement, const CHAR* szValueName, double fValue);

}

#endif