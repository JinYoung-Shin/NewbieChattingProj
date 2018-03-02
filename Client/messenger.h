#ifndef MESSENGER_H
#define MESSENGER_H
#include "../Common/CSheader.h"

class Messenger 
{
	public:
		int cli_ssock; // send_socket, recv_socket...
		int flag ; // To change socket attribute(Nonblock)...
		int portNo;
		char smsg[256];
		std::string serverIp;
		
		std::thread recv_thread();
	
		void sock_connect(); // socket connect
		void sock_nblock(); // socket non-block;
		void send_msg();
		void recv_msg();
		void send_recv_msg();
		void sock_close();
	
		Messenger() {
			cli_ssock = -1;
			flag = 0;
			portNo = 0;
		}
};

#endif