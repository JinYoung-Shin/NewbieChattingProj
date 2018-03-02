#include "messenger.h"
#include "../Common/message.h"

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
}

void Messenger::sock_nblock() 
{
	// Non-Blocking R/W Socket
	this->flag = fcntl(this->cli_ssock, F_GETFL, 0);
	if(fcntl(this->cli_ssock, F_SETFL, this->flag | O_NONBLOCK) < 0)
	{
		std::cout << strerror(errno) << std::endl;
	}
}

void Messenger::send_msg() 
{
	while(true)
	{
		char get_buffer[256];
		char send_msg[256];
		memset(send_msg, 0, 256);
	
		fgets(send_msg, 256, stdin);
		
		Message temp;
				
		strcpy(temp.plain , send_msg);
		temp.encode();
		
		if(send(this->cli_ssock, temp.packet, 256, 0) < 0)
		{
			std::cout << strerror(errno) << std::endl;
		}
	}	
}

void Messenger::recv_msg() 
{
	while(true)
	{
		char recv_msg[256];
		int ret;
		
		ret = recv(this->cli_ssock, recv_msg, 256, 0);
				
		if(ret != -1)
		{
			usleep(300000);
			
			Message temp;
			strcpy(temp.packet, recv_msg);
			temp.decode();
			
			std::cout << "Messeage from " << (int)temp.source << " : " ;
			
			for(int i=0; i< temp.length-4 ; i++)
			{
				cout << temp.plain[i];
			}
			cout << endl;
		}
		else
		{
			continue;
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