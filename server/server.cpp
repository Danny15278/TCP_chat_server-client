#include "server.hpp"

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

void start_server(int port) {
	int server_fd = socket(AF_INET, SOCK_STREAM, 0); // IPv4 and TCP chosen, reliable, ordered

	if (server_fd == -1) { 
		perror("socket");
		return;
	} 

	// configuration of socket address
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	
	// bind socket to IP address and port number to listen for connections
	if (bind(server_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
		perror("bind failed");
		return;
	}
	
	// listen for incoming TCP connections (up to 5 in backlog)
	if (listen(server_fd, 5) < 0) {
		perror("listen");
		return;
	}
	
	/* 
	if connection found, new socket talks to that specific client, server_fd still listening for more clients 
	while new_socket is used for communication 
	*/
	int addrlen = sizeof(address);
	int new_socket = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen);
	
	if (new_socket < 0) {
		perror("accept");
		return;
	}
	
	// persistent chat
	while (true) {
		/*
		read data from client, allocate 1KB memory buffer for storage.
		blocking call, reads up to 1024 bytes, returns no. bytes read. 
		Waits until data is available to read.
		*/
		char buffer[1024] = {0};
		int valread = read(new_socket, buffer, 1024);
		if (valread < 0) {
			perror("read");
		}
		
		// Respond to client via socket
		std::cout << "Client: " << buffer << std::endl;
		const char* reply = "Hello from the server!";
		send(new_socket, reply, strlen(reply), 0);
		std::cout << "Server: " << reply << std::endl;
	}
	close(new_socket);
	close(server_fd);
}
