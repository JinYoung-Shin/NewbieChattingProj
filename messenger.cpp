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
	if((this->cli_ssock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
	{
		std::cout << "Failed to create socket." << std::endl;
		exit(1);
	}
	
	if(connect(this->cli_ssock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
	{
		std::cout << "Failed to connect." << std::endl;
		exit(1);
	}
	
	std::cout << "You are connected to Server." << std::endl;
	std::cout << "Before you start chatting, please input your ID :" << std::endl;
	
	// sender, receiver 추가해주나 ?
	// std::string uid;
	// std::getline(std::cin, uid);
	// guest.set_info(serverIp, portNo, uid);
}

void Messenger::sock_nblock() 
{
	// Non-Blocking R/W Socket
	this->flag = fcntl(this->cli_ssock, F_GETFL, 0);
	if(fcntl(this->cli_ssock, F_SETFL, this->flag | O_NONBLOCK) < 0)
	{
		std::cout << errno << std::endl;
		std::cout << strerror(errno) << std::endl;
	}
}

void Messenger::send_msg() 
{
	while(true)
	{
		char send_msg[256];
		std::cin >> send_msg;
		
		// send_msg handling
		
		
		if(send(this->cli_ssock, send_msg, 256, 0) < 0)
		{
			std::cout << errno << std::endl;
			std::cout << strerror(errno) << std::endl;
		}
	}	
}

void Messenger::recv_msg() 
{
	while(true)
	{
		char recv_msg[256];
		
		if(recv(this->cli_ssock, recv_msg, 256, 0) < 0)
		{
			// Do nothing
		}
		else
		{
			// recv_msg handling
			
			std::cout << recv_msg << std::endl;	
		}
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