/*
 * NRF24L01__HandShake.h
 *
 * Created: 22/02/2018 18:31:24
 *  Author: Adiel
 */ 


#ifndef NRF24L01_HANDSHAKE_H_
#define NRF24L01_HANDSHAKE_H_

class Nrf24l01_HandShake : public Nrf24l01{
	private:
	unsigned char _ackPacketValue[Payload_Size];
	unsigned char _Packet[Payload_Size];
	void setToggleOption();
	void readAckPayload();
	void setAck(unsigned char *arr_of_data, unsigned char arr_Size);
	bool checkifAckPacketIsDummy();
	public:
	Nrf24l01_HandShake();
	bool Transmite_Payload(unsigned char *Data_Transmission);
	unsigned char *Receive_Payload(unsigned char *dataToBeSendFromRX);
	unsigned char *getRXpacket();
	
};

#endif /* NRF24L01+_HANDSHAKE_H_ */