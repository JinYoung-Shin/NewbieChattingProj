#ifndef MESSAGE_H
#define MESSAGE_H
#include "CSheader.h"
#define MAX_CLIENT_FD 10

using namespace std;

class Message 
{
	public:
		char plain[252];
		char packet[256];
		char buffer[1024];
		bool full;
		char type;
		char dest;
		char source;
		unsigned int length;
		unsigned int b_length;
		
		void encode();   //length, type, dest, source, plaintext -> packet;
		void decode();   //packet -> length, type, dest, source, plaintest 
		
		void encrypt(int key);
		void decrypt(int key);
	
		void push( char * data); // push buffer
		void pop(int *socket_id, int s); // extract and pop the message
	
		Message() {
			
			plain[0] = 0;
			packet[0] = 0;
			buffer[0] = 0;

			type = 'a';
			
			dest = 4;
			source = 4;
			length = 0;
			b_length = 0;
			
		}
};

#endif