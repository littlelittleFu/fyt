#ifndef SRV_COM_LIB_STDAFX_H
#define SRV_COM_LIB_STDAFX_H

#include <cstdint>
#include <cstring>
#include <cassert>

#include <string>
#include <algorithm>

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#endif

#include "spec.h"
#include "IConfigInfo.h"

#include "PortToLinux.h"

#include "netdata.h"
#include "DataInfo.hpp"

#include "StringHelper.h"
#include "Types.h"

#include "logic_def.hpp"
#include "CsvHelper.h"
#include "GameCfgMgr.h"

#endif
