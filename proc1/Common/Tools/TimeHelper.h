#pragma once


#include <string>
#include <list>
#include "ITimeHelper.h"
#include <vector>
#include <iomanip>
#include <sstream>
#include <unordered_map>

class TimeHelper : public ITimeHelper
{
public:
	TimeHelper();
	virtual ~TimeHelper();
	
public:
	std::string GetDayString() override;
	std::string GetCurTimeStrMS() override;
    std::string GetCurTimeStr() override;
    std::string ConvertTimeToString(time_t seconds, const char *format = DTFMTA0) override;
    time_t ConvertStringToTime(const char *str, const char *format = DTFMTB0) override;
    time_t ConvertStringToTime(const std::string &str, const char *format = DTFMTB0) override;
	time_t GetTimeStamp() override;
	bool IsDayChange() override;
	void CalcDeltaTime() override;
	unsigned int GetDeltaTime() override { return deltaTime; }
	unsigned int AddTimer(TimerData& timer,bool about = false) override;//for c++ use
    unsigned int AddTimer(unsigned int interval, bool loop, TIMER_CALLBACK callback, bool about = false) override;
	void RemoveTimer(unsigned int id, bool about = false) override;
	void Update(unsigned int delta) override;
	virtual void OnTimer(TimerData& timer, time_t temptick);
	TimerData* GetTimer(unsigned int id) override;
    time_t GetEndOfDay() override;
	uint32_t GetTimeSecOfDayEnd() override;
	uint32_t GetLoopTimeNum() override;

	void AddNumData(uint32_t id, const std::string& key, uint32_t val) override;
	uint32_t GetNumData(unsigned int id, const std::string& key) override;
	void RemoveNumData(unsigned int id, const std::string& key) override;
	void AddStrData(uint32_t id, const std::string& key, const std::string& val) override;
	const std::string GetStrData(unsigned int id, const std::string& key) override;
	void RemoveStrData(unsigned int id, const std::string& key) override;
	time_t GetTimeStamp2() override;
	time_t GetTimeStamp3() override;
protected:
	unsigned int GenerateTimeID(bool loop);

protected:
	tm curTm;
	time_t timeStamp;
	unsigned int deltaTime;
	unsigned int m_sTimerID;
	unsigned int m_sTempTimerID;
	std::list<TimerData> timerList;
	std::list<TimerData> timerListTemp;
	std::list<TimerData> timerListTemp_1000;			//降低循环次数
	std::unordered_map<time_t, std::list<TimerData>> timerListMap;
	//std::unordered_map<std::string, time_t> funListMap;
	time_t m_CurTime = 0;//据说GetTimeStamp 频繁使用会卡 不重要的用新的

	time_t nQuadPart = 0;
	time_t nbegin = 0;
};
