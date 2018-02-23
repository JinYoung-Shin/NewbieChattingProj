#include "guest.h"

void Guest::set_info(std::string _ip, int _port) {
	this->ipAddress = _ip;
	this->portNum = _port;
}

void Guest::set_uid(std::string _uid) {
	this->id = _uid;
}