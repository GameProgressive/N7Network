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

#include <MDK/MasterServerMDK.h>

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

extern void get_param_data(const char *data, const char* what, const char* out, size_t out_len);

#endif
