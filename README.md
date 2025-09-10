# Terminal-Based TCP Chat Server and Client 

This is a TCP/IP based project, written in C++. Multiple clients can connect and exchange messages over the network using TCP sockets and the C POSIX API, using socket programming and multithreading.
The server is written in modern C++, and handles multiple clients using std::thread. 
Supports basic send/receiving of text messages.

Requirements: 
- C++17
- g++ or clang++ for compilation
- POSIX compatible system (Linux, MacOS, WSL, etc.)


Instructions:
## Build server
`g++ -std=c++17 server/server.cpp main.cpp -o chat_server -pthread`

## Build client
`g++ -std=c++17 client/client.cpp main_client.cpp -o chat_client -pthread`

## Run the server and client
`./chat_server ./chat_client`
