#include "message.h"



void Message::encode() {
	
	this->length = strlen(this->plain)+4;

	this->packet[0] = this->length & 0xFF ;
	this->packet[1] = this->type;
	this->packet[2] = this->dest; 
	this->packet[3] = this->source;

	for(int i = 0; i < strlen(this->plain); i++)
	{
		this->packet[i + 4] = this->plain[i];
	}
	this->packet[this->length] = '\0';


}

void Message::decode() 
{ 
	
	this->length = this->packet[0] ;
	this->type = this->packet[1];
	this->dest = this->packet[2];
	this->source = this->packet[3];
	
	for(int i = 0; i < this->length-4; i++)
	{
		this->plain[i] = this->packet[i+4];
	}
	
	this->plain[length] = '\0';
}

void Message::encrypt(int key)
{
	
}

void Message::decrypt(int key) 
{
	
}

void Message::push(char* data) 
{
	strcat(buffer, data);
	b_length += strlen(data);
}
	

void Message::pop(int *socket_id, int s) {

	if(this->b_length<=4)  //  less than header length
	{
		return;
	}
	
	this->length = this->buffer[0];
	
	
	if (this->length <= this->b_length) //more than 1 message
	{
		for ( int i=0; i < this->length ; i++)
		{
			this->packet[i] = this->buffer[i];
		}
		
		this->packet[this->length] = 0;
		
		for ( int i=0; i < b_length - this->length+1 ; i++)
		{
			this->buffer[i] = this->buffer[i+this->length];
		}
		
		this->b_length = this->b_length - this->length;
		this->buffer[b_length]='\0';
		
		this->decode();
		
		this->packet[3] = s;
		
		for(int i = 0; i < MAX_CLIENT_FD; i++)// 전체 접속 인원 검색
		{
			
			if(socket_id[i] != s)  //broadcasting except the sender client
			{
					send(socket_id[i], this->packet, 256, 0);  
			}
		}
		
	}
	
}

