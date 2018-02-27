#ifndef __INC_WOPTIONS_H__
#define __INC_WOPTIONS_H__

#include "xini.h"

namespace WBASELIB
{

#define		WOPTION_SECTIONNAME_MAXLEN		32
#define		WOPTION_KEYNAME_MAXLEN			32

typedef enum
{
    WOPTION_TYPE_INT,
    WOPTION_TYPE_STRING

}WOption_Type;

struct WOption_Item
{
    FS_INT32		nOptionID;
    FS_INT32		nType;
    const TCHAR*	szSectionName;
    const TCHAR*	szKeyName;
};

class WOptions
{
public:
    WOptions();
    virtual ~WOptions();

    BOOL		SetOptionString(FS_INT32 nOptionID, LPCTSTR lpszValue);
    BOOL		SetOptionInt(FS_INT32 nOptionID, FS_INT32 nValue);
    LPCTSTR		GetOptionString(FS_INT32 nOptionID);
    FS_INT32		    GetOptionInt(FS_INT32 nOptionID);

    VOID		FreeConfig();
    void		SaveConfig();
    BOOL		LoadConfig(LPCTSTR lpszFilePath, const WOption_Item*pItem, FS_INT32 nItemCount);

protected:

    struct WOption_Value
    {
        FS_INT32		nOptionID;
        FS_INT32		nType;
        TCHAR	szSectionName[WOPTION_SECTIONNAME_MAXLEN];
        TCHAR	szKeyName[WOPTION_KEYNAME_MAXLEN];
        union
        {
            TCHAR	szValue[256];
            FS_INT32	nValue;
        };
    };
    WOption_Value*		GetOption(FS_INT32 nOptionID)
    {
        WOption_Value *pItem = NULL;
        if (m_pOption)
        {
            for (FS_INT32 i = 0; i < m_nOptionCount; i++)
            {
                if (m_pOption[i].nOptionID == nOptionID)
                {
                    pItem = m_pOption + i;
                    break;
                }
            }
        }
        return pItem;
    }

    WOption_Value*		m_pOption;
    FS_INT32			m_nOptionCount;
    TCHAR			m_szFilePath[256];
#ifndef _FS_OS_WIN
    XINI			m_xini;
#endif
};
}

#endif //__INC_WOPTIONS_H__
