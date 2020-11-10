#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <math.h>
#include "SoftUART.h"
/*
SoftUart::SoftUart(BaudRate rate)
{
	setBaudRate(rate);
}

void SoftUart::setBaudRate(BaudRate rate)
{
	
}
*/
char SoftUart::SoftUartReceiveData(void)
{
	char data = 0;
	while(bit_is_set(PINC,0));
	if (!bit_is_set(PINC,0))
	{
		_delay_us(104.5);
		for(char i = 0; i < 8; i++)
		{
			_delay_us(51);
			data |= bit_is_set(PINC,0) ? (1 << i) : (0 << i);
			_delay_us(51);
		}
		_delay_us(10);
		if (bit_is_set(PINC,0))
		{
			_delay_us(94);
			return data;
		}
	}
	return 0;
}
/*
unsigned char SoftUart::UartReceiveDataString(void)
{
	int i = 0;
	while(SoftUartReceiveData() == 0)
	{
		_str[i] = SoftUartReceiveData();
		i++;
	}
	_str[i] = 0;
	return *_str;
}
*/
void SoftUart::SoftUartTransmiteData(char data)
{
	while(bit_is_set(PINC,0));
	if (!bit_is_set(PINC,0))
	{
		_delay_us(104.5);
		for(char i = 0; i < 8; i++)
		{
			_delay_us(51);
			data |= bit_is_set(PINC,0) ? (1 << i) : (0 << i);
			_delay_us(51);
		}
		_delay_us(10);
		if (bit_is_set(PINC,0))
		{
			_delay_us(94);
		}
	}
}
void SoftUart::UARTstring(const char *StringPtr ,char space)
{
	if (space)
	{
		SoftUartTransmiteData((const char)*" ");
	}
	while(*StringPtr != '\0')
	{
		SoftUartTransmiteData(*StringPtr);
		StringPtr++;
	}
	if (space)
	{
		SoftUartTransmiteData((const char)*" ");
	}
}
void SoftUart::UARTacko()
{
	char data;
	data=SoftUartReceiveData();
	SoftUartTransmiteData(data);
}
void SoftUart::verafyNum(unsigned char value)
{
	switch (value)
	{
		case 0:SoftUartTransmiteData('0'); break;
		case 1:SoftUartTransmiteData('1'); break;
		case 2:SoftUartTransmiteData('2'); break;
		case 3:SoftUartTransmiteData('3'); break;
		case 4:SoftUartTransmiteData('4'); break;
		case 5:SoftUartTransmiteData('5'); break;
		case 6:SoftUartTransmiteData('6'); break;
		case 7:SoftUartTransmiteData('7'); break;
		case 8:SoftUartTransmiteData('8'); break;
		case 9:SoftUartTransmiteData('9'); break;
		case 10:SoftUartTransmiteData('A'); break;
		case 11:SoftUartTransmiteData('B'); break;
		case 12:SoftUartTransmiteData('C'); break;
		case 13:SoftUartTransmiteData('D'); break;
		case 14:SoftUartTransmiteData('E'); break;
		case 15:SoftUartTransmiteData('F'); break;
	}
}
char SoftUart::stringCmp(unsigned char *ptr1,const char *ptr2)
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
char SoftUart::stringCmp(unsigned char *ptr1, char *ptr2)
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
char SoftUart::stringCmp(char *ptr1, char *ptr2)
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
void SoftUart::sendNum(unsigned char num)
{
	verafyNum(num/16);
	verafyNum(num%16);
	SoftUartTransmiteData(',');
	SoftUartTransmiteData(' ');
}
void SoftUart::printDecimalNumInAscii(unsigned long int num)
{
	int count = 1;
	int arr[10] = {0};
	while(num != 0)
	{
		arr[count] = num % 10;
		num/= 10;
		count++;
	}
	while(count != 0)
	{
		SoftUartTransmiteData(arr[count]+'0');
		count--;
	}
	UARTstring(",",1);
}
void SoftUart::UARTstring(unsigned char *ptr)
{
	while(*ptr != '\0')
	{
		SoftUartTransmiteData(*ptr);
		ptr++;
	}
}