#ifndef UART_H_
#define UART_H_


enum BaudRate{BAUD4800=4800,BAUD9600=9600,BAUD19200=19200,BAUD38400=38400,BAUD57600=57600};


#define RXinterruptEnable() ({UCSR0B |= (1<<RXCIE0);})
#define RXinterruptDisable() ({UCSR0B &= ~(1<<RXCIE0);})
class Uart
{
	private:
	char _str[50];
	char _maxDelay;
	char _countMaxDelay;
	bool maxDelay();
	public:
	Uart(BaudRate rate = BAUD9600);
	char checkForData();
	char getData();
	void setBaudRate(BaudRate rate);
	unsigned char UARTreceive(void);
	unsigned char UARTreceiveString(void);
	void UARTsend( unsigned char data);
	void UARTstring(const char *StringPtr = "No String Entered",char space = 1);
	void UARTacko();
	void verafyNum(unsigned char value);
	char stringCmp(unsigned char *ptr1,const char *ptr2);
	char stringCmp(unsigned char *ptr1, char *ptr2);
	char stringCmp(char *ptr1, char *ptr2);
	void sendNum(unsigned char num);
	void printDecimalNumInAscii(unsigned long int num);
	void UARTstring(unsigned char *ptr);
};
#endif /* UART_H_ */