#include "stdafx.h"
#include "IScheduledHelper.h"
#include "ITimeHelper.h"
#include "StringHelper.h"
#include <sstream>
#include <iomanip>
#include <chrono>

#define SECOND_PER_HOUR			3600
#define SECOND_PER_DAY			86400

#define XML_NODE_ID_PREFIX		"Id_"
IScheduledHelper* IScheduledHelper::m_instance = nullptr;

Scheduled::Scheduled(uint16_t type, uint32_t id, std::string name, SCHEDULED_CALLBACK callback) :
	m_type(type), m_id(id), m_name(std::move(name)), m_callBack(callback), m_beInvalid(false)
{
	m_buildTimeStamp = (uint64_t)GetTimeStampMillisecond();
	m_paramsMap.clear();
	m_scheduledStrVec.clear();
	m_scheduledVec.clear();
}

Scheduled::~Scheduled()
{
	m_paramsMap.clear();
	m_scheduledStrVec.clear();
	m_scheduledVec.clear();
}

uint32_t Scheduled::GetId()
{
	return m_id;
}

std::string Scheduled::GetName()
{
	return m_name;
}

std::string Scheduled::GetParam(const std::string& key)
{
	auto iter = m_paramsMap.find(key);
	if (iter == m_paramsMap.end()) return "";

	return iter->second;
}

bool Scheduled::GetIsInvalid()
{
	return m_beInvalid;
}

void Scheduled::AddParam(std::string key, std::string value)
{
	m_paramsMap.emplace(std::move(key), std::move(value));
}

void Scheduled::Update(uint32_t diffMs)
{
	if (m_beInvalid) return;

	m_tick += diffMs;
	if (m_buildTimeStamp + m_tick >= m_nextTimeStamp)
	{
		if (m_callBack) m_callBack(this);
		GetNextTimeStamp();
	}
}

bool Scheduled::ParseScheduled(const std::vector<std::string>& scheduled)
{
	if (scheduled.empty()) return false;

	std::stringstream s;
	tm timeinfo;
	std::string formatStr = "";
	for (auto& ele : scheduled)
	{
		memset(&timeinfo, 0, sizeof(tm));
		formatStr = GetFormatString();
		s << ele;
		s >> std::get_time(&timeinfo, formatStr.c_str());
		s.str(""); s.clear();
		m_scheduledVec.push_back(timeinfo);
		m_scheduledStrVec.push_back(ele);
	}
	InitAdjustPriorityQueue();
	GetNextTimeStamp();
	return true;
}

UpdateXMLNodeInfo Scheduled::GenerateXMLNode(uint8_t type)
{
	UpdateXMLNodeInfo info;
	info.type = type;
	info.id = XML_NODE_ID_PREFIX + std::to_string(m_id);
	TiXmlElement node(info.id.c_str());
	node.SetAttribute("Type", m_type);
	node.SetAttribute("Name", ESCA2UTF8P(m_name));
	if (type == EUNT_DELETE) return info;

	{
		TiXmlElement childScheduled("Scheduleds");
		for (const auto& ele : m_scheduledStrVec)
		{
			TiXmlElement scheduled("Scheduled");
			scheduled.SetAttribute("Value", ESCA2UTF8P(ele));
			childScheduled.InsertEndChild(scheduled);
		}
		node.InsertEndChild(childScheduled);
	}
	{
		TiXmlElement childParams("Params");
		for (const auto& ele : m_paramsMap)
		{
			TiXmlElement param("Param");
			param.SetAttribute("Key", ESCA2UTF8P(ele.first));
			param.SetAttribute("Value", ESCA2UTF8P(ele.second));
			childParams.InsertEndChild(param);
		}
		node.InsertEndChild(childParams);
	}

	info.node = node.Clone();
	//info.node->Print(stdout, 0);
	return info;
}

void Scheduled::GetNextTimeStamp()
{
	while (m_scheduledDeq.empty())
	{
		ReAdjustPriorityQueue();
	}
	m_nextTimeStamp = m_scheduledDeq.top();
	m_scheduledDeq.pop();
}
///////////////////////////////////////////////////////ok
SpecifiedScheduled::SpecifiedScheduled(uint32_t id, const std::string& name, SCHEDULED_CALLBACK callback) :
	Scheduled((uint16_t)EScheduledTaskType::ESTT_SPECIFIED, id, name, callback)
{
}

