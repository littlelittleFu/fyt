#pragma once
#include <string>
#include <map>
#include <functional>


#define DTFMTA0     "%F %T"
#define DTFMTA1     "%Y/%m/%d %T"
#define DTFMTA2     "%Y_%m_%d %T"
#define DTFMTA3     "%Y%m%d%H%M%S"

#define DTFMTB0     "%d-%d-%d %d:%d:%d"
#define DTFMTB1     "%d/%d/%d %d:%d:%d"

#define MS2S(ms)    ((ms) / 1000)
#define S2MS(s)     ((s) * 1000)


struct TimerData;
typedef std::function<void(const TimerData& timer)> TIMER_CALLBACK;

struct TimerData
{
	unsigned int id;
	unsigned int interval;
	bool loop;
	bool invalid;
	int tick;
	time_t tick64;
	TIMER_CALLBACK callBack;
	std::map<std::string,uint32_t> NumData;
	std::map<std::string,std::string> StrData;
};

class ITimeHelper
{
public:
	static void SetInstance(ITimeHelper* inst) { m_instance = inst; };
	static ITimeHelper* GetInstance() { return m_instance; };

	virtual std::string GetDayString() = 0;
	virtual std::string GetCurTimeStrMS() = 0;
    virtual std::string GetCurTimeStr() = 0;
    virtual std::string ConvertTimeToString(time_t seconds, const char *format = DTFMTA0) = 0;
    virtual time_t ConvertStringToTime(const char *str, const char *format = DTFMTB0) = 0;
    virtual time_t ConvertStringToTime(const std::string &str, const char *format = DTFMTB0) = 0;
	virtual time_t GetTimeStamp() = 0;
	virtual bool IsDayChange() = 0;
	virtual void CalcDeltaTime() = 0;
	virtual unsigned int GetDeltaTime() = 0;
	virtual unsigned int AddTimer(TimerData& timer, bool about = false) = 0;
    virtual unsigned int AddTimer(unsigned int interval, bool loop, TIMER_CALLBACK callback, bool about = false) = 0;
	virtual void RemoveTimer(unsigned int id, bool about = false) = 0;
	virtual void Update(unsigned int delta) = 0;
	virtual TimerData* GetTimer(unsigned int id) = 0;
    virtual time_t GetEndOfDay() = 0;
	virtual uint32_t GetTimeSecOfDayEnd() = 0;
	virtual time_t GetTimeStamp2() = 0;
	virtual time_t GetTimeStamp3() = 0;
	virtual uint32_t GetLoopTimeNum() = 0;

	virtual void AddNumData(uint32_t id, const std::string& key, uint32_t val) = 0;
	virtual uint32_t GetNumData(unsigned int id, const std::string& key) = 0;
	virtual void RemoveNumData(unsigned int id, const std::string& key) = 0;
	virtual void AddStrData(uint32_t id, const std::string& key, const std::string& val) = 0;
	virtual const std::string GetStrData(unsigned int id, const std::string& key) = 0;
	virtual void RemoveStrData(unsigned int id, const std::string& key) = 0;

private:
	static ITimeHelper* m_instance;
};

#define GetTimeStampMillisecond() (ITimeHelper::GetInstance()->GetTimeStamp())
#define GetTimeStampMillisecond2() (ITimeHelper::GetInstance()->GetTimeStamp2())
#define GetTimeStampMillisecond3() (ITimeHelper::GetInstance()->GetTimeStamp3())