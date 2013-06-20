// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// The following macros define the minimum required platform.  The minimum required platform
// is the earliest version of Windows, Internet Explorer etc. that has the necessary features to run 
// your application.  The macros work by enabling all features available on platform versions up to and 
// including the version specified.

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

typedef unsigned __int64 uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <limits.h>

#define GET64(hi,lo) ((((uint64_t)(hi))<<32LL)|((uint64_t)(lo)))
#define LBS52(x) (x & 0x000FFFFFFFFFFFFFLL)
#define LBS48(x) (x & 0x0000FFFFFFFFFFFFLL)
#define LBS40(x) (x & 0x000000FFFFFFFFFFLL)
#define LBS32(x) (x &         0xFFFFFFFFLL)
#define LBS30(x) (x &         0x3FFFFFFFLL)
#define LBS28(x) (x &         0x0FFFFFFFLL)
#define LBS26(x) (x &         0x03FFFFFFLL)
#define LBS24(x) (x &         0x00FFFFFFLL)
#define LBS16(x) (x &         0x0000FFFFLL)

void DisplayMessageDigest(uint32_t sha1hash[5]);