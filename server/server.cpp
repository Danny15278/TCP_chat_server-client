#include "server.hpp"

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

void start_server(int port) {
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (server_fd == -1) {
		perror("socket");
		return;
	}

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(server_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
		perror("bind failed");
		return;
	}

	if (listen(server_fd, 5) < 0) {
		perror("listen");
		return;
	}

	int addrlen = sizeof(address);
	int new_socket = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen);
	
	if (new_socket < 0) {
		perror("accept");
		return;
	}
}
