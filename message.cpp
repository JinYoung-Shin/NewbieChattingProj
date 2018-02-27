#include "message.h"

//#define MAX_CLIENT_FD 10

void Message::encode() {
	
	this->length = this->plain.size();
	char ba[4];
	ba[0]= (( this->length >> 24 ) & 0xFF); 
	ba[1]= (( this->length >> 16 ) & 0xFF); 
	ba[2]= (( this->length >> 8 ) & 0xFF); 
	ba[3]= ( this->length & 0xFF );

	cout <<"i"<< +ba[0] << endl;
	cout <<"i"<< +ba[1] << endl;
	cout <<"i"<< +ba[2] << endl;
	cout <<"i"<< +ba[3] << endl;
	
	this->packet += ba[0];
	this->packet += ba[1];
	this->packet += ba[2];
	this->packet += ba[3];
	this->packet += this->type;
//	this->packet.append(this->dest);
//	this->packet.append(this->source);
	this->packet.append(this->plain);

}

void Message::decode() {
	
	this->length = (this->packet[0] << 24) | (this->packet[1] << 16 )|( this->packet[2] << 8 )| this->packet[3];
	this->type = this->packet[4];
	this->plain = (this->packet).substr(5,this->length);
	
}

void Message::encrypt(int key) {
}

void Message::decrypt(int key) {
}

void Message::pop() {

	// this.decode();
	
	
	/*
	for(int i = 0; i < MAX_CLIENT_FD; i++)// 전체 접속 인원 검색
	{
          write(socket_id[i], this->plain, this->length);
	}
	*/
	
}

