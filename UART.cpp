#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <math.h>
#include "UART.h"

Uart::Uart(BaudRate rate)
{
	_maxDelay = rate/9600;
	_countMaxDelay = 0;
	setBaudRate(rate);
}
void Uart::setBaudRate(BaudRate rate)
{
	unsigned int BAUD_PRESCALLER = (((F_CPU / (rate * 16UL))) - 1);
	UBRR0H = (unsigned int)(BAUD_PRESCALLER>>8);
	UBRR0L = (unsigned int)(BAUD_PRESCALLER);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (3<<UCSZ00);
}
bool Uart::maxDelay()
{
	if (_countMaxDelay > 10)
	{
		return true;
	}
	else
	{
		switch(_maxDelay)
		{
			case 1: _delay_ms(30/1); break;
			case 2: _delay_ms(30/2); break;
			case 3: _delay_ms(30/3); break;
			case 4: _delay_ms(30/4); break;
		}
		_countMaxDelay++;
		return false;
	}
}
char Uart::checkForData()
{
	for(int i = 0; i < 200; i++)
	{
		if ((UCSR0A & (1<<RXC0)))
		{
			return 1;
		}
		_delay_us(150);
	}
	return 0;
}
char Uart::getData()
{
	return UDR0;
}
unsigned char Uart::UARTreceive(void)
{
	while((!(UCSR0A & (1<<RXC0))) && maxDelay());
	return UDR0;
}
unsigned char Uart::UARTreceiveString(void)
{
	int i = 0;
	while(UARTreceive() == 0)
	{
		_str[i] = UARTreceive();
		i++;
	}
	_str[i] = 0;
	return *_str;
}
void Uart::UARTsend( unsigned char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}
void Uart::UARTstring(const char *StringPtr ,char space)
{
	if (space)
	{
		UARTsend((const char)*" ");
	}
	while(*StringPtr != '\0')
	{
		UARTsend(*StringPtr);
		StringPtr++;
	}
	if (space)
	{
		UARTsend((const char)*" ");
	}
}
void Uart::UARTacko()
{
	char data;
	data=UARTreceive();
	UARTsend(data);
}
void Uart::verafyNum(unsigned char value)
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
char Uart::stringCmp(unsigned char *ptr1,const char *ptr2)
{
	while(*ptr1 == '\0' || *ptr2 == '\0')
	{
		if (*ptr1 == *ptr2)
		{
			ptr2++;
			ptr1++;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}
char Uart::stringCmp(unsigned char *ptr1, char *ptr2)
{
	while(*ptr1 == '\0' || *ptr2 == '\0')
	{
		if (*ptr1 == *ptr2)
		{
			ptr2++;
			ptr1++;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}
char Uart::stringCmp(char *ptr1, char *ptr2)
{
	while(*ptr1 == '\0' || *ptr2 == '\0')
	{
		if (*ptr1 == *ptr2)
		{
			ptr2++;
			ptr1++;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}
void Uart::sendNum(unsigned char num)
{
	verafyNum(num/16);
	verafyNum(num%16);
	UARTsend(',');
	UARTsend(' ');
}
void Uart::printDecimalNumInAscii(unsigned long int num)
{
	int count = 1;
	int arr[10] = {0};
	while(num != 0 && count < 10)
	{
		arr[count] = num % 10;
		num/= 10;
		count++;
	}
	while(count != 0)
	{
		UARTsend(arr[count]+'0');
		count--;
	}
	UARTstring(",",1);
}
void Uart::UARTstring(unsigned char *ptr)
{
	while(*ptr != '\0')
	{
		UARTsend(*ptr);
		ptr++;
	}
}