cmake_minimum_required(VERSION 3.10)
project(chat_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED_ON)

add_executable(chat_server
	main.cpp
	server/server.cpp
	client/client.cpp
)
