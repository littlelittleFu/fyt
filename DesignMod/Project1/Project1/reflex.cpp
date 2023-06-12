#include"reflex.h"

Factory* Factory::instance = nullptr;
Factory* Factory::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Factory();
	}

	return instance;
}

//std::map<std::string, PTRCreateObj> Factory::m_classMap;
void* Factory::GetClassByName(std::string className)
{
	auto iter = m_classMap.find(className);
	if (iter != m_classMap.end())
	{
		return iter->second();
	}
	return nullptr;
}

void Factory::RegisterClass(std::string className, PTRCreateObj method)
{
	//if (m_classMap[className] == nullptr)
	//{
	//	m_classMap[className] = method;
	//}
	m_classMap.insert(std::make_pair(className, method));
}