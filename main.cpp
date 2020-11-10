/*
 * GSM.cpp
 *
 * Created: 19/12/2017 12:52:07
 * Author : Adiel
 */ 
#define  F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <string.h>
#include "UART.h"
#include "SoftUART.h"
#include "Gps.h"
#include "GpsLocation.h"
#include "NRF24L01_Basic.h"
#include "NRF24L01_HandShake.h"

class SMS
{
private:
	Uart gsmSMS;
	char _phoneBook[5][11];
	char _phoneNumber[50];
	char _recievedSMS[100];
	int _SMSindex;
	char _1minConterSMSreceived, _10secRestetGSMdelay , _GSMerrorCounter;
	bool _newData, _startTimeCounterSMSreceived, _startTimeCounterGSMreset;
	int _newDataIndex;
	bool sendCommand(const char ptr[], bool checkAck = false){
		int condition;
		gsmSMS.UARTstring(ptr,0);
		gsmSMS.UARTsend(13);
		if (checkAck)
		{
			char arr[15] = {0};
			RXinterruptDisable();
			condition = checkForACkPacket(arr, 14);
			RXinterruptEnable();
			if (*arr != 0)
			{
				if (compWordInArr(arr,"ERROR",5,condition))
				{
					return false;
				}
				else if (compWordInArr(arr,"OK",2,condition))
				{
					return true;
				}
				else if (compWordInArr(arr,'>',1,condition))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		} 
		else
		{
			return false;
		}
		return 0;
	}
	int checkForACkPacket(char getData[], int arrSize){
		int i = 0;
		char data = 0;
		
		do 
		{
			data = gsmSMS.UARTreceive();
			getData[i++] = data;
		}while(gsmSMS.checkForData() && i < arrSize);
		
		getData[i] = 0;
		if (i > 0)
		{
			return i;
		}
		else
		{
			return 0;
		}
	}
	char checkSignal(){
		if (sendCommand("AT+CSQ"))
		{
			/*
			if (_recievedPack[7]-'0' >= 0 && _recievedPack[7]-'0' <= 9)
			{
				return (_recievedPack[6]-'0')*10 + (_recievedPack[7]-'0');
			}
			else
			{
				return _recievedPack[6]-'0';
			}
			*/
		}
		return 0;
	}
	bool compWordInArr(const char *arr,const char *word, char wordSize, char arrMaxSize)
	{
		bool status = true;
		for(int i = 0; i < arrMaxSize; i++)
		{
			if (arr[i] == *word)
			{
				for (int j = 0; j < wordSize; j++,i++)
				{
					if (!(arr[i] == word[j]))
					{
						status = false;
					}
				}
				if (status)
				{
					return status;
				}
			}
		}
		return false;
	}
	bool compWordInArr(const char *arr,const char word, char wordSize, char arrMaxSize)
	{
		for(int i = 0; i < arrMaxSize; i++)
		{
			if (arr[i] == word)
			{
				return true;
			}
		}
		return false;
	}
	void setSMSindex()
	{
		int index = 3;
		
		while(_recievedSMS[index++] != ',' && index < 99);
		_SMSindex = _recievedSMS[index++] - '0';
			
		if (_recievedSMS[index]-'0' >= 0 && _recievedSMS[index]-'0' <= 9)
		{
			_SMSindex *= 10;
			_SMSindex += _recievedSMS[index] - '0';
		}
		if (_SMSindex > 20)
		{
			while(_SMSindex != 1)
			{
				deleteSMS(_SMSindex--);	
			}
		}
	}
	void resetGSM()
	{
		if (_GSMerrorCounter > 2)
		{
			PORTD &= ~(1<<5);
			_delay_ms(1000);
			PORTD |= (1<<5);
			_startTimeCounterGSMreset = true;
			_GSMerrorCounter = 0;
		}
	}
public:
	SMS(){
		DDRC = 0x02;
		DDRD |= (1<<5);
		PORTD |= (1<<5);
		*_phoneBook[1] = 0;
		*_phoneBook[2] = 0;
		*_phoneBook[3] = 0;
		*_phoneBook[4] = 0;
		_GSMerrorCounter = _1minConterSMSreceived = 0;
		_startTimeCounterSMSreceived = false;
		_newData = false;
		_newDataIndex = 0;
		setup(BAUD9600);}
	~SMS(){}
	char cmpSMSPhoneNumberToStorage(char *SMSPhoneNum){
		if(phoneCmp(SMSPhoneNum,_phoneBook[1])){
			return 1;
		}
		else if(phoneCmp(SMSPhoneNum,_phoneBook[2])){
			return 2;
		}
		else if(phoneCmp(SMSPhoneNum,_phoneBook[3])){
			return 3;
		}
		return 0;
	}
	bool delPhoneNum(char index){
		if(index >= '1' && index <= '3')
		{
			char arr[14];
			strcpy(arr,"AT+CPBW=X,,,");
			arr[8] = index;
			return sendCommand(arr,true);
		}
		return false;
	}
	void copyPhoneFromSimToRAM(){
		char phoneNum[15] = {0};
		for(int i = 1; i < 4; i++)
		{
			getPhoneBookNumber(phoneNum,i);
			if (*phoneNum != 0)
			{
				strcpy(_phoneBook[i],phoneNum);
			}
		}
	}
	void strCopy(char *dest, const char *source, int maxSize){
		int size = 0;
		while(size > maxSize && (source[size] != '\0' || dest[size] != '\0'))
		{
			dest[size] = source[size];
			size++;
		}
	}
	void timerSMSinterrupHandle(){
			if(_startTimeCounterSMSreceived)
			{
				if (_1minConterSMSreceived > 12)
				{
					_GSMerrorCounter++;
					_1minConterSMSreceived = 0;
					resetGSM();
				}
				else
				{
					_1minConterSMSreceived++;
				}
			}
		}
	void timerGSMresetInterrupHandle(){
		if(_startTimeCounterGSMreset)
		{
			if (_10secRestetGSMdelay > 2)
			{
				_10secRestetGSMdelay = 0;
				_startTimeCounterGSMreset = false;
				setup(BAUD9600);
			}
			else
			{
				_10secRestetGSMdelay++;
			}
		}
	}
	bool isNewDataReceived()
	{
		bool newData = _newData;
		_newData = false;
		return newData;
	}
	char *getPhoneBookNumber(char phoneNum[],char index){
		char arrCommand[15] ={"AT+CPBR=X\r\n"};
		char dataIn[50] = {0};
		RXinterruptDisable();
		arrCommand[8] = index + '0';
		gsmSMS.UARTstring(arrCommand,0);	
		checkForACkPacket(dataIn, 49);
		RXinterruptEnable();
		if (compWordInArr(dataIn,'"',1,49) && compWordInArr(dataIn+15,'"',1,34))
		{
			int counter = 0;
			while(dataIn[counter] != '0' && counter < 15)
			{
				counter++;
			}
			dataIn[counter+10] = '\0';
			strcpy(phoneNum,dataIn+counter);
			return _phoneNumber;
		}
		return 0;
	}
	int getRXackID(){
		return _newDataIndex;
	}
	void clearRXackID(){
		_newDataIndex = 0;
	}
	void setBaudRate(BaudRate baud){
		gsmSMS.setBaudRate(baud);
	}
	void setup(BaudRate BAUD = BAUD9600){
		//_delay_ms(3000);
		
		gsmSMS.setBaudRate(BAUD);
		char ptr[15] = {'A','T','+','C','S','C','S','=','"','G','S','M','"',0};
		sendCommand(ptr,true);
		sendCommand("AT+CMGF=1",true);
		sendCommand("AT+MORING=1",true);
		copyPhoneFromSimToRAM();
	}
	bool sendSMS(const char *ptr,int index, const char *massage2 = NULL, const char *massage3 = NULL, const char *massage4 = NULL, const char *massage5 = NULL){
		char command[25];
		if (*getPhoneNumber(index) == 0)
		{
			return false;
		}
		_delay_ms(50);
		strcpy(command,"AT+CMGS=");											//copy command
		strcpy(command+9,getPhoneNumber(index));							//copy phone number
		command[8] = command[19] = '"';										//set <"> for phone number
		command[20] = 0;													//close number with <">, run over the dummy char
		
		sendCommand(command,true);
		
		gsmSMS.UARTstring(ptr,0);
		if (massage2 != NULL)
		{
			gsmSMS.UARTsend(13);
			gsmSMS.UARTstring(massage2,0);
		}
		if (massage3 != NULL)
		{
			gsmSMS.UARTsend(13);
			gsmSMS.UARTstring(massage3,0);
		}
		if (massage4 != NULL)
		{
			gsmSMS.UARTsend(13);
			gsmSMS.UARTstring(massage4,0);
		}
		if (massage5 != NULL)
		{
			gsmSMS.UARTsend(13);
			gsmSMS.UARTstring(massage5,0);
		}
		gsmSMS.UARTsend(26);
		gsmSMS.UARTsend(13);
		_startTimeCounterSMSreceived = true;
		return false;
	}
	void checkStatus(){	
		char checkInterrupt[50];
		int i = 0;
		char data = 0;
		do
		{
			data = gsmSMS.UARTreceive();
			checkInterrupt[i++] = data;
		}while(gsmSMS.checkForData() && i < 49);
		checkInterrupt[i+1] = 0;
		
		if (i>1)
		{
			if (compWordInArr(checkInterrupt,"RING",4,i)||compWordInArr(checkInterrupt,"CLIP",4,i))
			{
				//gsmSMS.UARTstring("call received");
				_newData = true;
				_newDataIndex = 3;
			}
			else if (compWordInArr(checkInterrupt,"CMTI",4,i)||compWordInArr(checkInterrupt,"SM",2,i))
			{
				//gsmSMS.UARTstring("S_M_S");
				
				strcpy(_recievedSMS,checkInterrupt);
				setSMSindex();
				_newData = true;
				_newDataIndex = 4;
			}
			else if(compWordInArr(checkInterrupt,"+CMGS:",6,i)||compWordInArr(checkInterrupt,"CMGS:",5,i))
			{
				//gsmSMS.UARTstring("sms SENT\n");
				_newDataIndex = 5;
				_newData = true;
				_startTimeCounterSMSreceived = false;
				_1minConterSMSreceived = 0;
			}
			else if(compWordInArr(checkInterrupt,"CPIN",4,i)||compWordInArr(checkInterrupt,"CFUN",4,i))
			{
				_newDataIndex = 6;
				_newData = true;
			}
			else if(compWordInArr(checkInterrupt,"CONNECTED",9,i))
			{
				_newDataIndex = 7;
				_newData = true;
			}
			
		}
	}
	bool readSMS(char arr[], int arrSize, bool deleteSms = false, char phoneNumber[] = NULL){
		int indexNum = 10, indexData = 0, indexOk = 0;
		int size = 0;
		char arrData[20];
		RXinterruptDisable();
		if (_SMSindex < 10)
		{
			strcpy(arrData,"AT+CMGR= ");
			arrData[8] = _SMSindex+'0';
		}
		else
		{
			strcpy(arrData,"AT+CMGR=  ");
			arrData[8] = _SMSindex/10+'0';
			arrData[9] = _SMSindex%10+'0';
		}
		sendCommand(arrData,false);
		size = checkForACkPacket(arr, arrSize);
			
		//check if the data exist before getting into the While LOOP
		if (compWordInArr(arr+indexNum,'"',1,size) && compWordInArr(arr+indexNum,'+',1,size))
		{
			//get phone index number
			while(!(arr[++indexNum] == '"' && arr[++indexNum] == '+') && indexNum < arrSize);
			indexData = indexNum;	//data mast be after number
		}
		else
		{
			RXinterruptEnable();
			return 0;
		}
			
		//check if the data exist before getting into the While LOOP
		if (compWordInArr(arr+indexData,'\n',1,size))
		{
			//get data, index number.
			while(arr[indexData++] != '\n' && indexData < arrSize);
			indexOk = indexData;	//OK must be after data
		}
		else
		{
			RXinterruptEnable();
			return 0;
		}
			
		//check if the data exist before getting into the While LOOP
		if (compWordInArr(arr+indexOk,'\n',1,size))
		{
			//get end of data index number (it will get down a line and send OK)
			while(arr[indexOk++] != '\n' && indexOk < arrSize);
			//_recievedPackByCommand[indexNum+13] = 0;		//set end of string for strcpy()
		}
		else
		{
			RXinterruptEnable();
			return 0;
		}
		
		if (phoneNumber != NULL)
		{
			arr[indexNum+15] = '\0';
			//copy the phone number
			strcpy(phoneNumber,arr+indexNum+3);
			//set phone start number, always 0
			phoneNumber[0] = '0';
			phoneNumber[10] = 0;
		}
			
		arr[indexOk-2] = 0;	//put end of string after the end of data
		strcpy(arr,arr+indexData); //copy data
		if (deleteSms)
		{
			deleteSMS(_SMSindex);
		}
			
		RXinterruptEnable();
		return true;
	}
	bool deleteSMS(char SMSindex = 1){
		char arr[13];
		if (SMSindex < 10)
		{
			strcpy(arr,"AT+CMGD= ");
			arr[8] = SMSindex+'0';
		}
		else
		{
			strcpy(arr,"AT+CMGD=  ");
			arr[8] = SMSindex/10+'0';
			arr[9] = SMSindex%10+'0';
		}
		return sendCommand(arr,true);
	}
	bool setNewNum(const char *ptr,char index = 0){
		if(index >= '1' && index <= '4')
		{
			char arr[40];
			strcpy(arr,"AT+CPBW=X,");
			arr[8] = index;
			strcpy(arr+11,ptr);
			arr[10] = arr[21] = '"';
			strcpy(arr+22,",129,");
			return sendCommand(arr,true);
		}
		return false;
	}
	bool phoneCmp(const char *str1, const char *str2){
		bool result = true;
		
		//check if *str1 OR *str2 equle to 0.
		//if we don't check it, it will fail before the for loop condition and return true.
		if(!(*str1 && *str2))
		{
			return false;
		}
		
		for(char i = 0;((*str2 != 0 || *str1 != 0) && (result == true)) && i < 10; i++)
		{
			if(*(str1++) == *(str2++))
			{
				result = true;
			}
			else
			{
				return false;
			}
		}
		return result;
	}
	char *getPhoneNumber(int index){
		return _phoneBook[index];}
	void copyTemperaryPhoneFromSimToRAM(char *tempPhone){
		tempPhone[11] = '\0';
		strcpy(_phoneBook[4],tempPhone);
	}
	bool call(int index){
		char arr[16];
		strcpy(arr,"ATD");
		strcpy(arr+3,getPhoneNumber(1));
		arr[13] = ';';
		arr[14] = 0;
		return sendCommand(arr,true);
		}
	bool hangUpCall(){
		return sendCommand("ATH",true);
	}
};	
class mainControl: public SMS, public MovedFromLocation, public Nrf24l01_HandShake
{
private:
	unsigned char _sendPacket[6];
	char _indexOfContact;
	bool _alarmOnOff, _emergencyAlarmON;
	bool _doorOpenClose, _callOneTimeOnEmergencyMode;
	bool _startTimeCounterCarAlarm, _startTimeCounterEmergencyCarLocation;
	bool _carAlarmTimerOverFlow, _emergencyCarLocationTimerOverFlow;
	char  _10minCounterCarAlarm, _30secCounterEmergencyCarLocation;
	void timerSetting(){
			TCNT1 = 63974;   // for 1 sec at 16 MHz

			TCCR1A = 0x00;
			TCCR1B = (1<<CS10) | (1<<CS12);;  // Timer mode with 1024 prescler
			TIMSK1 = (1 << TOIE1) ;   // Enable timer1 overflow interrupt(TOIE1)
	}
	void changeArrToSmallLeters(char *arr, char arrMaxSize){
		for (int i = 0; i < arrMaxSize; i++)
		{
			if (arr[i] < 'a' && arr[i] >= 'A')
			{
				arr[i] = arr[i] + 32;
			}
		}
	}	
	bool compWordInArr(char *arr,const char *word, char wordSize, char arrMaxSize)
	{
		changeArrToSmallLeters(arr,arrMaxSize);
		bool status = true;
		for(int i = 0; i < arrMaxSize; i++)
		{
			if (arr[i] == *word)
			{
				for (int j = 0; j < wordSize; j++,i++)
				{
					if (!(arr[i] == word[j]))
					{
						status = false;
					}
				}
				if (status)
				{
					return status;
				}
			}
		}
		return false;
	}	
public:
	mainControl()
	{
		_carAlarmTimerOverFlow = _alarmOnOff = _doorOpenClose = _emergencyAlarmON = false;
		_emergencyCarLocationTimerOverFlow = false;
		_callOneTimeOnEmergencyMode = true;
		_10minCounterCarAlarm = _30secCounterEmergencyCarLocation = _indexOfContact = 0;
		resetPacket();
		Set_RX_Mode();
		timerSetting();
	}
	void timerCarSetToLockedInterrupHandle(){
		if (_startTimeCounterCarAlarm)
		{
			if (_10minCounterCarAlarm > 120)
			{
				_carAlarmTimerOverFlow = true;
				_startTimeCounterCarAlarm = false;
				_10minCounterCarAlarm = 0;
			}
			else
			{
				_10minCounterCarAlarm++;
			}
		}
	}
	void timerEmergencyCarLocationInterrupHandle(){
		if (_startTimeCounterEmergencyCarLocation)
		{
			if (_30secCounterEmergencyCarLocation > 6)
			{
				_emergencyCarLocationTimerOverFlow = true;
				_30secCounterEmergencyCarLocation = 0;
			}
			else
			{
				_30secCounterEmergencyCarLocation++;
			}
		}
	}
	void openTheCar(){
		_alarmOnOff = false;
	}
	unsigned char *packet(){
		return _sendPacket;
	}
	void resetPacket(){
		_sendPacket[0] = 0xEF;
		_sendPacket[1] = 0xAA;
		_sendPacket[2] = _sendPacket[3] = _sendPacket[4] = _sendPacket[5] = 0;
	}
	bool carAlarmed(){
		if (_carAlarmTimerOverFlow)
		{
			_alarmOnOff = true;
		}
		return _alarmOnOff;
	}
	void startTimeCounter(){
		if (!_alarmOnOff)
		{
			_startTimeCounterCarAlarm = true;
		}
	}
	void resetTimeConter(){
		_10minCounterCarAlarm = 0;
		if (_alarmOnOff)
		{
			_startTimeCounterEmergencyCarLocation = true;
			_emergencyAlarmON = true;
		}
	}
	int inputCommandBySMS(char *ptr, int arrSize, char *phoneNumber)
	{
		_indexOfContact = cmpSMSPhoneNumberToStorage(phoneNumber);
		if (_indexOfContact == 0)
		{
			if (*getPhoneNumber(1) != 0 || *getPhoneNumber(2) != 0 || *getPhoneNumber(3) != 0)
			{
				return 100;
			}
			else
			{
				copyTemperaryPhoneFromSimToRAM(phoneNumber);
				_indexOfContact = 4;
			}
		}
		
		if (compWordInArr(ptr,"new number",10,20))
		{
			return 1;
		} 
		else if (compWordInArr(ptr,"open the car",12,20))
		{
			return 2;
		}
		else if (compWordInArr(ptr,"new id",6,20))
		{
			return 3;
		}
		else if (compWordInArr(ptr,"delete id",9,20))
		{
			return 4;
		}
		else if (compWordInArr(ptr,"delete number",13,20))
		{
			return 5;
		}
		else if (compWordInArr(ptr,"car location",12,20))
		{
			return 6;
		}
		else if (compWordInArr(ptr,"default",7,20))
		{
			return 7;
		}
		else if (compWordInArr(ptr,"stop",4,20))
		{
			return 8;
		}
		else if (compWordInArr(ptr,"call",4,20))
		{
			return 9;
		}
		else if (compWordInArr(ptr,"disable the car",15,20))
		{
			return 10;
		}
		else if (compWordInArr(ptr,"alarm",5,20))
		{
			return 11;
		}
		else if (compWordInArr(ptr,"open",12,20))
		{
			return 12;
		}
		return 0;
	}
	bool commandAction(int commandIndex, char *ptr){
		char ptr_6_9[13] = "car is armed";
		char ptr_3_4[16] = "Wrong ID number";
		switch(commandIndex)
		{
			case  0:
			{
				sendSMS("unknown command",_indexOfContact);
				return true;
				break;
			}
			case  1:
			{
				if (*(ptr+21) == ' ')
				{
					if (setNewNum(ptr+11,*(ptr+22)))
					{
						copyPhoneFromSimToRAM();
						sendSMS("New number was set",_indexOfContact);
					}
					else
					{
						sendSMS("Fail",_indexOfContact);
					}
				} 
				else
				{
					sendSMS("ERROR",_indexOfContact);
				}
				return true;
				break;
			}
			case  2:
			{
				_alarmOnOff = false;
				_carAlarmTimerOverFlow = false;
				sendSMS("The car is Unlocked!",_indexOfContact);
				return true;
				break;
			}
			case  3:
			{
				if (ptr[10] > '0' && '9' >= ptr[10])
				{
					_sendPacket[2] = 0x10;
					_sendPacket[3] = ptr[10] - '0';
					sendSMS("Start The Process",_indexOfContact);
				}
				else
				{
					sendSMS(ptr_3_4,_indexOfContact);
				}
				return true;
				break;
			}
			case  4:
			{
				if (ptr[10] > '0' && '9' >= ptr[10])
				{
					_sendPacket[2] = 0x20;
					_sendPacket[3] = ptr[10] - '0';
					sendSMS("ID was deleted",_indexOfContact);
				}
				else
				{
					sendSMS(ptr_3_4,_indexOfContact);
				}
				return true;
				break;
			}
			case  5:
			{
				if (*(ptr+14) > '0' && *(ptr+14) < '4')
				{
					if (delPhoneNum(*(ptr+14)))
					{
						copyPhoneFromSimToRAM();
						sendSMS("Number was deleted",_indexOfContact);
					}
					else
					{
						sendSMS("Fail",_indexOfContact);
					}
				}
				else
				{
					sendSMS("ERROR",_indexOfContact);
				}
				return true;
			}
			case  6:
			{
				if (_alarmOnOff)
				{
					sendSMS(getGoogleMapsLink(),_indexOfContact,ptr_6_9);
				}
				else
				{
					sendSMS(getGoogleMapsLink(),_indexOfContact,"car is NOT armed");
				}
				return true;
				break;
			}
			case  7:
			{
				_sendPacket[2] = 0x30;
				sendSMS("System Back To DEFAULT",_indexOfContact);
				return true;
				break;
			}
			case  8:
			{
				_emergencyAlarmON = false;
				_startTimeCounterEmergencyCarLocation = false;
				_callOneTimeOnEmergencyMode = true;
				sendSMS("OK",_indexOfContact);
				break;
			}
			case  9:
			{
				return call(1);
				break;
			}
			case 10:
			{
				sendSMS("Car Disabled",_indexOfContact);
				return true;
				break;
			}
			case 11:
			{
				_alarmOnOff = true;
				sendSMS(ptr_6_9,_indexOfContact);
				return true;
				break;
			}
			case 12:
			{
				break;
			}
		}
		return false;
	}
	void emergencyCallIsanswer(){
		_callOneTimeOnEmergencyMode = false;
	}
	void alarmProtocol(){
		if (_emergencyAlarmON)
		{
			if (_callOneTimeOnEmergencyMode)
			{
				call(1);
			}
			else if (_emergencyCarLocationTimerOverFlow)
			{
				char *ptr = getGoogleMapsLink();
				sendSMS("The car might be stolen",1,ptr);
				_emergencyCarLocationTimerOverFlow = false;
			}
		}
	}
};

Uart check;
mainControl top;
ISR(USART_RX_vect)
{
	RXinterruptDisable();
	top.checkStatus();
	RXinterruptEnable();
}
ISR (TIMER1_OVF_vect){
	TCNT1 = 1;   //interrupt every 5 sec at 16 MHz clock
	top.timerSMSinterrupHandle();
	top.timerGSMresetInterrupHandle();	
	top.timerCarSetToLockedInterrupHandle();
	top.timerEmergencyCarLocationInterrupHandle();
}
int main(void)
{
	sei();
	check.setBaudRate(BAUD9600);
	RXinterruptEnable();
	char arr[101];
	char SMSrecievedPhoneNumber[15];
    while (1) 
    {
		RXinterruptEnable();
		top.carAlarmed();	//check if timer is up and lock the car
		top.alarmProtocol(); //check if alarm is activated and start sending a massages
		if(top.PayloadAvailable())
		{
			if (*(top.packet()+2) > 0)
			{
				static char count = 0;
				if (count >= 2)
				{
					count = 0;
				} 
				else
				{
					count++;
				}
			}
			unsigned char *Payload = top.Receive_Payload(top.packet());
			if (Payload[5] == 0x10)
			{
				top.openTheCar();
			}
		}
		if (top.getRXackID() == 4)
		{
			top.clearRXackID();
			top.readSMS(arr,100,true,SMSrecievedPhoneNumber);
			int index = top.inputCommandBySMS(arr,100,SMSrecievedPhoneNumber);
			top.commandAction(index,arr);
		}
		else if (top.getRXackID() == 3)
		{
			top.clearRXackID();
			top.sendSMS("CALL WAS RECEIVED!",1);
		}
		else if (top.getRXackID() == 7)
		{
			top.clearRXackID();
			top.emergencyCallIsanswer();
		}
		
		if(top.checkIfMoved())
		{
			//it will be reset if the car is not lock, else it will active emergency mode
			top.resetTimeConter();
		}
		else
		{
			top.startTimeCounter();
		}
    }
}

