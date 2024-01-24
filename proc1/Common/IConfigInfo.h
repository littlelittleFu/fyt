#ifndef  _ICONFIG_INFO_H_
#pragma once

#define CHECK_WHITE_IP_PATH "/test/getwhiteip"
#define CHECK_TOKEN_PATH "/api/verifyLogin"
#define REDEMPTION_CODE_PATH "/api/drawCode"
#define MONITOR_CHAT_PATH "/chatMonitor/syncData"
#define REPORT_ROLE_PATH "/report/role"
#define GIFT_CODE_PATH "/api/game_draw_activity_gift"
#define TRADE_CODE_PATH "/api/transWarning"
#define UPDATE_REBATE_CODE_PATH "/api/update_rebate_money"
#define GET_REBATE_CODE_PATH "/api/get_rebate_money"
#define GET_WHITE_ACCOUNT_NAME "/api/get_account_white_list"

class IConfigInfo
{
public:
	virtual uint32_t GetCurAgentId() = 0;       // 代理ID
	virtual uint32_t GetCurAreaId() = 0;		// 区ID
	virtual uint32_t GetCurAreaServerId() = 0;  // 区服ID
	virtual uint32_t GetCurServerId() = 0;      // 服务器ID
};

#endif // ! _I_ICONFIG_INFO_H_
