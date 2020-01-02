#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

#pragma once
#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <memory>
#include <boost/asio.hpp>
#include "chat_message.h"
#include "command.h"

using boost::asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;

class chat_client
{
public:

	chat_client(boost::asio::io_context&, const tcp::resolver::results_type&, char*);

	void write(std::unique_ptr<Command>&);

	void close();

private:

	void do_connect(const tcp::resolver::results_type&);

	void do_read_header();

	void do_read_body();

	void do_write();

private:
	std::string name_;
	boost::asio::io_context& io_context_;
	tcp::socket socket_;
	chat_message read_msg_;
	chat_message_queue write_msgs_;
};

#endif