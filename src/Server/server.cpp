#include "CSheader.h"
#include "message.h"

#define MAX_CLIENT_FD 10
#define SERV_PORT 8888

int main(void) 
{
	int ls; // server(listening) socket
	int cs; // client socket
	int s; // socket
	int sock_opt; // variable to prevent bind (duplicatiFon) error
	int socket_cli[MAX_CLIENT_FD]; // current client
	int num_cli = 0; // current client #
	int max_cli = 0; // max client file descriptor
	int state;
	int cli_len;
	int counter;
	int ilen;
	char buffer[256]; // msg buffer
	
	Message cli_m;
	
	fd_set fsStatus, allStatus;

	struct timeval timeout;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	
	// Create socket(with IPv4 + TCP Protocol)
	if((ls = socket(PF_INET, SOCK_STREAM, 0)) < 0)
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
	serverAddr.sin_port = htons(SERV_PORT); // Default Port
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
	
	std::cout << "Server is Running" << std::endl;
	
	FD_ZERO(&fsStatus);
	FD_SET(ls, &fsStatus);
	
	// Server Runs
	while(true)
	{
		allStatus = fsStatus;
		
		state = select(max_cli + 1, &allStatus, NULL, NULL, 0);
		
		if(FD_ISSET(ls, &allStatus)) 
		{
			cli_len = sizeof(clientAddr);
			
			cs = accept(ls, (struct sockaddr*)&clientAddr, (socklen_t*)&cli_len);
			
			std::cout << "IP : " << inet_ntoa(clientAddr.sin_addr) << " Port : " << ntohs(clientAddr.sin_port) << " client socket : " << cs << std::endl;
			
			for(counter = 0; counter < MAX_CLIENT_FD; counter++) 
			{
				if(socket_cli[counter] < 0)
				{
					socket_cli[counter] = cs;
					break;
				}
			}
			
			// Max client check
			
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
			cout << endl << "conneted client num : " << num_cli+1 << endl;
		}
		
		for(int i = 0; i <= num_cli; i++)
		{
			if((s = socket_cli[i]) < 0)
			{
				continue;
			}
			
			if(FD_ISSET(s, &allStatus))
			{
				memset(buffer, 0, 256);
				
				ilen = read(s, buffer, 256);
				if(ilen < 0)
				{
					if(errno == EAGAIN) 
					{
						continue;
					}
					else
					{
						std::cout << "read failed" << std::endl;
						exit(1);
					}
				}
				else if(ilen == 0)
				{
					
				}
				else
				{
					buffer[ilen] = '\0';

					cout << endl;
				
					std::cout << "Message from client socket " << s << " : " ;
					
					cli_m.push(buffer); //push the buffer
					cli_m.encode();	    //extract header from buffer
					cli_m.source = s;
					cli_m.pop(socket_cli, s);
					
					for(int i=0; i< cli_m.length-4 ; i++)
					{
						cout << cli_m.plain[i];
					}
					cout << endl;
					
					for(int i = 0; i < num_cli; i++)
					{
						if(i == s) 
						{
							continue;
						}
						
					}
					
					if(--state <= 0)
					{
						break;
					}
				}
			}
		}
	}
	//FD_CLEAR
	
	close(ls);
	
	return 0;
}