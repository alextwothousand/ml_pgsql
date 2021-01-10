/*********************************************************
*
*  Multi Theft Auto: San Andreas - Deathmatch
*
*  ml_base, External lua add-on module
*
*  Copyright � 2003-2008 MTA.  All Rights Reserved.
*
*  Grand Theft Auto is � 2002-2003 Rockstar North
*
*  THE FOLLOWING SOURCES ARE PART OF THE MULTI THEFT
*  AUTO SOFTWARE DEVELOPMENT KIT AND ARE RELEASED AS
*  OPEN SOURCE FILES. THESE FILES MAY BE USED AS LONG
*  AS THE DEVELOPER AGREES TO THE LICENSE THAT IS
*  PROVIDED WITH THIS PACKAGE.
*
*********************************************************/
#pragma once

/* Remove MSVC warnings */
#ifdef _MSC_VER
#pragma warning(disable : 4267)
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#endif

/* Module basic configuration */
#define MODULE_NAME		"Postgre.SQL"
#define MODULE_AUTHOR	"Disi"
#define MODULE_VERSION	0.5f

/* MTA-SA Module SDK */
#include "include/Common.h"
#include "include/ILuaModuleManager.h"
#include "include/lua.h"

/* Function-related return values */
#define LUA_FUNCTION_SUCCESS            (1)
#define LUA_FUNCTION_FAILURE            (2)

/* Function-related defines for easier working with API */
#define LUA_FUNCTION_DECLARE(function)  static int function(lua_State* luaVM)
#define LUA_FUNCTION_DEFINE(function)   int function(lua_State* luaVM)
#define LUA_FUNCTION_ASSERT(function, expression) { if(!(expression)) { lua_pushboolean(luaVM, 0); lua_pushstring(luaVM, "Assertation failed in function " function ": " #expression); return LUA_FUNCTION_FAILURE; } }

/* libpq-related errors function interaction */
#define LIBPQ_FINISH_AND_RETURN_ERROR(luavm, connection) { char* errmsg = PQerrorMessage(connection); lua_pushboolean(luavm, 0); lua_pushstring(luavm, errmsg); PQfinish(connection); return LUA_FUNCTION_FAILURE; }
#define LIBPQ_CLEAR_AND_RETURN_ERROR(luavm, connection, result) { lua_pushboolean(luavm, 0); lua_pushstring(luavm, PQerrorMessage(connection)); PQclear(result); return LUA_FUNCTION_FAILURE; }
#define LIBPQ_RETURN_ERROR(luavm, connection) { lua_pushboolean(luavm, 0); lua_pushstring(luavm, PQerrorMessage(connection)); return LUA_FUNCTION_FAILURE; }

/* LUA imports */
#include "luaimports.h"

/* Standard Library useful includes */
#include <memory> // smart pointers
#include <string> // std::string

/* libpq SDK */
#include <libpq-fe.h>

/* Define types here in case we need to change them in the future */
typedef std::string libpq_query_t;