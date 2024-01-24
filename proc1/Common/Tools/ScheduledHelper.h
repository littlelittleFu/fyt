#pragma once


#include <string>
#include <list>
#include "IScheduledHelper.h"
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

#define CallBackParamKey "CallbackParamKey"
#define CallBackFuncNameKey "CallbackFuncNameKey"

typedef std::function<ScheduledPtr(uint32_t, const std::string&, SCHEDULED_CALLBACK)> SchedulePtrBuilder;
class ScheduledHelper : public IScheduledHelper
{
public:
	ScheduledHelper();
	virtual ~ScheduledHelper();
	
public:
	virtual ScheduledPtr AddScheduled(uint16_t type, const std::string& name, const std::vector<std::string>& scheduled,
		const std::string& params, const std::string& callBackFunc) override;
	virtual ScheduledPtr AddScheduled(uint16_t type, const std::string& name, const std::vector<std::string>& scheduled,
		const std::string& params, SCHEDULED_CALLBACK callBackFunc) override;
	virtual void Update(uint32_t delta) override;
protected:
	ScheduledPtr CreateScheduled(uint16_t type, const std::string& name, const std::vector<std::string>& scheduled,
		const std::string& params, SCHEDULED_CALLBACK MyCallBackFunc, const std::string& MyCallBackFuncName = "");
	uint32_t GenerateScheduledId();
	void UpdateXmlDocument(UpdateXMLNodeInfo& updateInfo);
	void Enqueue(const UpdateXMLNodeInfo& updateInfo);
	void InitXMLDocument();
	void InitThread();
	void ShutDownThread();
	void RestoreScheduledData();
	void MergeScheduled();
protected:
	TiXmlDocument		m_doc;
	TiXmlNode*			m_rootNode = nullptr;
	std::atomic<bool>	m_run{false};
	std::thread			m_thread;
	std::mutex			m_mutex;
	std::condition_variable m_cv;
	std::list<UpdateXMLNodeInfo> m_taskDeq;

	uint32_t m_sheduledId;
	std::map<uint32_t, ScheduledPtr> m_scheduledPtrMap;
	std::map<uint32_t, ScheduledPtr> m_tmpScheduledPtrMap;

	static std::map<uint16_t, SchedulePtrBuilder> m_builder;
};
