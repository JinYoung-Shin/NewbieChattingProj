#include "CSheader.h"

using namespace std;

class Message 
{
	public:
		string plain;
		string packet;
		char type;
		char dest;
		char source;
		unsigned int length;
		
	
		void encode();   //type, dest, source, length -> encode;f
		void decode();
		
		void encrypt(int key);
		void decrypt(int key);
		void pop();
	
		Message() {
			
			plain = "\0";
			packet = "\0";

			type = 'a';
			
			dest=0;
			source = 0;
			length = 0;

		}

	
};
