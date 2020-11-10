/*
 * NRF_Project.c
 *
 * Created: 25/08/2016 11:57:45
 * Author : Azriel
 */ 



/************************************************************************/
/*                              UART SETUP                              */
/************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
/*
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_putstring(unsigned char *StringPtr);
void Verafy_num(unsigned char value);
void Send_num(unsigned char num);


void USART_init(void){

	UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (3<<UCSZ00);
}

unsigned char USART_receive(void){

	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;

}

void USART_send( unsigned char data){

	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;

}

void USART_putstring(unsigned char *StringPtr){

	unsigned char i = 0;
	while(i != 0)
	{
		USART_send(StringPtr[i]);
		i++;
	}

}
void Verafy_num(unsigned char value)
{
	switch (value)
	{
		case 0:USART_send('0'); break;
		case 1:USART_send('1'); break;
		case 2:USART_send('2'); break;
		case 3:USART_send('3'); break;
		case 4:USART_send('4'); break;
		case 5:USART_send('5'); break;
		case 6:USART_send('6'); break;
		case 7:USART_send('7'); break;
		case 8:USART_send('8'); break;
		case 9:USART_send('9'); break;
		case 10:USART_send('A'); break;
		case 11:USART_send('B'); break;
		case 12:USART_send('C'); break;
		case 13:USART_send('D'); break;
		case 14:USART_send('E'); break;
		case 15:USART_send('F'); break;
	}
}
void Send_num(unsigned char num)
{
	Verafy_num(num/16);
	Verafy_num(num%16);
	USART_send(',');
	USART_send(' ');
}

*/
/************************************************************************/
/*                          END OF LCD UART                             */
/************************************************************************/


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <stdio.h>

