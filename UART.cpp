/*
 * UART.cpp
 *
 * Created: 23/11/2017 16:24:53
 *  Author: Adiel
 */ 

#include <avr/io.h>
#include <util/delay.h>
class Uart
{
private:
	enum BaudRate{9600}//{4800=4800,9600=9600,19200=19200,38400=38400,57600=57600,115200=115200};
	//unsigned char *stringPtr;
	Uart()
	{
	}
	~Uart(){}
public:	
	Uart()
	{
		
	}
	~Uart()
	{
		
	}

	void USARTsetup(BaudRate rate = 9600)
	{
		unsigned int BAUD_PRESCALLER = (((F_CPU / (rate * 16UL))) - 1)
		UBRR0H = (unsigned int)(BAUD_PRESCALLER>>8);
		UBRR0L = (unsigned int)(BAUD_PRESCALLER);
		UCSR0B = (1<<RXEN0)|(1<<TXEN0);
		UCSR0C = (3<<UCSZ00);
	}
	unsigned char UARTreceive(void)
	{
		while(!(UCSR0A & (1<<RXC0)));
		return UDR0;
	}

	void UARTsend( unsigned char data)
	{
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = data;
	}

	void UARTstring(unsigned char *StringPtr)
	{
		StringPtr = new unsigned char(sizeof(*StringPtr+1));
		unsigned char i = 0;
		while(i != 0)
		{
			UARTsend(StringPtr[i]);
			i++;
		}
		delete StringPtr;
	}
	void verafyNum(unsigned char value)
	{
		switch (value)
		{
			case 0:UARTsend('0'); break;
			case 1:UARTsend('1'); break;
			case 2:UARTsend('2'); break;
			case 3:UARTsend('3'); break;
			case 4:UARTsend('4'); break;
			case 5:UARTsend('5'); break;
			case 6:UARTsend('6'); break;
			case 7:UARTsend('7'); break;
			case 8:UARTsend('8'); break;
			case 9:UARTsend('9'); break;
			case 10:UARTsend('A'); break;
			case 11:UARTsend('B'); break;
			case 12:UARTsend('C'); break;
			case 13:UARTsend('D'); break;
			case 14:UARTsend('E'); break;
			case 15:UARTsend('F'); break;
		}
	}
	void sendNum(unsigned char num)
	{
		verafyNum(num/16);
		verafyNum(num%16);
		UARTsend(',');
		UARTsend(' ');
	}
};
void main()
{
	
}