#include "CSheader.h"

class Messenger 
{
	public:
		int cli_ssock; // send_socket, recv_socket...
		int flag ; // To change socket attribute(Nonblock)...
		char smsg[100];
		std::string serverIp;
		int portNo;
	
		void sock_connect(); // socket connect
		void sock_nblock(); // socket non-block;
		void send_msg();
		void recv_msg();
		void send_recv_msg();
		void sock_close();

		std::thread recv_thread();
	
		Messenger() {
			
			
		}
};