/************************************************************************/
/*                          define all registers                        */
/************************************************************************/
#define CONFIG			0x00 //configuration register: control	RX_DR, TX_DS, MAX_RT, CRC, CRC_SIZE, PWR_UP, TX/RX_MODE
#define EN_AA			0x01 //Enhanced ShockBurst: En/Dis Auto ACK on data pipe (0 to 5)
#define EN_RXADDR		0x02 //Enable RX Address: En/Dis RX Addresses on Data pipe (0 to 5)
#define SETUP_AW		0x03 //Setup of Address width: 3/4/5 Byte (common to all data pipes)
#define SETUP_RETR		0x04 //Setup of Auto Retransmission: delay between packets sent (250uS to 4000uS) and ARC(retransmit amount 0-15)
#define RF_CH			0x05 //set the Channel frequency 
#define RF_SETUP		0x06 //RF Setup register: Set data rate speed. 250k/1M/2M or low mode 250Kbps and set up output power(0,-6,-12,-18)dBm
#define STATUS			0x07 //give an indication on: data arrived, data sent, max RT, pipe PAYLOAD available for reading(3 bit), TX FIFO full flag 
#define OBSERVE_TX		0x08 //2 counters of lost packets
#define RPD				0x09 //Received Power Detector: recognize power receiving   
#define RX_ADDR_P0		0x0A //Received Address data pipe (LSByte is written first) up to 5 Byte according to size you defined
#define RX_ADDR_P1		0x0B //Received Address data pipe (LSByte is written first) up to 5 Byte according to size you defined
#define RX_ADDR_P2		0x0C //Received Address data pipe (only LSByte) The MSByte stay the same as pipe 1
#define RX_ADDR_P3		0x0D //Received Address data pipe (only LSByte) The MSByte stay the same as pipe 1
#define RX_ADDR_P4		0x0E //Received Address data pipe (only LSByte) The MSByte stay the same as pipe 1
#define RX_ADDR_P5		0x0F //Received Address data pipe (only LSByte) The MSByte stay the same as pipe 1
#define TX_ADDR			0x10 //Transmit Address data pipe (LSByte is written first) set this address to be equal to Pipe 0
#define RX_PW_P0		0x11 //Set up RX payload size in pipe 0 (1-32 Byte) 0=Pipe not used
#define RX_PW_P1		0x12 //Set up RX payload size in pipe 1 (1-32 Byte) 0=Pipe not used
#define RX_PW_P2		0x13 //Set up RX payload size in pipe 2 (1-32 Byte) 0=Pipe not used
#define RX_PW_P3		0x14 //Set up RX payload size in pipe 3 (1-32 Byte) 0=Pipe not used
#define RX_PW_P4		0x15 //Set up RX payload size in pipe 4 (1-32 Byte) 0=Pipe not used
#define RX_PW_P5		0x16 //Set up RX payload size in pipe 5 (1-32 Byte) 0=Pipe not used
#define FIFO_STATUS		0x17 //give indication on: RX FIFO, TZ FIFO (empty or full) and, give option of reuse of last packet(in PTX)
#define DYNPL			0x1C //Enable Dynamic Payload Length: En/Dis the option for each Pipe
#define FEATURE			0x1D //it allow as to En/Dis all Pipes: Dynamic Payload, ACK Payload, W_TX_PAYLOAD_NOACK command. 
/************************************************************************/
/*                         define all commands                          */
/************************************************************************/
#define READ_RX_PAYLOAD			0x61
#define WRITE_TX_PAYLOAD		0xA0
#define FLUSH_TX				0xE1
#define FLUSH_RX				0xE2
#define REUSE_TX_PL				0xE3
#define READ_RX_PL_WIDTH		0x60
#define WRITE_TX_PAYLOAD_NOACK	0xB0
#define NOP						0xFF
#define  READ_REGISTER			0x00
#define  WRITE_REGISTER			0x20
#define  W_ACK_PAYLOAD			0xA8
/************************************************************************/
/*                    define all options of registers                   */
/************************************************************************/
#define MASK_RX_DR  6
#define MASK_TX_DS  5
#define MASK_MAX_RT 4
#define EN_CRC      3
#define CRCO        2
#define PWR_UP      1
#define PRIM_RX     0
#define ENAA_P5     5
#define ENAA_P4     4
#define ENAA_P3     3
#define ENAA_P2     2
#define ENAA_P1     1
#define ENAA_P0     0
#define ERX_P5      5
#define ERX_P4      4
#define ERX_P3      3
#define ERX_P2      2
#define ERX_P1      1
#define ERX_P0      0
#define AW          0
#define ARD         4
#define ARC         0
#define PLL_LOCK    4
#define RF_DR       3
#define RF_PWR      1
#define LNA_HCURR   0
#define RX_DR       6
#define TX_DS       5
#define MAX_RT      4
#define RX_P_NO     1
#define TX_FULL     0
#define PLOS_CNT    4
#define ARC_CNT     0
#define TX_REUSE    6
#define FIFO_FULL   5
#define TX_EMPTY    4
#define RX_FULL     1
#define RX_EMPTY    0
/************************************************************************/
/*                          PIN definition                              */
/************************************************************************/
#define  CE		0 //PORT B
#define IRQ		2 //PORT B
#define CSN		1 //PORT B
#define MOSI	3 //PORT B
#define MISO	4 //PORT B
#define SCK		5 //PORT B
/*****************PORT DEFINITION*******************/
#define Out_OR_IN	DDRB
#define READ_DATA	PINB
#define Send_Signal PORTB
/****************Define Size Of Payload*************/
#define Payload_Size 6

#define MaxPakcetTXtoRX 100
#define MaxPakcetRXtoTX 15
#define SwitchToRX		10
#define SwitchToTX		20
#define ON				1
#define OFF				0
/************************************************************************/
/*                        End of All Define                             */
/************************************************************************/
void SPI_SETUP (void);
unsigned char SPI_Byte_TX_OR_RX (unsigned char data);
unsigned char Write_Data_To_nRF(unsigned char Reg_Name, unsigned char *arr_of_data, unsigned char arr_Size);
unsigned char Read_Data_From_nRF(unsigned char Reg_Name, unsigned char *arr_of_data, unsigned char arr_Size);
void Set_interrupt(void);
void Main_setup_nRF(void);
void Reset_IRQ(void);
unsigned char Receive_Payload(unsigned char *Receive_Data);
void Transmite_Payload(unsigned char *Data_Transmission);
unsigned char Check_STATUS_Register();
void Read_Payload(unsigned char *Receive_Data);
void Set_RX_Mode(void);
void Set_TX_Mode(void);