SpecifiedScheduled::~SpecifiedScheduled()
{
}

std::string SpecifiedScheduled::GetFormatString()
{
	return "%Y-%m-%d %H:%M:%S";
}

void SpecifiedScheduled::InitAdjustPriorityQueue()
{
	for (auto& timeinfo : m_scheduledVec)
	{
		uint64_t cutTimeStamp = (uint64_t)GetTimeStampMillisecond();
		uint64_t timeStamp = (uint64_t)S2MS(mktime(&timeinfo));
		if (cutTimeStamp > timeStamp) continue;

		m_scheduledDeq.push(timeStamp);
	}
}

void SpecifiedScheduled::ReAdjustPriorityQueue()
{
	// 空
}

void SpecifiedScheduled::GetNextTimeStamp()
{
	if (m_scheduledDeq.empty())
	{
		m_beInvalid = true;
		return;
	}
	m_nextTimeStamp = m_scheduledDeq.top();
	m_scheduledDeq.pop();
}
///////////////////////////////////////////////////////ok
YearScheduled::YearScheduled(uint32_t id, const std::string& name, SCHEDULED_CALLBACK callback) :
	Scheduled((uint16_t)EScheduledTaskType::ESTT_YEAR, id, name, callback)
{
}

YearScheduled::~YearScheduled()
{
}

std::string YearScheduled::GetFormatString()
{
	return "%m-%d %H:%M:%S";
}

void YearScheduled::InitAdjustPriorityQueue()
{
	auto cutTimeStamp = (uint64_t)GetTimeStampMillisecond();
	for (auto& timeinfo : m_scheduledVec)
	{
		time_t cutTimeStampSecond = MS2S(cutTimeStamp);
		tm* now = std::localtime(&cutTimeStampSecond);
		if (!now) continue;

		timeinfo.tm_year = now->tm_year;
		uint64_t timeStamp = (uint64_t)S2MS(mktime(&timeinfo));
		if (cutTimeStamp > timeStamp) continue;

		m_scheduledDeq.push(timeStamp);
	}
}

void YearScheduled::ReAdjustPriorityQueue()
{
	auto cutTimeStamp = (uint64_t)GetTimeStampMillisecond();
	for (auto& timeinfo : m_scheduledVec)
	{
		timeinfo.tm_year += 1;
		uint64_t timeStamp = (uint64_t)S2MS(mktime(&timeinfo));
		if (cutTimeStamp > timeStamp) continue;

		m_scheduledDeq.push(timeStamp);
	}
	// m_buildTimeStamp = cutTimeStamp;
	// m_tick = 0;
}
///////////////////////////////////////////////////////ok
MonthScheduled::MonthScheduled(uint32_t id, const std::string& name, SCHEDULED_CALLBACK callback) :
	Scheduled((uint16_t)EScheduledTaskType::ESTT_MONTH, id, name, callback)
{
}

MonthScheduled::~MonthScheduled()
{
}

std::string MonthScheduled::GetFormatString()
{
	return "%d %H:%M:%S";
}

void MonthScheduled::InitAdjustPriorityQueue()
{
	auto cutTimeStamp = (uint64_t)GetTimeStampMillisecond();
	for (auto& timeinfo : m_scheduledVec)
	{
		time_t cutTimeStampSecond = MS2S(cutTimeStamp);
		tm* now = std::localtime(&cutTimeStampSecond);
		if (!now) continue;

		timeinfo.tm_year = now->tm_year;
		timeinfo.tm_mon = now->tm_mon;
		uint64_t timeStamp = (uint64_t)S2MS(mktime(&timeinfo));
		if (cutTimeStamp > timeStamp) continue;

		m_scheduledDeq.push(timeStamp);
	}
}

void MonthScheduled::ReAdjustPriorityQueue()
{
	auto cutTimeStamp = (uint64_t)GetTimeStampMillisecond();
	for (auto& timeinfo : m_scheduledVec)
	{
		timeinfo.tm_mon = (timeinfo.tm_mon + 1) % 12;
		if (timeinfo.tm_mon == 0) timeinfo.tm_year += 1;
		uint64_t timeStamp = (uint64_t)S2MS(mktime(&timeinfo));
		if (cutTimeStamp > timeStamp) continue;

		m_scheduledDeq.push(timeStamp);
	}
	// m_buildTimeStamp = cutTimeStamp;
	// m_tick = 0;
}
///////////////////////////////////////////////////////ok
WeekScheduled::WeekScheduled(uint32_t id, const std::string& name, SCHEDULED_CALLBACK callback) :
	Scheduled((uint16_t)EScheduledTaskType::ESTT_WEEK, id, name,  callback)
{
}

