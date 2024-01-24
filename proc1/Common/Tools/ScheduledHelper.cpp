#include "stdafx.h"
#include "ScheduledHelper.h"
#include "Lua/LuaEngine.h"


static inline void CallBackFunc(Scheduled* scheduled)
{
	if (scheduled)
	{
		LuaBindCallVoid(scheduled->GetParam(CallBackFuncNameKey), scheduled->GetId(), scheduled->GetName(), scheduled->GetParam(CallBackParamKey));
	}
}


#define SCHEDULED_RECORD_XML_FILE "Schedule/ScheduleRecord.xml"
std::map<uint16_t, SchedulePtrBuilder> ScheduledHelper::m_builder =
{
	{(uint16_t)ESTT_SPECIFIED,	[](uint32_t id, const std::string& name, SCHEDULED_CALLBACK callback) {return std::make_shared<SpecifiedScheduled>(id,name,callback); }},
	{(uint16_t)ESTT_YEAR,		[](uint32_t id, const std::string& name, SCHEDULED_CALLBACK callback) {return std::make_shared<YearScheduled>(id,name,callback); }},
	{(uint16_t)ESTT_MONTH,		[](uint32_t id, const std::string& name, SCHEDULED_CALLBACK callback) {return std::make_shared<MonthScheduled>(id,name,callback); }},
	{(uint16_t)ESTT_WEEK,		[](uint32_t id, const std::string& name, SCHEDULED_CALLBACK callback) {return std::make_shared<WeekScheduled>(id,name,callback); }},
	{(uint16_t)ESTT_DAY,		[](uint32_t id, const std::string& name, SCHEDULED_CALLBACK callback) {return std::make_shared<DayScheduled>(id,name,callback); }}
};
ScheduledHelper::ScheduledHelper() : m_sheduledId(0), m_run(true)
{
	m_scheduledPtrMap.clear();
	m_tmpScheduledPtrMap.clear();
	m_taskDeq.clear();
	/*
	InitXMLDocument();
	InitThread();
	RestoreScheduledData();
	*/
}

ScheduledHelper::~ScheduledHelper()
{
	/*
	MergeScheduled();
	ShutDownThread();
	*/
	m_scheduledPtrMap.clear();
	m_tmpScheduledPtrMap.clear();
	m_taskDeq.clear();
}

void ScheduledHelper::InitThread()
{
	m_thread = std::move(std::thread([&]()
	{
		UpdateXMLNodeInfo updateInfo;
		while (m_run)
		{
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				m_cv.wait(lock, [&]() {return !m_taskDeq.empty() || !m_run; });

				if (m_taskDeq.empty() && !m_run) break;

				updateInfo = m_taskDeq.front();
				m_taskDeq.pop_front();
			}
			UpdateXmlDocument(updateInfo);
		}
	}));
}

void ScheduledHelper::ShutDownThread()
{
	m_run = false;
	m_cv.notify_one();
	m_thread.join();
}

ScheduledPtr ScheduledHelper::AddScheduled(uint16_t type, const std::string& name, const std::vector<std::string>& scheduled, const std::string& params, const std::string& callBackFunc)
{
	return CreateScheduled(type, name, scheduled, params, CallBackFunc, callBackFunc);
}

ScheduledPtr ScheduledHelper::AddScheduled(uint16_t type, const std::string& name, const std::vector<std::string>& scheduled, const std::string& params, SCHEDULED_CALLBACK callBackFunc)
{
	return CreateScheduled(type, name, scheduled, params, callBackFunc);
}

void ScheduledHelper::Update(uint32_t delta)
{
	MergeScheduled();

	for (auto iter = m_scheduledPtrMap.begin(); iter != m_scheduledPtrMap.end(); ) 
	{
		iter->second->Update(delta);
		if (iter->second->GetIsInvalid())
		{
			//Enqueue(iter->second->GenerateXMLNode(EUNT_DELETE));
			iter = m_scheduledPtrMap.erase(iter);
		}
		else
			++iter;
	}
}

ScheduledPtr ScheduledHelper::CreateScheduled(uint16_t type, const std::string& name, const std::vector<std::string>& scheduled,
	const std::string& params, SCHEDULED_CALLBACK MyCallBackFunc, const std::string& MyCallBackFuncName)
{
	auto iter = m_builder.find(type);
	if (iter == m_builder.end()) return ScheduledPtr();

	uint32_t tryeMaxCnt = (uint32_t)m_scheduledPtrMap.size() + (uint32_t)m_tmpScheduledPtrMap.size() + 1;
	while (tryeMaxCnt--)
	{
		uint32_t id = GenerateScheduledId();
		if (m_scheduledPtrMap.find(id) == m_scheduledPtrMap.end() 
			&& m_tmpScheduledPtrMap.find(id) == m_tmpScheduledPtrMap.end())
		{
			ScheduledPtr ptr = iter->second(id, name, MyCallBackFunc);
			if (!ptr->ParseScheduled(scheduled)) return ScheduledPtr();

			ptr->AddParam(CallBackParamKey, params);
			ptr->AddParam(CallBackFuncNameKey, MyCallBackFuncName);
			m_tmpScheduledPtrMap.insert(std::make_pair(id, ptr));
			return ptr;
		}
	}

	return ScheduledPtr();
}

