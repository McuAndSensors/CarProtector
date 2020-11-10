/*
 * NRF24L01_Basic.cpp
 *
 * Created: 22/02/2018 18:30:06
 *  Author: Adiel
 */ 
#define F_CPU 16000000		//change to your clk speed

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <stdio.h>
#include "NRF24L01_Basic.h"

void Nrf24l01::SPI_SETUP (void)
{
	// turn off interrupts
	cli();
	
	// Set MOSI, SCK, CSN, CE as Output
	DDRB=(1<<SCK)|(1<<MOSI)|(1<<CSN)|(1<<CE)|(1<<2);
	
	// Enable SPI, Set as Master
	// Data speed: Fosc/16, Enable Interrupts
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
	//CSN is high, No data to be send now
	Send_Signal = (1<<CSN);
	
	//CE is LOW, now we don't sending or receiving anything
	Send_Signal = (1<<CE);
	
	// Enable Global Interrupts
	sei();
}
unsigned char Nrf24l01::SPI_Byte_TX_OR_RX (unsigned char data)
{
	// Load data into the buffer
	SPDR = data;
	
	//Wait until transmission complete
	while(!(SPSR & (1<<SPIF) ));
	
	// Return received data
	return(SPDR);
}
void Nrf24l01::Set_interrupt()
{
	DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
	// PD2 (PCINT0 pin) is now an input

	PORTD |= (1 << PORTD2);    // turn On the Pull-up
	// PD2 is now an input with pull-up enabled


	EICRA |= (1 << ISC01);    // set INT0 to trigger on falling adge
	EIMSK |= (1 << INT0);     // Turns on INT0

	sei();                    // turn on interrupts

}
void Nrf24l01::Main_setup_nRF(void)
{
	unsigned char Value_of_command[6];
	
	//Set_interrupt(); //Enable interrupt on INT0 (PORT D PIN 2)
	
	// turn off interrupts
	cli();
	
	_delay_ms(120);  //The time for the chip to power up and set all registers
	
	//EN_AA enable (Auto Ack) TX get automatic respond from receiver when a transmission is success
	//work only when the TX and the RX have the same address
	//Enable Auto Acknowledgment on Data Pipe 0  ;bit 0 = '1'
	Value_of_command[0]= 0x01;
	Write_Data_To_nRF(EN_AA,Value_of_command,1);
	
	//Chose number of Data Pipe
	//Enable one data pipe ; bit 0='1'
	Value_of_command[0]= 0x01;
	Write_Data_To_nRF(EN_RXADDR,Value_of_command,1);
	
	//Define the Size of Address (the bigger the size is, the more secure the info will be)
	//we define 5 byte address; bit 1,0 ="11"
	Value_of_command[0]= 0x03;
	Write_Data_To_nRF(SETUP_AW,Value_of_command,1);
	
	//RF channel setup, chose between 2.400GHz t0 2.526GHz
	//we will chose channel 3 2.403GHz, the same mast be on TX and RX
	//RF_CH = 0x03 that will be 0b0000 0011
	Value_of_command[0]= 0x03;
	Write_Data_To_nRF(RF_CH,Value_of_command,1);
	
	//Define the delay between packet retransmission
	//in are case we will choose 750uS just to be sure
	//we will choose also the max of retransmission to be 15
	//bit 3-0 is retransmission amount ="1111" 15 times
	//bit 7-4 is the delay between packets ="0010'  ;0b0010 1111
	Value_of_command[0]= 0x2F;
	Write_Data_To_nRF(SETUP_RETR,Value_of_command,1);
	
	//choose the power mode in dB of transmission and choose the speed of data rate
	//bit 5 and 3 define the speed both bit = '0' it will be on 1Mbps
	//bit 2 and 1 are for power mode "11"=0dB ; bit 0 = don't care
	Value_of_command[0]= 0x26;
	Write_Data_To_nRF(RF_SETUP,Value_of_command,1);
	
	//Receiver address is need to be modified, we make the size of it to 5 Bytes
	//The address will be 0x15,0x35,0x17,0xC5,0x32
	Value_of_command[0]= 0x15;
	Value_of_command[1]= 0x35;
	Value_of_command[2]= 0x17;
	Value_of_command[3]= 0xC5;
	Value_of_command[4]= 0x32;
	Write_Data_To_nRF(RX_ADDR_P0,Value_of_command,5);
	//if you want to use a multiply pipe here is the place to add them
	
	//Write_Data_To_nRF(RX_ADDR_P1,Value_of_command,5);
	
	//Here we set the Transmitter address to be the same as the receiver.
	//it is important to remember that the TX address is must be equal to the
	//receiver of pipe 0 only, and not to the others pipes (in case you use multiply data pipes).
	Write_Data_To_nRF(TX_ADDR,Value_of_command,5);
	
	//here we define how much payload we would like to send each transmit (1-32)
	//we will define to send 6 bytes on each packet on data pipe 0
	//you can change Payload_Size in the define
	//bits 0-5 will define the bit amount.
	Value_of_command[0]= Payload_Size;
	Write_Data_To_nRF(RX_PW_P0,Value_of_command,1);
	
	//Now the function of TX_Mode or Set_RX_Mode must be called in order
	//to complete the Setup process
	
	// turn on interrupts
	sei();
}
unsigned char Nrf24l01::Check_STATUS_Register()
{
	unsigned char STATUS_reg;
	
	//get STATUS register value
	STATUS_reg = SPI_Byte_TX_OR_RX(NOP);

	//Check if RX_DR is = '0' he will return RX_DR value
	//that mean the interrupt have been active
	if(!(STATUS_reg & (1<<RX_DR)))
	{
		STATUS_reg = RX_DR;
	}
	
	//Check if TX_DS is = '0' he will return TX_DS value
	//that mean the interrupt have been active
	if(!(STATUS_reg & (1<<TX_DS)))
	{
		STATUS_reg = TX_DS;
	}
	
	//Check if MAX_RT is = '0' he will return MAX_RT value
	//that mean the interrupt have been active
	if(!(STATUS_reg & (1<<MAX_RT)))
	{
		STATUS_reg = MAX_RT;
	}
	
	//if non of the MAX_RT/TX_DS/RX_DR is true, he will return the register value
	return STATUS_reg;
}
unsigned char Nrf24l01::Write_Data_To_nRF(unsigned char Reg_Name, unsigned char *arr_of_data, unsigned char arr_Size)
{
	// turn off interrupts
	cli();
	
	unsigned char i, Status_reg;
	// Make sure we don't write after a command that was less then the minimum time
	_delay_us(10);
	
	// turn off interrupts
	cli();
	
	//now we get CSN to low so the nRF can listen
	Send_Signal = 0<<CSN;
	
	//This if condition check if we want to write data into register or into the TX FIFO
	//if we put value of '0' in the name of the register that mean that we don't a register to refer to.
	//any number bigger then '0' will be considered as register name by value
	if(Reg_Name != 0x50 )
	{
		//now the SPI will send command of writing, and the name of the register we will like to write to.
		Status_reg = SPI_Byte_TX_OR_RX(WRITE_REGISTER + Reg_Name);
		_delay_us(5);
	}
	else
	{
		//now the SPI will send command of writing the data to the TX FIFO.
		Status_reg = SPI_Byte_TX_OR_RX(WRITE_TX_PAYLOAD);
		_delay_us(10);
	}
	
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
	
	//now we send back the state of the status register.
	return(Status_reg);
}
unsigned char Nrf24l01::Read_Data_From_nRF(unsigned char Reg_Name, unsigned char *arr_of_data, unsigned char arr_Size)
{
	unsigned char i, Status_reg;
	// Make sure we don't read after a command that was less then the minimum time
	_delay_us(10);
	
	// turn off interrupts
	cli();
	
	//now we get CSN to low so the nRF can listen
	Send_Signal = 0<<CSN;
	_delay_us(2);
	if(Reg_Name != 0x50)
	{
		//now the SPI will send command of reading, and the name of the register we will like to read to.
		Status_reg = SPI_Byte_TX_OR_RX(READ_REGISTER + Reg_Name);
		_delay_us(10);
	}
	else
	{
		//now the SPI will send command of reading, and the name of the register we will like to read to.
		Status_reg = SPI_Byte_TX_OR_RX(READ_RX_PAYLOAD);
		_delay_us(10);
	}
	//now we receiving the packet one by one till it reach the "arr_Size" value
	//and of course we take 10uS delay between each byte that we send.
	for(i = 0; i < arr_Size; i++)
	{
		//Here we send dummy byte just to get it to work.
		arr_of_data[i] = SPI_Byte_TX_OR_RX(NOP);
		_delay_us(10);
	}
	
	//now we get CSN to High again and we stop the nRF communication
	Send_Signal = 1<<CSN;
	_delay_us(10);
	
	// turn on interrupts
	sei();
	
	//now we send back the state of the status register.
	return(Status_reg);
}
Nrf24l01::Nrf24l01(){
	SPI_SETUP();
	Main_setup_nRF();
	count2 = 0;
	count1 = 0;
}
Nrf24l01::~Nrf24l01(){}
void Nrf24l01::Reset_IRQ(void)
{
	_delay_us(10);
	Send_Signal = (0<<CSN);	//CSN low
	_delay_us(10);
	SPI_Byte_TX_OR_RX(WRITE_REGISTER + STATUS);	//Write to STATUS register
	_delay_us(10);
	SPI_Byte_TX_OR_RX(0x70);	//Reset all IRQ interrupt
	_delay_us(10);
	Send_Signal = (1<<CSN);	//CSN IR_High
}
void Nrf24l01::Set_RX_Mode(void)
{
	//Here i define an arr only because the function must get an arr
	unsigned char Value_of_command[2];
	
	// turn off interrupts
	cli();
	
	//here we use config register to say the device is receiver
	//0x1E = MAX_RT interrupt not be refracted on the IRQ pin
	//0x1E = Enable CRC 2 Byte, POWER_UP = '1', PRX mode
	Value_of_command[0]= 0x0F;
	Write_Data_To_nRF(CONFIG,Value_of_command,1);
	
	//Now we Don't sending or receiving anything
	Send_Signal = (0<<CE);
	
	//Time Delay must is 1.5 mS from POWER_DOWN ==> START_UP i gave 2mS
	_delay_ms(2);
	
	// turn on interrupts
	sei();
}
void Nrf24l01::Read_Payload(unsigned char *Receive_Data)
{
	//now we get CSN to low so the nRF can listen
	Send_Signal = 0<<CSN;
	
	//now the SPI will send command of reading, and the name of the register we will like to read to.
	SPI_Byte_TX_OR_RX(READ_RX_PAYLOAD);
	_delay_us(10);
	
	for(char i = 0; i < Payload_Size; i++)
	{
		//Here we send dummy byte just to get it to work.
		*Receive_Data = SPI_Byte_TX_OR_RX(NOP);
		_delay_us(10);
		Receive_Data++;
	}
	
	//now we get CSN to High again and we stop the nRF communication
	Send_Signal = 1<<CSN;
	_delay_us(10);
}
unsigned char Nrf24l01::Receive_Payload(unsigned char *Receive_Data)
{
	unsigned char STATUS_reg_condition[2];
	
	// turn off interrupts
	cli();
	
	//Read the value of FIFO_STATUS register
	Read_Data_From_nRF(FIFO_STATUS,STATUS_reg_condition,1);
	
	//Check if bit RX_EMPTY is not '1', if bit = '1', RX_FIFO is Empty so we check if it is not '1'
	if (!(STATUS_reg_condition[0] & (1 << RX_EMPTY)))
	{
		//if so, that mean that they are more DATA in the FIFO from the last time we listened
		//so now we gonna read it without listening because it is already there
		Read_Payload(Receive_Data);
		
		// turn on interrupts
		sei();
		
		//because we want to avoid the function running into the listening code again, we use return
		//with value 0 so we know it is from memory.
		return 0;
	}
	//if the RX_FIFO empty, clean it, and clear interrupt and then start listening for new DATA
	else
	{
		//after reading the RX FIFO you must clean it other ways you will get dummy data
		//in order to send a command CSN must get low
		Send_Signal = 0<<CSN;
		
		//a small delay just to be sure
		_delay_us(2);
		
		//clean RX FIFO
		SPI_Byte_TX_OR_RX(FLUSH_RX);
		
		//return to high again, no more commands for now
		Send_Signal = 1<<CSN;
		
		//Clear all interrupts
		Reset_IRQ();
	}
	
	//set CE to 1 for receiving data
	Send_Signal = (1<<CE);
	
	//wait for data for 2mS
	_delay_us(2000);
	
	
	//The first value is '0x50' because we want to read the RX FIFO
	//any other value will make it to read register value and not the RX FIFO
	Read_Data_From_nRF(0x50,Receive_Data,Payload_Size);

	
	//stop listening
	Send_Signal = (0<<CE);
	
	// turn on interrupts
	sei();
	
	//return 1, so the user know the value is from listening and not from RX_FIFO memory
	return 1;
}
void Nrf24l01::Set_TX_Mode(void)
{
	//Here i define an arr only because the function must get an arr
	unsigned char Value_of_command[2];
	
	// turn off interrupts
	cli();
	
	//here we use config register to say the device is Transmitter
	//0x1E = MAX_RT interrupt not be refracted on the IRQ pin
	//0x1E = Enable CRC 2 Byte, POWER_UP = '1', PTX mode
	Value_of_command[0]= 0x0E;
	Write_Data_To_nRF(CONFIG,Value_of_command,1);
	
	//Now we Don't sending or receiving anything
	Send_Signal = (0<<CE);
	
	//Time Delay must is 1.5 mS from POWER_DOWN ==> START_UP i gave 2mS
	_delay_ms(2);
	
	// turn on interrupts
	sei();
}
bool Nrf24l01::Transmite_Payload(unsigned char *Data_Transmission, bool basicORhandshake)
{
	unsigned char Check_Status[2];
	
	// turn off interrupts
	cli();
	
	//This is the value to clear TX FIFO; 0xE1
	//It is a command that send through SPI
	
	//get the status register condition
	Write_Data_To_nRF(STATUS, Check_Status,1);
	
	//check if the transmitter reached to max of retransmissions
	if((Check_Status[0] & (1<<MAX_RT)) == 0x01)
	{
		//if it reached to max reset it
		Reset_IRQ();
	}
	
	//in order to send a command CSN must go low
	Send_Signal = 0<<CSN;
	
	//according to the data sheet TX FIFO must get clean after transfer
	SPI_Byte_TX_OR_RX(FLUSH_TX);
	
	//after the command CSN get high again
	Send_Signal = 1<<CSN;
	
	//Send the data that is in the Data_Transmission arr
	//By putting the '0x50' value, we saying that the information is for the TX FIFO. (Payload)
	//Payload_size is a DEFINE in the program, you can change it to the size you like (1-32)
	
	Write_Data_To_nRF(0x50, Data_Transmission,Payload_Size);
	//if you change the packet payload to more/less then 6(current value)
	//you must change the value in here too.
	
	//Enable the global interrupt
	sei();
	
	//CE is high to transmit data
	Send_Signal = (1<<CE);
	
	_delay_us(15);
	Send_Signal = (0<<CE);
	//we gave here a pulse of 15uS minimum for the data to be transmitted
	
	//this variable set the delay according to the file use. Bacis or HandShake
	if (basicORhandshake)
	{
		//if HandShake mode defined, we add 3mS to wait for the ack packet as well
		//delay of waiting to transmission (Tesb = Tul+2*Tstby2a+Toa+Tack+Tirq)=1100us
		_delay_us(4100);
	} 
	else
	{
		//delay of waiting to transmission (Tesb = Tul+2*Tstby2a+Toa+Tack+Tirq)=1100us
		_delay_us(1100);
	}	
	
	//Write_Data_To_nRF(STATUS, Check_Status,1);
	*Check_Status = SPI_Byte_TX_OR_RX(NOP);
	
	//Reset_IRQ();
	if(*Check_Status & (1<<TX_DS) || *Check_Status & (1<<RX_DR))
	{
		Reset_IRQ();
		Reset_IRQ();
		return true;
	}
	else
	{
		Reset_IRQ();
		Reset_IRQ();
		return false;
	}
}
bool Nrf24l01::PayloadAvailable()
{
	unsigned char STATUS_reg;

	//stop listening
	Send_Signal = (0<<CE);
	
	//get STATUS register value
	STATUS_reg = SPI_Byte_TX_OR_RX(NOP);
	
	//set CE to 1 for receiving data
	Send_Signal = (1<<CE);
	
	//wait for data
	_delay_ms(5);
	Reset_IRQ();
	
	//Check if RX_DR is = '0' he will return RX_DR value
	//that mean the interrupt have been active
	if(STATUS_reg & (1<<RX_DR))
	{
		return true;
	}
	//set CE to 1 for receiving data
	Send_Signal = (1<<CE);
	return false;
}