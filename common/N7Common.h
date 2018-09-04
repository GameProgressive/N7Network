/*
    This file is part of N7Network.

    N7Network is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    N7Network is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with N7Network.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _N7COMMON_H_
#define _N7COMMON_H_

#include <MDK/ModuleEntryPoint.h>

#include <string>

#if _WIN32 && _MSC_VER
#include <Windows.h>
#ifdef __cplusplus
#define N7ModuleStart extern "C" { __declspec(dllexport) int MDKModule(void* data) {
#else
#define N7ModuleStart __declspec(dllexport) int MDKModule(void* data) {
#endif
#else
#ifdef __cplusplus
#define N7ModuleStart extern "C" { int MDKModule(void* data) {
#else
#define N7ModuleStart int MDKModule(void* data) {
#endif
#endif
#ifdef __cplusplus
#define N7ModuleEnd Server->Run(); return ERROR_NONE; }}
#else
#define N7ModuleEnd return ERROR_NONE; }
#endif

#define GS_REQUEST_LEN				20
#define GS_GAMENAME_LEN				64
#define GP_EMAIL_LEN				51
#define GP_PASSWORD_LEN				31
#define GP_PASSWORDENC_LEN			((((GP_PASSWORD_LEN+2)*4)/3)+1)
#define GP_PARTNERID_LEN			sizeof(int)
#define GP_NAMESPACEID_LEN			sizeof(int)
#define GP_NICK_LEN                 31
#define GP_UNIQUENICK_LEN           21
#define GP_XOR_SEED                 0x79707367 // "gspy"
#define GP_STATUS_STRING_LEN        256
#define GP_FIRSTNAME_LEN            31
#define GP_LASTNAME_LEN             31
#define GP_HOMEPAGE_LEN             76
#define GP_ZIPCODE_LEN              11
#define GP_COUNTRYCODE_LEN          3
#define GP_AIMNAME_LEN              51
#define GP_LOGIN_TICKET_LEN         25
#define GP_LOCATION_STRING_LEN      256
#define GS_PARTNER_ID				0
#define GP_SERVERCHALL_LEN			11
#define GP_AUTHTOKEN_LEN			256
#define GP_PARTNERCHALLENGE_LEN     256
#define GP_CLIENTCHALL_LEN			64
#define GP_PLACE_LEN                128

#define MD5_BUFFER_LEN				33

#endif
