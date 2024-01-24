#pragma once
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <queue>
#include <functional>
#include <tinyxml.h>

class Scheduled;
typedef std::shared_ptr<Scheduled> ScheduledPtr;
typedef std::function<void(Scheduled* scheduled)> SCHEDULED_CALLBACK;
enum EUpdateXMLNodeType 
{
	EUNT_NULL = 0,
	EUNT_INSRTY = 1,		// 插入
	EUNT_UPDATE,			// 更新(没用到)
	EUNT_DELETE,			// 删除
};
struct UpdateXMLNodeInfo
{
	uint8_t				type = EUNT_NULL;
	std::string			id = "";
	TiXmlNode*			node = nullptr;
};
enum EScheduledTaskType
{
	ESTT_NULL = 0,
	ESTT_SPECIFIED = 1,	// 指定
	ESTT_YEAR,			// 每年
	ESTT_MONTH,			// 每月
	ESTT_WEEK,			// 每周
	ESTT_DAY,			// 每天
};

// 计划任务
class Scheduled
{
public:
	Scheduled(uint16_t type, uint32_t id, std::string name, SCHEDULED_CALLBACK callback);
	virtual ~Scheduled();

	uint32_t GetId();
	std::string GetName();
	std::string GetParam(const std::string& key);
	bool GetIsInvalid();
	void AddParam(std::string key, std::string value);

	void Update(uint32_t diffMs);
	bool ParseScheduled(const std::vector<std::string>& scheduled);
	UpdateXMLNodeInfo GenerateXMLNode(uint8_t type);
protected:
	virtual void GetNextTimeStamp();

	virtual std::string GetFormatString() = 0;
	virtual void InitAdjustPriorityQueue() = 0;
	virtual void ReAdjustPriorityQueue() = 0;
protected:
	bool								m_beInvalid = false;
	uint64_t							m_buildTimeStamp = 0;
	uint16_t							m_type = EScheduledTaskType::ESTT_NULL;
	uint32_t							m_id = 0;
	std::string							m_name = "";
	std::map<std::string, std::string>	m_paramsMap;
	std::vector<std::string>			m_scheduledStrVec;
	std::vector<tm>						m_scheduledVec;
	std::priority_queue<uint64_t, std::vector<uint64_t>, std::greater<uint64_t>>		m_scheduledDeq;
	uint64_t							m_nextTimeStamp = 0;
	int64_t								m_tick = 0;
	SCHEDULED_CALLBACK					m_callBack;
};

// 指定时间执行一次
class SpecifiedScheduled : public Scheduled
{
public:
	SpecifiedScheduled(uint32_t id, const std::string& name, SCHEDULED_CALLBACK callback);
	virtual ~SpecifiedScheduled();
	// 重写
	virtual void GetNextTimeStamp() override;
	// 实现
	virtual std::string GetFormatString() override;
	virtual void InitAdjustPriorityQueue() override;
	virtual void ReAdjustPriorityQueue() override;
};
// 每年执行一次
class YearScheduled : public Scheduled
{
public:
	YearScheduled(uint32_t id, const std::string& name, SCHEDULED_CALLBACK callback);
	virtual ~YearScheduled();
	// 实现
	virtual std::string GetFormatString() override;
	virtual void InitAdjustPriorityQueue() override;
	virtual void ReAdjustPriorityQueue() override;
};
// 每月执行一次
class MonthScheduled : public Scheduled
{
public:
	MonthScheduled(uint32_t id, const std::string& name, SCHEDULED_CALLBACK callback);
	virtual ~MonthScheduled();
	// 实现
	virtual std::string GetFormatString() override;
	virtual void InitAdjustPriorityQueue() override;
	virtual void ReAdjustPriorityQueue() override;
};
// 每周执行一次
class WeekScheduled : public Scheduled
{
public:
	WeekScheduled(uint32_t id, const std::string& name, SCHEDULED_CALLBACK callback);
	virtual ~WeekScheduled();
	// 实现
	virtual std::string GetFormatString() override;
	virtual void InitAdjustPriorityQueue() override;
	virtual void ReAdjustPriorityQueue() override;
};
// 每天执行一次
class DayScheduled : public Scheduled
{
public:
	DayScheduled(uint32_t id, const std::string& name, SCHEDULED_CALLBACK callback);
	virtual ~DayScheduled();
	// 实现
	virtual std::string GetFormatString() override;
	virtual void InitAdjustPriorityQueue() override;
	virtual void ReAdjustPriorityQueue() override;
};


class IScheduledHelper
{
public:
	static void SetInstance(IScheduledHelper* inst) { m_instance = inst; };
	static IScheduledHelper* GetInstance() { return m_instance; };

	virtual ScheduledPtr AddScheduled(uint16_t, const std::string&, const std::vector<std::string>&, const std::string&, const std::string&) = 0;
	virtual ScheduledPtr AddScheduled(uint16_t, const std::string&, const std::vector<std::string>&, const std::string&, SCHEDULED_CALLBACK) = 0;
	virtual void Update(uint32_t delta) = 0;
private:
	static IScheduledHelper* m_instance;
};
