#include "stdafx.h"
#include "TimeHelper.h"
#include <chrono>
#ifdef _WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif
TimeHelper::TimeHelper()
{
	timespec ts;
	auto base = timespec_get(&ts, TIME_UTC);
	auto lt = std::localtime(&ts.tv_sec);
	curTm.tm_year = lt->tm_year;
	curTm.tm_mon = lt->tm_mon;
	curTm.tm_mday = lt->tm_mday;

	timeStamp = GetTimeStamp();
	deltaTime = 0;
}

TimeHelper::~TimeHelper()
{

}

std::string TimeHelper::GetDayString()
{
	timespec ts;
	auto base = timespec_get(&ts, TIME_UTC);
	auto lt = std::localtime(&ts.tv_sec);
	char ret[16] = { 0 };
	sprintf_s(ret, _countof(ret), "%04d-%02d-%02d", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday);
	return ret;
}

std::string TimeHelper::GetCurTimeStrMS()
{
	timespec ts;
	timespec_get(&ts, TIME_UTC);
	auto lt = std::localtime(&ts.tv_sec);
    char buf[32] = {0};
	sprintf_s(buf, _countof(buf), "%04d-%02d-%02d %02d:%02d:%02d %03d",
		lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec, ts.tv_nsec / 1000000);
	return buf;
}

std::string TimeHelper::GetCurTimeStr()
{
    return ConvertTimeToString(time(nullptr));
}

std::string TimeHelper::ConvertTimeToString(time_t seconds, const char *format)
{
    struct tm *p = localtime(&seconds);
    if (!format) format = DTFMTA0;
    char buf[32] = {0};
    strftime(buf, _countof(buf), format, p);
    return buf;
}

time_t TimeHelper::ConvertStringToTime(const char *str, const char *format)
{
    if (!str) return 0;
    if (!format) format = DTFMTB0;

    int year, month, day, hour, minute, second;
    int ret = sscanf_s(str, format, &year, &month, &day, &hour, &minute, &second);
    if (ret != 6) return 0;

    if (year < 1900 || month < 1 || day < 1 || hour < 0 || minute < 0 || second < 0) return 0;

    struct tm when = { 0 };
    when.tm_year = year - 1900;     // Years from 1900
    when.tm_mon = month - 1;        // 0-based
    when.tm_mday = day;             // 1-based

    when.tm_hour = hour;
    when.tm_min = minute;
    when.tm_sec = second;

    // Make sure the daylight savings is same as current timezone.
    static int isdst = -1;
    if (isdst == -1) {
        time_t now = time(nullptr);
        isdst = std::localtime(&now)->tm_isdst;
    }
    when.tm_isdst = isdst;

    // Convert the tm struct to the Linux epoch
    time_t converted;
    converted = mktime(&when);

    return converted;
}

time_t TimeHelper::ConvertStringToTime(const std::string &str, const char *format)
{
    return ConvertStringToTime(str.c_str(), format);
}

time_t TimeHelper::GetTimeStamp()
{
	auto tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
	std::time_t timestamp = tmp.count();
	return timestamp;
}
time_t TimeHelper::GetTimeStamp2() {
	if (m_CurTime == 0)
	{
		return ITimeHelper::GetInstance()->GetTimeStamp();
	}
	return m_CurTime;
}
time_t TimeHelper::GetTimeStamp3() {
#ifdef _WIN32

	if (nbegin == 0)
	{
		LARGE_INTEGER nFreq;
		LARGE_INTEGER begin;
		QueryPerformanceFrequency(&nFreq);
		nQuadPart = nFreq.QuadPart;
		while (true)
		{
			auto timestart = GetTimeStampMillisecond();
			QueryPerformanceCounter(&begin);
			auto timeend = GetTimeStampMillisecond();
			if (timeend - timestart == 1)
			{
				nbegin = begin.QuadPart;
				break;
			}
		}
	}
	LARGE_INTEGER  end;
	double dt;
	QueryPerformanceCounter(&end);
	dt = (end.QuadPart - nbegin) / (double)nQuadPart * 1000000;
	auto x = llround(dt);
	return ITimeHelper::GetInstance()->GetTimeStamp()*1000 + x %1000;
#else
	struct timeval start;
	gettimeofday(&start, NULL);
	return (start.tv_sec) * 1000000 + start.tv_usec;//Î¢Ãë
#endif
}

