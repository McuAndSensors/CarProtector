/*
 * NRF24L01__Basic.h
 *
 * Created: 22/02/2018 18:28:53
 *  Author: Adiel
 */ 

#ifndef NRF24L01_BASIC_H_
#define NRF24L01_BASIC_H_

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


class Nrf24l01{
	protected:
	int count1, count2;
	void SPI_SETUP (void);
	unsigned char SPI_Byte_TX_OR_RX (unsigned char data);
	void Set_interrupt();
	void Main_setup_nRF(void);
	unsigned char Check_STATUS_Register();
	unsigned char Write_Data_To_nRF(unsigned char Reg_Name, unsigned char *arr_of_data, unsigned char arr_Size);
	unsigned char Read_Data_From_nRF(unsigned char Reg_Name, unsigned char *arr_of_data, unsigned char arr_Size);
	public:
	Nrf24l01();
	~Nrf24l01();
	void Reset_IRQ(void);
	void Set_RX_Mode(void);
	void Read_Payload(unsigned char *Receive_Data);
	unsigned char Receive_Payload(unsigned char *Receive_Data);
	void Set_TX_Mode(void);
	bool Transmite_Payload(unsigned char *Data_Transmission, bool basicORhandshake = false);
	bool PayloadAvailable();
};




#endif /* NRF24L01+_BASIC_H_ */