//##################Toggle Functions##################
char RX_Process();
char TX_Process();
void OneTimeSetup();
void processRXorTX();
void SwithDefinedTXMode(char **Mode);
void SwithDefinedRXMode(char **Mode);
void switchBtweenModes(char *Mode);
char CheckIfExchangeIsSuccess(char ***Mode);
char CheckIfPakcerTranssmited();
char CheckIfDataReceived();
char TryAgain(char CurrentCondition, char ReTryAmount);
void SetPPScountTimer();
void SetBackToDefult();
char EnsureExchangeConditionTransition(char ExchangeConditionTransition);
char SetToggleONorOFF(char ONorOFF);
char SetControllerRXorTX(char RXorTXMode);

//TX = '1', RX = '0'
char  RXorTX = 0;
#define RX		1
#define TX		0
char OneTime = 1, OnOrOff = 0;
int count1 = 0, count2 = 0;

unsigned char Send_To_nRF[Payload_Size];
unsigned char Receive_From_nRF[Payload_Size];
//unsigned char send_or_receive[Payload_Size];

	/*
int main(void)
{
	
	unsigned char STATUS_is_ok;
	Main_setup_nRF();
	USART_init();
	Set_RX_Mode();
	//Set_TX_Mode();
	STATUS_is_ok = 0;
	
	while(1)
	{
		//Send_Signal = 1<<CE;
		//_delay_us(10000);
		//Send_Signal = 1<<CE;
		//Send_Signal = 0<<CSN;
		//Read_Data_From_nRF(FIFO_STATUS,send_or_receive,1);
		//Send_num(send_or_receive[0]);
		Read_Data_From_nRF(STATUS,send_or_receive,1);
		//Send_num(send_or_receive[0]);
		//Send_Signal = 0<<CSN;
		
		if(Receive_Payload(send_or_receive))
		{
			//Send_Signal = 0<<CE;
			Receive_Payload(send_or_receive);
			Send_num(send_or_receive[0]);
			Send_num(send_or_receive[1]);
			Send_num(send_or_receive[2]);
			Send_num(send_or_receive[3]);
			Send_num(send_or_receive[4]);
			Send_num(send_or_receive[5]);
			STATUS_is_ok ++;
			//Reset_IRQ();
			//Send_Signal = 1<<CE;
		}
		
		//Reset_IRQ();
		//_delay_ms(10);
		//send_or_receive[3]++;
		//Transmite_Payload(send_or_receive);
	}
	return 0;
}
*/
/************************************************************************/
/*                        Main Setup Functions                          */
/************************************************************************/
/*
ISR (INT0_vect)
{
	Receive_Payload(send_or_receive);
	Send_num(send_or_receive[0]);
	Send_num(send_or_receive[1]);
	Send_num(send_or_receive[2]);
	Send_num(send_or_receive[3]);
	Send_num(send_or_receive[4]);
	Send_num(send_or_receive[5]);
}
*/
/*******************************SPI_SETUP********************************/
/*Here we define the SPI protocol and define all pins that are used as  */
/*input or an out put, this function is called from the MAIN_SETUP, so  */
/*you don't need to call it in main.									*/
/************************************************************************/
void SPI_SETUP (void)
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
/***************************SPI_Byte_TX_OR_RX****************************/
/*This function sent/received only one byte, this function made only to	*/
/*make the code easer to read, this function is used only in the		*/
/*Write_Data_To_nRF or Read_Data_From_nRF functions.					*/
/************************************************************************/
unsigned char SPI_Byte_TX_OR_RX (unsigned char data)
{
	// Load data into the buffer
	SPDR = data;
	
	//Wait until transmission complete
	while(!(SPSR & (1<<SPIF) ));
	
	// Return received data
	return(SPDR);
}

