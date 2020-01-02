#ifndef CLIENT_COMMAND_H
#define CLIENT_COMMAND_H

#pragma once
#include "command.h"

class ClientCommand : public Command
{
public:

	ClientCommand(chat_message);

	~ClientCommand();

	chat_message getCommand();

};


#endif // !CLIENT_COMMAND_H