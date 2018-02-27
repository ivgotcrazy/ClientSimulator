#ifndef __XML_PROTOCOL_PARSER_H
#define __XML_PROTOCOL_PARSER_H

#include "tinyxml.h"
#include "wbasetype.h"

const CHAR*		WXmlParser_LoadCommand( TiXmlElement& element,const CHAR* szCommand,FS_INT32 nLength );

const CHAR*		WXmlParser_GetCommand( TiXmlElement *pElement,FS_UINT16& wCommand );
BOOL			WXmlParser_SetCommand( TiXmlElement *pElement,FS_UINT16 wCommand );

const CHAR*		WXmlParser_GetVersion( TiXmlElement *pElement );
BOOL			WXmlParser_SetVersion( TiXmlElement *pElement,const CHAR* szVersion );

const CHAR*		WXmlParser_GetSeqnum( TiXmlElement *pElement,FS_INT32& nSeqnum );
BOOL			WXmlParser_SetSeqnum( TiXmlElement *pElement,FS_INT32 nSeqnum );

const CHAR*		WXmlParser_GetFieldValue( TiXmlElement* pElement,const CHAR* szValueName,CHAR* szValue = NULL,FS_UINT32 dwSize = 0 );
BOOL			WXmlParser_SetFieldValue( TiXmlElement *pElement,const CHAR* szValueName,const CHAR* szValue );
BOOL			WXmlParser_AddFieldValue( TiXmlElement *pElement,const CHAR* szValueName,const CHAR* szValue );

const CHAR*		WXmlParser_GetFieldValue( TiXmlElement* pElement,const CHAR* szValueName,WCHAR* wszValue,FS_UINT32 dwSize );
BOOL			WXmlParser_SetFieldValue( TiXmlElement *pElement,const CHAR* szValueName,const WCHAR* wszValue );
BOOL			WXmlParser_AddFieldValue( TiXmlElement *pElement,const CHAR* szValueName,const WCHAR* wszValue );

const CHAR*		WXmlParser_GetFieldValue( TiXmlElement* pElement,const CHAR* szValueName,FS_INT32& nValue );
BOOL			WXmlParser_SetFieldValue( TiXmlElement *pElement,const CHAR* szValueName,FS_INT32 nValue );
BOOL			WXmlParser_AddFieldValue( TiXmlElement *pElement,const CHAR* szValueName,FS_INT32 nValue );

const CHAR*		WXmlParser_GetFieldValue( TiXmlElement* pElement,const CHAR* szValueName,GUID& guid );
BOOL			WXmlParser_SetFieldValue( TiXmlElement *pElement,const CHAR* szValueName,const GUID& guid );
BOOL			WXmlParser_AddFieldValue( TiXmlElement *pElement,const CHAR* szValueName,const GUID& guid );

#endif