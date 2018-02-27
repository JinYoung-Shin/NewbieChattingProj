#include "CSheader.h"
#include "messageHandler.h"

#define MAX_CLIENT_FD 10

int main(void) 
{
	int ls; // server(listening) socket
	int cs; // client socket
	int s; // socket
	
	int num_cli = 0; // current client #
	int max_cli = 0; // max client file descriptor
	int socket_cli[MAX_CLIENT_FD];
	int state;
	int cli_len;
	int counter;
	int sock_opt; // variable to prevent bind error
	char buffer[1024]; // msg buffer
	int ilen;
	
	fd_set fsStatus, allStatus;
	struct timeval timeout;
	
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	
	// Create socket
	if((ls = socket(PF_INET, SOCK_STREAM, 0)) < 0) // Open Socket with IPv4 + TCP Protocol
	{
		std::cout << "socket error" << std::endl;
		exit(1);
	}
	
	// Prevent Bind Error
	sock_opt = 1;
	if (setsockopt(ls, SOL_SOCKET, SO_REUSEADDR, &sock_opt , sizeof(sock_opt)) == -1) {
		std::cout << "setting sock option" << std::endl;
	}
	
	// Bind Socket
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888); // Default Port
	serverAddr.sin_addr.s_addr = htons(INADDR_ANY); // Default IP address
	
	if((bind(ls, (const struct sockaddr*)&serverAddr, sizeof(serverAddr))) < 0 )
	{
		std::cout << "bind 에러 " << errno << std::endl;
		exit(1);
	}
	
	if(listen(ls, MAX_CLIENT_FD) < 0)
	{
		std::cout << "listen 에러" << std::endl;
		exit(1);
	}
	
	max_cli = ls;
	num_cli = -1;
	
	for(int i = 0; i < MAX_CLIENT_FD; i++) 
	{
		socket_cli[i] = -1;
	}
	
	FD_ZERO(&fsStatus);
	FD_SET(ls, &fsStatus);
	
	std::cout << "Server is Running" << std::endl;
	
	// Server Runs(Forever)
	while(true)
	{
		allStatus = fsStatus;
		state = select(max_cli + 1, &allStatus, NULL, NULL, 0);
		
		if(FD_ISSET(ls, &allStatus)) {
			cli_len = sizeof(clientAddr);
			
			cs = accept(ls, (struct sockaddr*)&clientAddr, (socklen_t*)&cli_len);
			
			std::cout << "IP : " << inet_ntoa(clientAddr.sin_addr) << " Port : " << ntohs(clientAddr.sin_port) << " client socket : " << cs << std::endl;
			
			for(counter = 0; counter < MAX_CLIENT_FD; counter++) {
				if(socket_cli[counter] < 0)
				{
					socket_cli[counter] = cs;
					break;
				}
			}
			
			FD_SET(cs, &fsStatus);

			if(cs > max_cli)
			{
				max_cli = cs;
			}

			if(counter > num_cli)
			{
				num_cli = counter;
			}

			if(--state <= 0)
			{
				continue;
			}
		}
		
		for(int i = 0; i <= num_cli; i++)
		{
			if(( s = socket_cli[i]) < 0)
			{
				continue;
			}
			
			if(FD_ISSET(s, &fsStatus))
			{
				memset(buffer, 0, 1024);
								
				ilen = read(s, buffer, 1024);
				
				if ( ilen == -1)
				{
					std::cout << "read failed" << std::endl;
				}
				
				buffer[ilen] = '\0';
				
				std::cout << "Message from client socket " << s << " : " << buffer << std::endl;
				// messageHandler aaa;
				// aaa.messageHandler(buffer, s, ilen);  // 온전한 메시지인지 확인
						
				//끊긴 경우
				
				write(s, buffer, 1024);
				
				if(--state <= 0)
				{
					break;
				}
			}
		}
		
	}
	//close
	return 0;
}