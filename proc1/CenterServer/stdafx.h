#pragma once

#include <string>
#include <vector>
#include <list>
#include <set>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <tuple>
#include <typeinfo>
#include <algorithm>
#include <stdint.h>
#include <stdlib.h>
#include <utility>
#include <random>
#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>
#include <functional>
#include <cstdint>
#include <codecvt>
#include <assert.h>
#include <stdexcept>
#include <iterator>
#include <inttypes.h>
#include <cstring>

#include <inifile.h>
#include <curl.h>
#include <ctpl_stl.h>

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <WinService.h>
#else
#include <signal.h>
#endif

#include "spec.h"
#include "PortToLinux.h"
#include "DataInfo.hpp"
#include "logic_def.hpp"
#include "Types.h"
#include "Tools.h"
#include "ObjID.h"
#include "ClientErrorCode.h"
#include "ErrorCode.h"
#include "ErrorMsg.h"
#include "TimeHelper.h"
#include "iconv.h"
#include "StringHelper.h"
#include "LogHelper.h"
#include "FileHelper.h"
#include "CsvHelper.h"
#include "AES.h"
#include "SessionFactory.h"
#include "Utility.h"
#include "LuaWrap.h"
#include "LuaEngine.h"
#include "EventTrigger.h"
#include "Globle.h"
//#include "CLuaLib.h"

#include "GameCfgMgr.h"
#include "ConfigInfo.h"
#include "SessionCS2Log.h"
#include "CBufManager.h"
#include "MsgCostStat.h"

//#include "tinyxml.h"
#include "json.h"
#include "MD5.h"
//#include "zlib.h"