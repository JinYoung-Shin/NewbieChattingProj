#ifndef MESSENGER_H
#define MESSENGER_H
#include "CSheader.h"

class Messenger 
{
	public:
		int cli_ssock; // send_socket, recv_socket...
		int flag ; // To change socket attribute(Nonblock)...
		int portNo;
		char smsg[256];
		std::string serverIp;
	
		void sock_connect(); // socket connect
		void sock_nblock(); // socket non-block;
		void send_msg();
		void recv_msg();
		void send_recv_msg();
		void sock_close();

		std::thread recv_thread();
	
		Messenger() {
			cli_ssock = -1;
			flag = 0;
			portNo = 0;
		}
};

#endif