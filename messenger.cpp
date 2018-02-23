#include "messenger.h"
#include <thread>

void Messenger::sock_connect() 
{
	struct sockaddr_in server_addr;
	
	std::cout << "Please, enter the Server IP address : ";
	std::getline(std::cin, this->serverIp);
	std::cout << "Please, enter the Port number : ";
	std::cin >> this->portNo;
	
	//Create remote (server) socket address
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr((this->serverIp).c_str()); // 채팅방 서버의 주소 !
	server_addr.sin_port = htons(this->portNo); // 포트번호, 방식 고민 / 랜덤 제너레이팅 방식 ?
	
	//Create Socket
	if(this->cli_ssock = socket(PF_INET, SOCK_STREAM, 0)) // socket(int domain, int type, int protocol)
	{
		std::cout << "Failed to create socket." << std::endl;
	}
	
	if(connect(this->cli_ssock, (struct sockaddr*)&server_addr, sizeof(server_addr))) 
	{
		std::cout << "Failed to connect." << std::endl;
	}
	
	// std::cout << "You are connected to Server. Before you start chatting, please input your ID :";
	// std::getline(std::cin, uid);
	// Set guest info 한큐에 다해라...
	// guest.set_info(serverIp, portNo);
	// guest.set_uid(uid);
}

void Messenger::sock_nblock() 
{
	// Non-Blocking R/W Socket
	this->flag = fcntl(this->cli_ssock, F_GETFL, 0);
	if(fcntl(this->cli_ssock, F_SETFL, this->flag | O_NONBLOCK) < 0)
	{
		std::cout << errno << std::endl; // non-block failure
	}
}

void Messenger::send_msg() 
{
	while(true)
	{
		char send_msg[256];
		std::cin >> send_msg;
		if(send(this->cli_ssock, send_msg, 256, 0) < 0)
		{
			// perror("This kind of error");
			std::cout << errno << std::endl;
		}
		// send_msg handling
	}	
}

void Messenger::recv_msg() 
{
	while(true)
	{
		char recv_msg[256];
		if(recv(this->cli_ssock, recv_msg, 256, 0) < 0)
		{
			// perror("This kind of error");
			std::cout << errno << std::endl;
		}
		// recv_msg handling
		std::cout << recv_msg << std::endl;	
	}
}

std::thread Messenger::recv_thread()
{
	return std::thread([=] { this->recv_msg(); });
}

void Messenger::sock_close() 
{
	close(this->cli_ssock);
}