#include "default_command.h"

DefaultCommand::DefaultCommand(chat_message cm)
{
	std::cout << "named \"DefaultCommand\" was created by chat_message.\n";
	this->cmd = cm;
}

DefaultCommand::~DefaultCommand()
{
	std::cout << "Command named \"DefaultCommand\" was ";
}

chat_message DefaultCommand::getCommand()
{
	return this->cmd;
}