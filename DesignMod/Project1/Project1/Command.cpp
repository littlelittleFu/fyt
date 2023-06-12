#include "Command.h"

void ConcreteCommand::Execute()
{
	receiver->Action();
}