#pragma once
#include "chat_client.h"
#include <memory>
#include <iostream>
#include <cstring>
#include <malloc.h>
#include "command.h"
#include "client_command.h"
#include "default_command.h"

using std::unique_ptr;

void deleteSpaces(std::string& str)
{
	size_t begin = str.find_first_not_of(' ');
	size_t end = str.find_last_not_of(' ');
	str.erase(end + 1, str.size() - end);
	str.erase(0, begin);
}

const std::vector<std::vector<std::string>> commands = {
	{
		"ClientCommand ",
		"connected ",
		"unconnected ",
		"play ",
		"pause ",
		"registrate "
	}
};

Command* determineCommandType(char* str)
{
	chat_message msg;
	msg.body_length(strlen(str));
	std::memcpy(msg.body(), str, msg.body_length());
	msg.encode_header();

	std::string copy = str;
	deleteSpaces(copy);
	if (copy.find("> ") == 0)
	{
		for (size_t i = 0; i < commands.size(); ++i)
		{
			if (copy.find(commands[i][0]) < copy.length())
			{
				for (size_t j = 0; j < commands[i].size(); ++j)
				{
					if (copy.find(commands[i][j]) < copy.length())
					{
						switch (i)
						{
						case 0:
							return new ClientCommand(msg);
						default:
							break;
						}
					}
				}
			}
		}

		return new DefaultCommand(msg);
	}
	else return nullptr;
}

int main(int argc, char* argv[])
{
	try
	{
		argv[1] = (char*)"127.0.0.1";
		argv[2] = (char*)"4000";
		argv[3] = (char*)"Name";
		argc = 4;
		if (argc != 4)
		{
			std::cerr << "Usage: chat_client <host> <port>\n";
			return 1;
		}

		boost::asio::io_context io_context;

		tcp::resolver resolver(io_context);
		auto endpoints = resolver.resolve(argv[1], argv[2]);
		chat_client c(io_context, endpoints, argv[3]);

		std::thread t([&io_context]() { io_context.run(); });

		char line[chat_message::max_body_length + 1];

		while (std::cin.getline(line, chat_message::max_body_length + 1))
		{
			unique_ptr<Command> cmd(determineCommandType(line));
			if (cmd != nullptr) c.write(cmd);
			else continue;
		}

		c.close();
		t.join();
	}
	catch (std::exception & e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}