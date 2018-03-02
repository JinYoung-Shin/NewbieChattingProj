#include "messenger.h"

int main()
{	
	Messenger messenger;
	
	messenger.sock_connect();
	messenger.sock_nblock();
	
	// Thread
	std::thread rthread = messenger.recv_thread();
	messenger.send_msg();
	rthread.join();

	messenger.sock_close();
	
	return 0;
}