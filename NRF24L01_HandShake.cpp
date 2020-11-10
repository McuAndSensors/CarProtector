/*
 * NRF24L01__HandShake.cpp
 *
 * Created: 22/02/2018 18:31:01
 *  Author: Adiel
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include "NRF24L01_Basic.h"
#include "NRF24L01_HandShake.h"

void Nrf24l01_HandShake::setToggleOption()
{
	//Enable the Toggle in FEATURE register by setting the second bit High
	unsigned char Value_of_command[2]= {0x02};
	Write_Data_To_nRF(FEATURE,Value_of_command,1);
}
void Nrf24l01_HandShake::readAckPayload()
{
	//now we get CSN to low so the nRF can listen
	Send_Signal = 0<<CSN;
	
	//now the SPI will send command of reading, and the name of the register we will like to read to.
	SPI_Byte_TX_OR_RX(READ_RX_PAYLOAD);
	_delay_us(10);
	
	for(int i = 0; i < Payload_Size; i++)
	{
		//Here we send dummy byte just to get it to work.
		_ackPacketValue[i] = SPI_Byte_TX_OR_RX(NOP);
		_delay_us(10);
	}
	
	//now we get CSN to High again and we stop the nRF communication
	Send_Signal = 1<<CSN;
	_delay_us(10);
}
bool Nrf24l01_HandShake::checkifAckPacketIsDummy()
{
	char ackCounter = 0;
	for(int i = 0; i < Payload_Size; i++)
	{
		if (_ackPacketValue[0] == _ackPacketValue[i])
		{
			ackCounter++;
		}
	}
	
	if(ackCounter <= (Payload_Size-1))
	{
		return true;
	}
	else
	{
		for(int i = 0; i < Payload_Size; i++)
		{
			_ackPacketValue[i] = 0;
		}
		return false;
	}
}
void Nrf24l01_HandShake::setAck(unsigned char *arr_of_data, unsigned char arr_Size = Payload_Size)
{
	// turn off interrupts
	cli();
	
	unsigned char i;
	// Make sure we don't write after a command that was less then the minimum time
	_delay_us(10);
	
	//now we get CSN to low so the nRF can listen
	Send_Signal = 0<<CSN;
	
	//now the SPI will send command of writing the data to the TX FIFO.
	SPI_Byte_TX_OR_RX(W_ACK_PAYLOAD);
	_delay_us(10);
	
	//now we sending the packet one by one till it reach the "arr_Size" value
	//and of course we take 10uS delay between each byte that we send.
	for(i = 0; i < arr_Size; i++)
	{
		SPI_Byte_TX_OR_RX(arr_of_data[i]);
	}
	
	//now we get CSN to High again and we stop the nRF communication
	Send_Signal = 1<<CSN;
	_delay_us(10);
	
	// turn on interrupts
	sei();
}
Nrf24l01_HandShake::Nrf24l01_HandShake()
{
	setToggleOption();
	count2 = 0;
	count1 = 0;
}
bool Nrf24l01_HandShake::Transmite_Payload(unsigned char *Data_Transmission)
{
	if (Nrf24l01::Transmite_Payload(Data_Transmission,true))
	{
		readAckPayload();
		checkifAckPacketIsDummy();
		return true;
	}
	return false;
}
unsigned char *Nrf24l01_HandShake::Receive_Payload(unsigned char *dataToBeSendFromRX)
{
	setAck(dataToBeSendFromRX);
	Nrf24l01::Receive_Payload(_Packet);
	return _Packet;
}
unsigned char *Nrf24l01_HandShake::getRXpacket()
{
	return _ackPacketValue;
}