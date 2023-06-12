#include "Builder.h"

void ThinPerson::BuildHead()
{

}

void ThinPerson::BuildBody()
{

}

void ThinPerson::BuildArmL()
{

}

void ThinPerson::BuildArmR()
{

}

void ThinPerson::BuildLegL()
{

}

void ThinPerson::BuildLegR()
{

}

PersonBuilder* PerDirector::CreatePerson()
{
	m_pb->BuildHead();
	m_pb->BuildBody();
	m_pb->BuildArmL();
	m_pb->BuildArmR();
	m_pb->BuildLegL();
	m_pb->BuildLegR();

	return m_pb;
}