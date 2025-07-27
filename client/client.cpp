#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>

#include "client.hpp"

void start_client(const char* server_ip, int port) {
	// create TCP socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	
	// check for failure during socket creation
	if (sock < 0) {
		perror("socket");
		return; 
	}
	
	/*
	define server address struct (IPv4). Convert port 8000 from host byte order
	to network byte order using htons().
	*/
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8000);

	// Convert IPv4 address from text -> binary
	// 127.0.0.1 is the loopback address "this machine", connect server
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		std::cerr << "Invalid address or not supported.\n";
		return;
	}
	
	// connect to server via TCP handshake
	if (connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("connect");
		return;
	}

	std::cout << "Connected to the server!\n";

	while (true) {
		std::string user_input;
		std::getline(std::cin, user_input);
		if (user_input == "exit") break;

		send(sock, user_input.c_str(), user_input.size(), 0);

		char buffer[1024] = {0};
		int valread = recv(sock, buffer, sizeof(buffer) - 1, 0);
		if (valread <= 0) {
		    std::cout << "Disconnected." << std::endl;
		    break;
		}

		buffer[valread] = '\0';
		std::cout << "Server: " << buffer << std::endl;
	}

	close(sock);
}
