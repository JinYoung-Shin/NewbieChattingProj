#include "CSheader.h"
#include "message.h"

class messageHandler 
{
	public:
		int m_length;
		int b_length;
		int file;
		bool header;
		std::string exbuffer;
		std::string buffer;
	
		void push(std::string Buffer, int file, int ilen);
	
		messageHandler () {
			exbuffer = "\0";
			buffer  = "\0";
			m_length = 0;
			b_length = 0;
			file = 0;
			header = 0;
		}
};

void messageHandler::push(std::string Buffer, int file, int ilen) {
	if(m_length <= b_length+ilen)
	{
		Message temp; 
		temp.length = m_length;
		
		// temp 메시지 클래스 생성
		
		/*
		temp.pop();
		*/
	}
}