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
#include <bitset>
#include <array>

#include "tinyxml.h"
#include "json/json.h"
#include "zlib.h"

#include <inifile.h>
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
#include "Role/logic_def.hpp"
#include "Types.h"
#include "Type.h"
#include "Tools.h"
#include "ObjID.h"
#include "ClientErrorCode.h"
#include "ErrorCode.h"
#include "ErrorMsg.h"
#include "TimeHelper.h"
#include "ScheduledHelper.h"
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
#include "CLuaLib.h"

#include "GameCfgMgr.h"
#include "ConfigInfo.h"
#include "SessionMS2Log.h"
#include "SessionMS2CS.h"
#include "CBufManager.h"
#include "MsgCostStat.h"

#include "exp_common.h"
#include "buff_prop_exp.h"
#include "skill_prop_exp.h"
#include "quest_prop_exp.h"
#include "map_prop_exp.h"
#include "role_prop_exp.h"
#include "global_prop_exp.h"
#include "monster_prop_exp.h"
#include "item_prop_exp.h"
#include "group_attr_prop_exp.h"
#include "buff_group_exp.h"
#include "npc_prop_exp.h"
#include "title_prop_exp.h"