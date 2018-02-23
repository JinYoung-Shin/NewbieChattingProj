#include "messenger.h"

void start();

int main()
{	
	Messenger messenger;
	
	messenger.sock_connect();
	messenger.sock_nblock();
	
	// thread
	std::thread rthread = messenger.recv_thread();
	messenger.send_msg();
	rthread.join();
	// EAGAIN(버퍼가 꽉차서 전송이 불가능 할 경우에 발생하는 에러코드) 처리 !?!
		
	messenger.sock_close();
	
	return 0;
}