WeekScheduled::~WeekScheduled()
{
}

std::string WeekScheduled::GetFormatString()
{
	return "%w %H:%M:%S";
}

void WeekScheduled::InitAdjustPriorityQueue()
{
	auto cutTimeStamp = (uint64_t)GetTimeStampMillisecond();
	for (auto& timeinfo : m_scheduledVec)
	{
		time_t cutTimeStampSecond = MS2S(cutTimeStamp);
		// 上一个周日0点
		auto weekBeginTimeStampSecond = (cutTimeStampSecond - (4 * 24 + 8)* SECOND_PER_HOUR/*周四8点374400*/) - cutTimeStampSecond % (SECOND_PER_DAY * 7);
		auto timeStampSecond = weekBeginTimeStampSecond + timeinfo.tm_wday * SECOND_PER_DAY;
		tm* now = std::localtime(&timeStampSecond);
		if (!now) continue;

		timeinfo.tm_year = now->tm_year;
		timeinfo.tm_mon = now->tm_mon;
		timeinfo.tm_mday = now->tm_mday;
		uint64_t timeStamp = (uint64_t)S2MS(mktime(&timeinfo));
		if (cutTimeStamp > timeStamp) continue;

		m_scheduledDeq.push(timeStamp);
	}
}

void WeekScheduled::ReAdjustPriorityQueue()
{
	auto cutTimeStamp = (uint64_t)GetTimeStampMillisecond();
	for (auto& timeinfo : m_scheduledVec)
	{
		auto timeStamp = S2MS((uint64_t)mktime(&timeinfo) + (SECOND_PER_DAY * 7));
		time_t timeStampSecond = MS2S(timeStamp);
		tm* now = std::localtime(&timeStampSecond);
		if (!now) continue;

		timeinfo.tm_year = now->tm_year;
		timeinfo.tm_mon = now->tm_mon;
		timeinfo.tm_mday = now->tm_mday;
		if (cutTimeStamp > timeStamp) continue;

		m_scheduledDeq.push(timeStamp);
	}
	// m_buildTimeStamp = cutTimeStamp;
	// m_tick = 0;
}
///////////////////////////////////////////////////////
DayScheduled::DayScheduled(uint32_t id, const std::string& name, SCHEDULED_CALLBACK callback) :
	Scheduled((uint16_t)EScheduledTaskType::ESTT_DAY, id, name, callback)
{
}

DayScheduled::~DayScheduled()
{
}

std::string DayScheduled::GetFormatString()
{
	return "%H:%M:%S";
}

void DayScheduled::InitAdjustPriorityQueue()
{
	auto cutTimeStamp = (uint64_t)GetTimeStampMillisecond();
	for (auto& timeinfo : m_scheduledVec)
	{
		time_t cutTimeStampSeconds = MS2S(cutTimeStamp);
		tm* now = std::localtime(&cutTimeStampSeconds);
		if (!now) continue;

		timeinfo.tm_year = now->tm_year;
		timeinfo.tm_mon = now->tm_mon;
		timeinfo.tm_mday = now->tm_mday;
		uint64_t timeStamp = (uint64_t)S2MS(mktime(&timeinfo));
		if (cutTimeStamp > timeStamp) continue;

		m_scheduledDeq.push(timeStamp);
	}
}

void DayScheduled::ReAdjustPriorityQueue()
{
	auto cutTimeStamp = (uint64_t)GetTimeStampMillisecond();
	for (auto& timeinfo : m_scheduledVec)
	{
		auto timeStamp = S2MS((uint64_t)mktime(&timeinfo) + SECOND_PER_DAY);
		time_t timeStampSecond = MS2S(timeStamp);
		tm* now = std::localtime(&timeStampSecond);
		if (!now) continue;

		timeinfo.tm_year = now->tm_year;
		timeinfo.tm_mon = now->tm_mon;
		timeinfo.tm_mday = now->tm_mday;
		if (cutTimeStamp > timeStamp) continue;

		m_scheduledDeq.push(timeStamp);
	}
	// m_buildTimeStamp = cutTimeStamp;
	// m_tick = 0;
}