// serviceaddrconfig.h: interface and implementation of the CServiceAddrConfig class.
//
/////////////////////////////////////////////////////////////////////////////////
#include "string"
#include "wfilefunction.h"
#include "wcharfunction.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

using namespace WBASELIB;

typedef struct{
	GUID				guidService;
    FS_UINT16			wServiceAppID;
	CHAR				szServiceAddr[1024];
	BOOL				bSupportCascade;
}ServiceAddrItem;

class CServiceAddrConfig  
{
public:
	CServiceAddrConfig()
	{
		_stprintf( m_szConfigFilePath,_T("%sServerAddr.ini"),GetModulePath());
	};
	virtual ~CServiceAddrConfig(){};
public:
	void	UpdateServerAddr( const ServiceAddrItem& addr )
	{
        	WCHAR szAppName[MAX_PATH];
		ZeroMemory( szAppName,sizeof(szAppName));
		StringFromGUID2( addr.guidService,szAppName,MAX_PATH );
        	TCHAR szApp[MAX_PATH];
		ZeroMemory( szApp,sizeof(szApp));
#ifdef _UNICODE
        	wstrcpy(szApp, szAppName);
#else
        	ConvertUnicodeToUtf8(szAppName, szApp, _countof(szApp));
#endif
		TCHAR szKey[MAX_PATH];
		TCHAR szValue[MAX_PATH];
		ZeroMemory( szValue,sizeof(szValue));
		_stprintf( szKey, _T("%s.%s"), szApp, _T("AppID") );
		m_pt.put(szKey, addr.wServiceAppID);

		_stprintf( szKey, _T("%s.%s"), szApp, _T("Addr") );
#ifdef _UNICODE
		ConvertUtf8ToUnicode( addr.szServiceAddr,szValue,_countof(szValue) );
#else
        	strcpy(szValue, addr.szServiceAddr);
#endif
		m_pt.put(szKey, szValue);

		_stprintf( szKey, _T("%s.%s"), szApp, _T("SupportCascade") );
		m_pt.put(szKey, addr.bSupportCascade);

        	boost::property_tree::ini_parser::write_ini(m_szConfigFilePath, m_pt);
	};
	BOOL	ReadServerAddr( const GUID& guidService,ServiceAddrItem& addr )
	{
        	boost::property_tree::ini_parser::read_ini(m_szConfigFilePath, m_pt);

		ZeroMemory( &addr,sizeof(addr));

		WCHAR szAppName[MAX_PATH];
		ZeroMemory( szAppName,sizeof(szAppName));
		StringFromGUID2( guidService,szAppName,MAX_PATH );
        	TCHAR szApp[MAX_PATH];
		ZeroMemory( szApp,sizeof(szApp));
#ifdef _UNICODE
        	wstrcpy(szApp, szAppName);
#else
        	ConvertUnicodeToUtf8(szAppName, szApp, _countof(szApp));
#endif
		TCHAR szKey[MAX_PATH];
		addr.guidService = guidService;

		_stprintf( szKey, _T("%s.%s"), szApp, _T("AppID") );
		addr.wServiceAppID = m_pt.get( szKey, 0 );

		_stprintf( szKey, _T("%s.%s"), szApp, _T("SupportCascade") );
		addr.bSupportCascade = m_pt.get( szKey, 0 );

		TCHAR szValue[1024];
		ZeroMemory( szValue,sizeof(szValue));
		_stprintf( szKey, _T("%s.%s"), szApp, _T("Addr") );
        	_stprintf( szValue, _T("%s"), m_pt.get( szKey, _T("")).c_str());
		if( _tcslen( szValue ) > 0 ){
#ifdef _UNICODE
			ConvertUnicodeToUtf8( szValue,addr.szServiceAddr,_countof(addr.szServiceAddr) );
#else
        		strcpy(addr.szServiceAddr, szValue);
#endif
		}
		return addr.wServiceAppID != 0 && strlen( addr.szServiceAddr ) > 0;
	};
protected:

#ifdef _UNICODE
    typedef boost::property_tree::wptree    PropertyTree;
#else
    typedef boost::property_tree::ptree     PropertyTree;
#endif
    PropertyTree m_pt;

	TCHAR		m_szConfigFilePath[MAX_PATH];
};