bool TimeHelper::IsDayChange()
{
	static timespec tsOld;
	timespec ts;
	auto base = timespec_get(&ts, TIME_UTC);
	auto lt = std::localtime(&ts.tv_sec);
	if ((curTm.tm_year != lt->tm_year) || (curTm.tm_mon != lt->tm_mon) || (curTm.tm_mday != lt->tm_mday)) {
		curTm.tm_year = lt->tm_year;
		curTm.tm_mon = lt->tm_mon;
		curTm.tm_mday = lt->tm_mday;
		return true;
	}
	return false;
}

void TimeHelper::CalcDeltaTime()
{
	time_t timeStampNew = GetTimeStamp();
	deltaTime = timeStampNew - timeStamp;
	timeStamp = timeStampNew;
	m_CurTime = timeStampNew;
}

unsigned int TimeHelper::GenerateTimeID(bool loop)
{
	m_sTimerID++;
	m_sTimerID = m_sTimerID % 1000000000;
	return m_sTimerID;
	/*if (loop)
	{
		m_sTimerID++;
		m_sTimerID = m_sTimerID % 1000000000;
		return m_sTimerID + 1000000000;
	}
	else
	{
		m_sTempTimerID++;
		m_sTempTimerID = m_sTempTimerID % 1000000000;
		return m_sTempTimerID;
	}*/
}

unsigned int TimeHelper::AddTimer(TimerData& timer, bool about)
{
	timer.id = GenerateTimeID(timer.loop);
	timer.invalid = false;
	timer.tick = 0;
	if (about)
	{
		timer.tick64 = GetTimeStampMillisecond2() + timer.interval;
		timerListTemp_1000.push_back(timer);
	}
	else
	{
		timer.tick64 = GetTimeStampMillisecond() + timer.interval;
		timerListTemp.push_back(timer);
	}
	return timer.id;
}

unsigned int TimeHelper::AddTimer(unsigned int interval, bool loop, TIMER_CALLBACK callback, bool about)
{
    TimerData timer;

    timer.id = GenerateTimeID(loop);
    timer.interval = interval;
    timer.loop = loop;
    timer.invalid = false;
    timer.tick = 0;
    timer.callBack = std::move(callback);
	if (about)
	{
		timer.tick64 = GetTimeStampMillisecond2() + interval;
		timerListTemp_1000.emplace_back(std::move(timer));
	}
	else
	{
		timer.tick64 = GetTimeStampMillisecond() + interval;
		timerListTemp.emplace_back(std::move(timer));
	}
    return timer.id;
}

void TimeHelper::RemoveTimer(unsigned int id, bool about)
{
	for (auto iter = timerListTemp_1000.begin(); iter != timerListTemp_1000.end(); ++iter) {
		if (iter->id == id) {
			iter->invalid = true;
			return;
		}
	}
	for (auto iter = timerListTemp.begin(); iter != timerListTemp.end(); ++iter) {
		if (iter->id == id) {
			iter->invalid = true;
			return;
		}
	}

	for (auto imter = timerListMap.begin(); imter != timerListMap.end(); ++imter)
	{
		for (auto iter = imter->second.begin(); iter != imter->second.end(); ++iter) {
			if (iter->id == id) {
				iter->invalid = true;
				return;
			}
		}
	}
}

uint32_t TimeHelper::GetLoopTimeNum()
{
	return timerListMap[0].size();
}

TimerData* TimeHelper::GetTimer(unsigned int id)
{
	for (auto iter = timerListTemp.begin(); iter != timerListTemp.end(); ++iter) {
		if (iter->id == id) {
			return &(*iter);
		}
	}
	for (auto iter = timerListTemp_1000.begin(); iter != timerListTemp_1000.end(); ++iter) {
		if (iter->id == id) {
			return &(*iter);
		}
	}

	for (auto imter = timerListMap.begin(); imter != timerListMap.end(); ++imter)
	{
		for (auto iter = imter->second.begin(); iter != imter->second.end(); ++iter) {
			if (iter->id == id) {
				return &(*iter);
			}
		}
	}

	return nullptr;
}