void Set_interrupt()
{
	DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
	// PD2 (PCINT0 pin) is now an input

	PORTD |= (1 << PORTD2);    // turn On the Pull-up
	// PD2 is now an input with pull-up enabled


	EICRA |= (1 << ISC01);    // set INT0 to trigger on falling adge
	EIMSK |= (1 << INT0);     // Turns on INT0

	sei();                    // turn on interrupts

}
/*************************Write_Data_To_nRF******************************/
/*This function is use to write an max 32 byte of data by using an arr	*/
/*on the main function. by sending the arr you must declare is size, the*/
/*name of the arr is Data_communication and you can move in it any data */
/************************************************************************/
unsigned char Write_Data_To_nRF(unsigned char Reg_Name, unsigned char *arr_of_data, unsigned char arr_Size)
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


/*************************Read_Data_From_nRF*****************************/
/*This function is use to read an max 32 byte of data by using an arr	*/
/*on the main function. by receiving the arr you must declare is size,  */
/*name of the arr is Data_communication and you can move from it data   */
/************************************************************************/
unsigned char Read_Data_From_nRF(unsigned char Reg_Name, unsigned char *arr_of_data, unsigned char arr_Size)
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


/***************************Main_setup_nRF*******************************/
/*This function must be called in order to active the nRF24L01+  if you */
/*won't call this function, nothing is going to work. This function set */
/*the SPI communication and the interrupt on Port D, (it can be change) */
/*later on it define all the register, this setup define only one data  */
/*pipe of communication, you can change it for more, 5 byte address size*/
/*and Auto Ack on Pipe 0, you can see every definition down below       */ 
/************************************************************************/
void Main_setup_nRF(void)
{
	unsigned char Value_of_command[5];
	SPI_SETUP(); //Setup the SPI configuration 
	
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
unsigned char Check_STATUS_Register()
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
/********************************Reset_IRQ*******************************/
/*This function will be use to clear all kind of interrupts, the word   */
/*IRQ (interrupt request) goes HIGH in 3 cases 1.TX complete 2.RX comp' */
/*3.max retransmit. this function will clear all of those interrupts    */
/************************************************************************/
void Reset_IRQ(void)
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
/************************************************************************/
/*                               RX mode                                */
/************************************************************************/
void Set_RX_Mode(void)
{
	//Here i define an arr only because the function must get an arr
	unsigned char Value_of_command[1];
	
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

void Read_Payload(unsigned char *Receive_Data)
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

unsigned char Receive_Payload(unsigned char *Receive_Data)
{
	unsigned char STATUS_reg_condition[1];
	
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
/************************************************************************/
/*                               TX mode                                */
/************************************************************************/
void Set_TX_Mode(void)
{
	//Here i define an arr only because the function must get an arr
	unsigned char Value_of_command[1];
	
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

void Transmite_Payload(unsigned char *Data_Transmission)
{
	unsigned char Check_Status[1];
	
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
	
	_delay_us(80);
	Send_Signal = (0<<CE);
	//we gave here a pulse of 15uS for the data to be transmitted
	
	//once again a long delay before the next move
	_delay_us(900);
}




void switchBtweenModes(char* Mode)
{
	//NOTE: defined TX/RX mode mean: the controller is TX but can change to RX,
	//if there is problem with changing, so it will go to the main user defuled witch is RX/TX
	
	//check current mode if = 1 so it is TX mode else it is RX mode
	if (RXorTX)
	{
		//go to check if this mode is needed to be changed
		SwithDefinedTXMode(&Mode);
	}
	else
	{
		//go to check if this mode is needed to be changed
		SwithDefinedRXMode(&Mode);
	}
}

void SwithDefinedRXMode(char **Mode)
{
	//check if default RX mode is in RX mode
	if (**Mode == 0 || **Mode == SwitchToRX)
	{
		//check if the last sell is riches the value of changing (Last sell is use for counting receiving packages)
		if (Receive_From_nRF[Payload_Size-1] >= (char)MaxPakcetTXtoRX)
		{
			//if the counting is riches the value of changing, set the TX mode
			Set_TX_Mode();
			
			//value of SwitchToTX (constant value) moved into Mode, so when it enter in this function
			//next time, it will go to TX mode in the RX defined controller
			**Mode = SwitchToTX;
			
			//set the last sell (counting packet sell) back to zero
			Receive_From_nRF[Payload_Size-1] = 0;
			
			//check if the transform is succeed
			if (!(CheckIfExchangeIsSuccess(&Mode)))
			{
				//if it is not succeed, set it back to default
				SetBackToDefult();
			}
		}
	}
	//if it is not RX so check if it is TX mode
	else if (**Mode == 1 || **Mode == SwitchToTX)
	{
		//check if the last sell is riches the value of changing (Last sell is use for counting receiving packages)
		if (Send_To_nRF[Payload_Size-1] >= (char)MaxPakcetRXtoTX && EnsureExchangeConditionTransition(5))
		{
			//if the counting is riches the value of changing, set the RX mode 
			Set_RX_Mode();
			
			//value of SwitchToRX (constant value) moved into Mode, so when it enter in this function
			//next time, it will go to RX mode (Default direction)
			**Mode = SwitchToRX;
			
			//set the last sell (counting packet sell) back to zero
			Send_To_nRF[Payload_Size-1] = 0;
			
			//check if the transform is succeed
			if (!(CheckIfExchangeIsSuccess(&Mode)))
			{
				//if it is not succeed, set all setting back to default
				SetBackToDefult();
			}
		}
	}
}

void SwithDefinedTXMode(char **Mode)
{
	//check if default TX mode is in RX mode
	if (**Mode == 0 || **Mode == SwitchToRX)
	{
		//check if the last sell is riches the value of changing (Last sell is use for counting receiving packages)
		if (Receive_From_nRF[Payload_Size-1] >= (char)MaxPakcetRXtoTX)
		{
			//if the counting is riches the value of changing, set the TX mode
			Set_TX_Mode();
			
			//value of SwitchToTX (constant value) moved into Mode, so when it enter in this function
			//next time, it will go to TX mode in the TX defined controller
			**Mode = SwitchToTX;
			
			//set the last sell (counting packet sell) back to zero
			Receive_From_nRF[Payload_Size-1] = 0;
			
			//check if the transform is succeed
			if (!(CheckIfExchangeIsSuccess(&Mode)))
			{
				//if it is not succeed, set it back to default
				SetBackToDefult();
			}
		}
	}
	else if (**Mode == 1 || **Mode == SwitchToTX)
	{
		if (Send_To_nRF[Payload_Size-1] >= (char)MaxPakcetTXtoRX && EnsureExchangeConditionTransition(5))
		{
			//if the counting is riches the value of changing, set the RX mode
			Set_RX_Mode();
			
			//value of SwitchToRX (constant value) moved into Mode, so when it enter in this function
			//next time, it will go to RX mode in the TX defined controller
			**Mode = SwitchToRX;
			
			//set the last sell (counting packet sell) back to zero
			Send_To_nRF[Payload_Size-1] = 0;
			
			//check if the transform is succeed
			if (!(CheckIfExchangeIsSuccess(&Mode)))
			{
				//if it is not succeed, set it back to default
				SetBackToDefult();
			}
		}
	}
}

void processRXorTX()
{
	//Set static value of Mode, so we can update it in any function by pointer
	static char Mode;
	
	//one time setup, this setup will be active again when SetBackToDefault function has been called
	if (OneTime)
	{
		//set the mode and the global RXorTX to what the user choose in function SetControllerRXorTX
		Mode = RXorTX = SetControllerRXorTX(RXorTX);
		
		//do the one time setup before start
		OneTimeSetup();
		
		//disable this if condition
		OneTime = 0;
	}
	
	//check if we are in TX mode
	if (Mode == 1 || Mode == (char)SwitchToTX)
	{
		//go to the process routine of TX
		TX_Process();
	}
	else if (Mode == 0 || Mode == (char)SwitchToRX)
	{
		//go to the process routine of RX
		RX_Process();
	}
	
	//Check if the Toggle is Enabled by the user
	if (SetToggleONorOFF(OnOrOff))
	{
		//check if RX/TX need to be changed
		switchBtweenModes(&Mode);
	}
}
void OneTimeSetup()
{
	//check if we are defined in TX mode
	if (RXorTX)
	{
		//setup the TX mode
		Set_TX_Mode();
	}
	else
	{
		//setup the RX mode
		Set_RX_Mode();
	}
}
char TX_Process()
{
	//increase the last sell to count packet send in the RX&TX controllers
	Send_To_nRF[Payload_Size-1]++;
	
	//send the arr to the RX controller
	Transmite_Payload(Send_To_nRF);
	
	//check if the packet is transmitted
	if (CheckIfPakcerTranssmited())
	{
		//this variable use for count PPS (Packet Per Second)
		//it is use bt interrupt of timer 1
		count1++;
		
		//if the packet transmitted return 1
		return 1;
	}
	else
	{
		//if packet not transmitted send 0
		return 0;
		
		//this variable is for counting fail packets
		count2++;
	}
	//reset all interrupts
	Reset_IRQ();
}
char CheckIfDataReceived()
{
	//this arr is for getting STATUS register value
	char test[1] = {0};
	
	//for command
	Send_Signal = 0<<CSN;
	
	//a small delay just to be sure
	_delay_us(2);
	
	//Read STATUS register
	test[0] = SPI_Byte_TX_OR_RX(NOP);
	
	//end of command
	Send_Signal = 1<<CSN;

	//check if flag of receiving data is = 1 
	if(test[0] & (1 << 3) || test[0] & (1 << RX_DR) )
	{
		//return 1 = success
		return 1;
	}
	else if (test[0] & (1<<1))
	{
		Reset_IRQ();
	}
	
	//return 0 = fail
	return 0;
}
char RX_Process()
{
	//check if any data has been received
	if(CheckIfDataReceived())
	{
		//get the data that has been received into thr receive arr
		if(Receive_Payload(Receive_From_nRF))
		{
			//count for receive packet
			count1++;
		}
		else
		{
			//count for fail to receive packet
			count2++;
		}
		//return 1 = success
		return 1;
	}
	else
	{
		//return 0 = fail
		return 0;
	}
}
char CheckIfExchangeIsSuccess(char ***Mode)
{
	//check which mode we are in
	if (***Mode == 0 || ***Mode == SwitchToRX)
	{
		//check if packet received
		if(RX_Process())
		{
			//success
			return 1;
		}
		else
		{
			//not received give it another try (10 time to retry)
			if (TryAgain(***Mode,10))
			{
				//if after 10 time no success, return 0 = fail
				return 0;
			}
		}
	}
	else if (***Mode == 1 || ***Mode == SwitchToTX)
	{
		//check if packet has been send
		if(TX_Process())
		{
			//return success
			return 1;
		}
		else
		{
			//not transmitted give it another try (10 time to retry)
			if (TryAgain(***Mode,10))
			{
				//if after 10 time no success, return 0 = fail
				return 0;
			}
		}
	}
	//if it success in firs time or after trying a few time return 1 = success
	return 1;
}
char TryAgain(char CurrentCondition, char ReTryAmount)
{
	//static variable for counting success RX/TX
	static char CountSeccess = 0;
	
	//variable to check if it has been successful TX/RX
	char Value = 0;
	
	//as long as ReTrt != 0
	if (ReTryAmount != 0)
	{
		//check if we are in RX mode
		if (CurrentCondition == 0 || CurrentCondition == SwitchToRX)
		{
			//check if we received any data
			Value = RX_Process();
		}
		//check if we are in TX mode
		else if (CurrentCondition == 1 || CurrentCondition == SwitchToTX)
		{
			//check if we send data successfully
			Value = TX_Process();
		}
		//check if TX/RX was successful
		if (Value)
		{
			//check it it was successful more then 2 time
			if (CurrentCondition > 1)
			{
				//reset counter
				CountSeccess = 0;
				
				//return success
				return 1;
			}
			else
			{
				//count the success amount of times
				CountSeccess++;
				
				//call function again (recursion) and sub 1 from ReTry value
				TryAgain(CurrentCondition, ReTryAmount-1);
			}
		}
	}
	
	//reset counter 
	CountSeccess = 0;
	
	//return 0 = fail
	return 0;
}

void SetBackToDefult()
{
	//allow one time setup (in processRXorTX function) to be reactive
	OneTime = 1;
	
	//call process again
	processRXorTX();
}
char CheckIfPakcerTranssmited()
{
	//this one byte arr is for checking STATUS register
	unsigned char TXtransmit[1] = {0};
		
	//reading STATUS register value
	Read_Data_From_nRF(STATUS,TXtransmit,1);
	
	//check if Data Send flag is 1
	if (*TXtransmit & (1 << TX_DS))
	{
		//if so return success
		return 1;
	}
	else
	{
		//fail
		return 0;
	}
}
void ReTransmmitLastPacket()
{
	//in order to send a command CSN must go low
	Send_Signal = 0<<CSN;
	
	//this value is a command of re sending last packet
	SPI_Byte_TX_OR_RX(REUSE_TX_PL);
	
	//after the command CSN get high again
	Send_Signal = 1<<CSN;
}
void SetPPScountTimer()
{
	//timer value for 1 Sec interrupt
	OCR1A = 0x3D08;

	TCCR1B |= (1 << WGM12);
	// Mode 4, CTC on OCR1A

	TIMSK1 |= (1 << OCIE1A);
	//Set interrupt on compare match

	TCCR1B |= (1 << CS12) | (1 << CS10);
	// set prescaler to 1024 and start the timer

}

char EnsureExchangeConditionTransition(char ExchangeConditionTransition)
{
	//this function is use for re sending the exchange value of the last sell a few time, what for? well, since we are
	//working with RF so it could be that the packet didn't not send and the exchange will not be complete, so we send it
	//a few times to make sure that the RX got it.
	
	//check that the variable is != 0, this is a recurtion function
	if (ExchangeConditionTransition != 0)
	{
		//send the packet with change value signal
		Transmite_Payload(Send_To_nRF);
		
		//re call the function and decrease one from the last value
		EnsureExchangeConditionTransition(ExchangeConditionTransition-1);
	}
	//return 1, meaning we finished sending the signal at the amount of times the user asked
	return 1;
}
char SetToggleONorOFF(char ONorOFF)
{
	//this function is for the user to set toggle on or off into global variable
	OnOrOff = ONorOFF;
	
	//check if ON
	if (OnOrOff)
	{
		//return ON, constant value
		return ON;
	}
	else
	{
		//return OFF, constant value
		return OFF;
	}
}
char SetControllerRXorTX(char RXorTXMode)
{
	//this function is for the user to define the controller to be RX/TX into global variable
	RXorTX = RXorTXMode;
	
	//check if TX is been defined
	if (RXorTXMode)
	{
		//return TX, constant Value
		return TX;
	}
	else
	{
		//return TX, constant Value
		return RX;
	}
}
char CheckIfTheDataIsNewData()
{
	//set static variable to memory the last data
	static unsigned char MemoryLastData = 0xFF;
	
	//check if last sell in the arr value is different from the previous one
	if (Receive_From_nRF[Payload_Size - 1] != MemoryLastData)
	{
		//return success
		return 1;
	}
	else
	{
		//fail
		return 0;
	}
	
	//move current value to the static variable of function memory
	MemoryLastData = Receive_From_nRF[Payload_Size - 1];
}