uint32_t ScheduledHelper::GenerateScheduledId()
{
	m_sheduledId++;
	if (m_sheduledId == 1000000000) m_sheduledId = 1;

	return m_sheduledId;
}

void ScheduledHelper::UpdateXmlDocument(UpdateXMLNodeInfo& updateInfo)
{
	switch (updateInfo.type)
	{
		case EUNT_INSRTY:
			m_rootNode->LinkEndChild(updateInfo.node);
			break;
		case EUNT_UPDATE:
		{
			auto node = m_rootNode->FirstChild(updateInfo.id.c_str());
			if (node)
			{
				m_rootNode->RemoveChild(node);
			}
			m_rootNode->LinkEndChild(updateInfo.node);
		}
		break;
		case EUNT_DELETE:
		{
			auto node = m_rootNode->FirstChild(updateInfo.id.c_str());
			if (node)
			{
				m_rootNode->RemoveChild(node);
			}
		}
		break;
	}
	m_doc.SaveFile(SCHEDULED_RECORD_XML_FILE);
}

void ScheduledHelper::Enqueue(const UpdateXMLNodeInfo& updateInfo)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_taskDeq.push_back(updateInfo);
	m_cv.notify_one();
}

void ScheduledHelper::InitXMLDocument()
{
	if (!m_doc.LoadFile(SCHEDULED_RECORD_XML_FILE))
	{
		TiXmlDocument doc;
		TiXmlDeclaration declaration = TiXmlDeclaration("1.0", "UTF-8", "");
		TiXmlElement rootNode = TiXmlElement("Records");
		doc.InsertEndChild(declaration);
		doc.InsertEndChild(rootNode);
		m_doc = doc;
		m_doc.SaveFile(SCHEDULED_RECORD_XML_FILE);
	}
	m_rootNode = m_doc.FirstChild("Records");
	assert(m_rootNode != nullptr);
}

void ScheduledHelper::RestoreScheduledData()
{
	TiXmlElement* idNode = m_rootNode->FirstChildElement();
	while (idNode)
	{
		int32_t type = 0;
		std::string name = "";
		std::vector<std::string> scheduledVec;
		std::map<std::string,std::string> paramsMap;

		idNode->QueryIntAttribute("Type", &type);
		name = utf8_to_gbk(idNode->Attribute("Name"));

		TiXmlElement* scheduledsNode = idNode->FirstChildElement("Scheduleds");
		if (scheduledsNode)
		{
			TiXmlElement* scheduledNode = scheduledsNode->FirstChildElement();
			while (scheduledNode)
			{
				scheduledVec.emplace_back(utf8_to_gbk(scheduledNode->Attribute("Value")));
				scheduledNode = scheduledNode->NextSiblingElement();
			}
		}
		TiXmlElement* paramsNode = idNode->FirstChildElement("Params");
		if (paramsNode)
		{
			TiXmlElement* paramNode = paramsNode->FirstChildElement();
			while (paramNode)
			{
				paramsMap.emplace(utf8_to_gbk(paramNode->Attribute("Key")), utf8_to_gbk(paramNode->Attribute("Value")));
				paramNode = paramNode->NextSiblingElement();
			}
		}
		AddScheduled(type, name, scheduledVec, paramsMap[CallBackParamKey], paramsMap[CallBackFuncNameKey]);
		idNode = idNode->NextSiblingElement();
	}
	// scheduled重新生成id,所以这里重新清理了,如果要求效率高点可以,重新解析id,不抛送任务
	m_rootNode->Clear();
	m_doc.SaveFile(SCHEDULED_RECORD_XML_FILE);
}

void ScheduledHelper::MergeScheduled()
{
	for (auto iter = m_tmpScheduledPtrMap.begin(); iter != m_tmpScheduledPtrMap.end(); ++iter)
	{
		//Enqueue(iter->second->GenerateXMLNode(EUNT_INSRTY));
		m_scheduledPtrMap.emplace(*iter);
	}
	m_tmpScheduledPtrMap.clear();
}