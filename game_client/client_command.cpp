#include "client_command.h"

ClientCommand::ClientCommand(chat_message cm)
{
	std::cout << "named \"ClientCommand\" was created by chat_message.\n";
	this->cmd = cm;
}

ClientCommand::~ClientCommand()
{
	std::cout << "Command named \"ClientCommand\" was ";
}

chat_message ClientCommand::getCommand()
{
	return this->cmd;
}