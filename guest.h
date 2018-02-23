#include "CSheader.h"

class Guest 
{
	public:
		std::string id;
		std::string ipAddress;
		std::string sendMsg; // To be Echoed
		std::string rcvMsg;
		int pKey;
		int portNum;
	
		void set_info(std::string _ip, int _port);
		void set_uid(std::string _uid);
	
		Guest() {
			id = "\0";
			ipAddress = "\0";
			portNum = 0;
			sendMsg = "\0";
			rcvMsg = "\0";
			pKey = 0;
		}
	
		// 전송용/수신용 메세지 == 패킷 (포맷?) 
		// 개인 키 ???
	
	// function 암, 복호화
	
};