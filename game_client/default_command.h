#ifndef DEFAULT_COMMAND_H
#define DEFAULT_COMMAND_H

#pragma once
#include "command.h"

class DefaultCommand : public Command
{
public:

	DefaultCommand(chat_message);

	~DefaultCommand();

	chat_message getCommand();

};


#endif // !DEFAULT_COMMAND_H