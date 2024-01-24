#include "stdafx.h"
#include "StringHelper.h"

#ifdef _WIN32
#include <shlwapi.h>
#endif

const char * stristr(const char *haystack, const char *needle)
{
    if (!haystack || !needle) return nullptr;

#ifdef _WIN32
    return StrStrIA(haystack, needle);
#else
    return strcasestr(haystack, needle);
#endif
}