void TimeHelper::Update(unsigned int delta)
{
	auto temptick = GetTimeStampMillisecond();
	
	for (auto iter = timerListMap[0].begin(); iter != timerListMap[0].end();) {
		if (iter->invalid) {
			iter = timerListMap[0].erase(iter);
			continue;
		}
		++iter;
	}
	
	for (auto iter = timerListTemp.begin(); iter != timerListTemp.end(); ++iter) {
		if (!iter->invalid) {
			auto timestamp = (iter->tick64/10+1)*10;
			if (iter->loop)
			{
				timestamp = 0;
			}
			timerListMap[timestamp].push_back(std::move(*iter));
		}
	}
	timerListTemp.clear();

	for (auto iter = timerListTemp_1000.begin(); iter != timerListTemp_1000.end(); ++iter) {
		if (!iter->invalid) {
			auto timestamp = (iter->tick64 / 1000 + 1) * 1000;
			if (iter->loop)
			{
				timestamp = 0;
			}
			timerListMap[timestamp].push_back(std::move(*iter));
		}
	}
	timerListTemp_1000.clear();

	
	for (auto imter = timerListMap.begin(); imter != timerListMap.end(); )
	{
		if (imter->first <= temptick)
		{
			for (auto iter = imter->second.begin(); iter != imter->second.end(); ++iter) {
				if (iter->tick64 <= temptick && !iter->invalid) {
					OnTimer(*iter,temptick);
				}
			}
			if (imter->first != 0)
			{
				imter = timerListMap.erase(imter);
				continue;
			}
		}
		++imter;
	}

	/*for (auto itr : funListMap)
	{
		LOG_NORMAL("name: %s, cost: %ld", itr.first.c_str(), itr.second);
	}
	funListMap.clear();*/
}

void TimeHelper::OnTimer(TimerData& timer,time_t temptick)
{
	if (timer.loop) {
		//timer.tick -= timer.interval;
		timer.tick64 = temptick + timer.interval;
	}
	else {
		timer.invalid = true;
	}

	if (nullptr != timer.callBack) {
		//auto starttick = GetTimeStampMillisecond3();
		timer.callBack(timer);
		//auto endtick = GetTimeStampMillisecond3();
		//auto str = GetStrData(timer.id, "name");
		//funListMap[str] += endtick - starttick;
	}
}

time_t TimeHelper::GetEndOfDay()
{
    time_t cur = time(nullptr);

    auto *lt = localtime(&cur);

    lt->tm_hour = 23;
    lt->tm_min = 59;
    lt->tm_sec = 59;

    return mktime(lt);
}

uint32_t TimeHelper::GetTimeSecOfDayEnd()
{
	time_t cur = time(nullptr);
	time_t dayEnd = GetEndOfDay();
	return uint32_t(dayEnd - cur + 1);
}

void TimeHelper::AddNumData(uint32_t id, const std::string& key, uint32_t val)
{
	auto timer = GetTimer(id);
	if (nullptr != timer) {
		timer->NumData[key] = val;
	}
}

uint32_t TimeHelper::GetNumData(unsigned int id, const std::string& key)
{
	auto timer = GetTimer(id);
	if (nullptr != timer && timer->NumData.find(key) != timer->NumData.end()) {
		return timer->NumData[key];
	}
	return 0;
}

void TimeHelper::RemoveNumData(unsigned int id, const std::string& key)
{
	auto timer = GetTimer(id);
	if (nullptr != timer) {
		auto iter = timer->NumData.find(key);
		if (iter != timer->NumData.end()) {
			timer->NumData.erase(iter);
		}
	}
}

void TimeHelper::AddStrData(uint32_t id, const std::string& key, const std::string& val)
{
	auto timer = GetTimer(id);
	if (nullptr != timer) {
		timer->StrData[key] = val;
	}
}

const std::string TimeHelper::GetStrData(unsigned int id, const std::string& key)
{
	auto timer = GetTimer(id);
	if (nullptr != timer && timer->StrData.find(key) != timer->StrData.end()) {
		return timer->StrData[key];
	}
	return "";
}

void TimeHelper::RemoveStrData(unsigned int id, const std::string& key)
{
	auto timer = GetTimer(id);
	if (nullptr != timer) {
		auto iter = timer->StrData.find(key);
		if (iter != timer->StrData.end()) {
			timer->StrData.erase(iter);
		}
	}
}
