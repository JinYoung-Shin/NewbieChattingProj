#ifndef GUEST_H
#define GUEST_H
#include "../Common/CSheader.h"

class Guest 
{
	public:
		std::string id;
		std::string ipAddress;
		std::string sendMsg; // To be Echoed
		std::string rcvMsg;
		int pKey;
		int portNum;
	
		void set_info(std::string _ip, int _port, std::string _uid) 
		{
			this->ipAddress = _ip;
			this->portNum = _port;
			this->id = _uid;
	
		}
	
		Guest() {
			id = "\0";
			ipAddress = "\0";
			portNum = 0;
			sendMsg = "\0";
			rcvMsg = "\0";
			pKey = 0;
		}
};
#endif