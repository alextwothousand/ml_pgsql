/*********************************************************
*
*  Multi Theft Auto: San Andreas - Deathmatch
*
*  ml_base, External lua add-on module
*  
*  Copyright (c) 2003-2008 MTA.  All Rights Reserved.
*
*  Grand Theft Auto is (c) 2002-2003 Rockstar North
*
*  THE FOLLOWING SOURCES ARE PART OF THE MULTI THEFT
*  AUTO SOFTWARE DEVELOPMENT KIT AND ARE RELEASED AS
*  OPEN SOURCE FILES. THESE FILES MAY BE USED AS LONG
*  AS THE DEVELOPER AGREES TO THE LICENSE THAT IS
*  PROVIDED WITH THIS PACKAGE.
*
*********************************************************/
#include "CPostgresManager.hpp"


CPostgresManager::CPostgresManager()
{

}


CPostgresManager::~CPostgresManager()
{
    CloseAllConnections();
}


CPostgresConnection* CPostgresManager::NewConnection(lua_State* pLuaVM)
{
    const char* szConnectionInfo = luaL_checkstring(pLuaVM, 1);
    CPostgresConnection* pConnection = new CPostgresConnection(pLuaVM, szConnectionInfo);
    
    g_pPostgresManager->Add(pConnection);

    return pConnection;
}


void CPostgresManager::CloseAllConnections(lua_State* pLuaVM)
{
    int i = 0;
    for (auto& connection : m_vecConnections)
    {
        if (!pLuaVM || (connection && connection->GetVM() == pLuaVM))
        {
            SAFE_DELETE(connection);
            m_vecConnections.erase(m_vecConnections.begin() + i);
        }

        i++;
    }
}

void CPostgresManager::RemoveConnection(CPostgresConnection* pConnection)
{
    int i = 0;
    for (auto& connection : m_vecConnections)
    {
        if(pConnection == connection)
        {
            SAFE_DELETE(connection);
            m_vecConnections.erase(m_vecConnections.begin() + i);
        }

        i++;
    }
}
