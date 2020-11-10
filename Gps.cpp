#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <math.h>
#include "Gps.h"
#include "UART.h"
#include "SoftUART.h"
SoftUart UartGps;
	int GPS::getPart(char part)//1= time---2&4=Latitude and Longitude-----6= speed
	{
		int count = 0;
		for (int i = 1; i <= part; i++)
		{
			count++;
			while(gpsData[count] != ',' && count < 90)
			{
				count++;
			}
		}
		return count+1;
	}
	int GPS::cmp(char *str1, const char *str2)
		{
			char count1 = 0, count2 = 0;
			while(*str1 != '\0' || *str2 != '\0')
			{
				if (*str1 == *str2)
				{
					str2++;
					str1++;
					count1++;
				}
				else
				{
					str2++;
					str1++;
				}
				count2++;
			}
			if (count2 == count1)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	int GPS::read()
	{
		int count = 0;
		char dataIn = 0;
		while(dataIn !='$')
		{
			dataIn = UartGps.SoftUartReceiveData();
		}
		while(dataIn != ',' && count < 90)
		{
			dataIn = UartGps.SoftUartReceiveData();
			gpsData[count] = dataIn;
			count++;
		}
		count--;
		gpsData[count] = 0;
		if (cmp(gpsData,"GPRMC"))
		{
			count = 0;
			while(count < 89 && dataIn != '*')
			{
				dataIn = UartGps.SoftUartReceiveData();
				gpsData[count] = dataIn;
				count++;
			}
			gpsData[count] = 0;
		}
		else
		{
			return 0;
		}
		return 1;
	}
	int GPS::readGps()
	{
		for (char i = 0; i <= 30; i++)
		{
			if (read())
			{
				return 1;
			}
		}
		return 0;
	}
	int GPS::aountOfNumberTillThePoint(char part)
	{
		char counter = 0;
		int location = getPart(part);
		while(gpsData[location] != '.' && location < 90)
		{
			counter++;
			location++;
		}
		return counter;
	}
	int GPS::sizeOfChrechterInPart(char part)
	{
		char counter = 0;
		int location = getPart(part);
		
		while(gpsData[location] != ',' && location < 90)
		{
			counter++;
			location++;
		}
		return counter;
	}
	unsigned long int GPS::degCalculator(char min, unsigned long int sec)
	{
		unsigned long int divNum = 100;
		while (sec > divNum)
		{
			divNum *= 10;
		}
		double calculate = sec;
		unsigned long int result = 0;
		calculate /= divNum;
		calculate += min;
		calculate /= 60;
		calculate *= 10000000;
		result = calculate;
		//UartGps.printDecimalNumInAscii(result);
		return result;
	}
	char GPS::gpsSignal()
	{
		int index = getPart(1);
		if (gpsData[index] == 'V')
		{
			//UartGps.UARTstring("No GPS signal\n");
			return 0;
		}
		else
		{
			return 1;
		}
	}
	void GPS::getLongitude()
	{
		int count = 0;
		int deg = 0, min = 0;
		unsigned long int sec = 0;
		
		count = getPart(4);
		char partSize = sizeOfChrechterInPart(4);
		char sizeToPoint = aountOfNumberTillThePoint(4);
		for (int i = count; i < (sizeToPoint + count - 2) && i < 90; i++)
		{
			deg *= 10;
			deg += gpsData[i] - '0';
		}
		_deglongitude = deg;
		for (int i = (count + (sizeToPoint - 2)); i < (sizeToPoint + count) && i < 90; i++)
		{
			min *= 10;
			min += gpsData[i] - '0';
		}
		for (int i = (count + sizeToPoint +1); i < (partSize + count)&&(sec<100000); i++)
		{
			sec *= 10;
			sec += gpsData[i] - '0';
		}
		unsigned long int passPointDeg = degCalculator(min,sec);
		_longitude = passPointDeg;
		longitude[11] = 0;
		for (int i = 10; i > 3 && i < 90; i--)
		{
			longitude[i] = (passPointDeg % 10) + '0';
			passPointDeg/=10;
		}
		longitude[3] = '.';
		for (int i = 2; i >= 0 && i < 90; i--)
		{
			longitude[i] = (deg % 10) + '0';
			deg/=10;
		}
	}
	void GPS::getLatitude()
	{
		int count = 0;
		int deg = 0, min = 0;
		unsigned long int sec = 0;
		
		count = getPart(2);
		char partSize = sizeOfChrechterInPart(2);
		char sizeToPoint = aountOfNumberTillThePoint(2);
		for (int i = count; i < (sizeToPoint + count - 2) && i < 90; i++)
		{
			deg *= 10;
			deg += gpsData[i] - '0';
		}
		_degLatitude = deg;
		for (int i = (count + (sizeToPoint - 2)); i < (sizeToPoint + count) && i < 90; i++)
		{
			min *= 10;
			min += gpsData[i] - '0';
		}
		for (int i = (count + sizeToPoint +1); i < (partSize + count)&&(sec<100000) && i < 90; i++)
		{
			sec *= 10;
			sec += gpsData[i] - '0';
		}
		unsigned long int passPointDeg = degCalculator(min,sec);
		_latitude = passPointDeg;
		latitude[11] = 0;
		for (int i = 10; i > 3 && i < 90; i--)
		{
			latitude[i] = (passPointDeg % 10) + '0';
			passPointDeg/=10;
		}
		latitude[3] = '.';
		for (int i = 2; i >= 0 && i < 90; i--)
		{
			latitude[i] = (deg % 10) + '0';
			deg/=10;
		}
	}
	void GPS::gpsSpeed()
	{
		int index = getPart(6);
		double speedInKnot = 0;
		int speedInKph = 0;
		char speedCharecterSize = 1;
		char sizeToPoint = aountOfNumberTillThePoint(6);
		for (int i = index; i < (sizeToPoint + index) && i < 90; i++)
		{
			speedInKnot *= 10;
			speedInKnot += gpsData[i] - '0';
		}
		speedInKnot *= 1.85;
		_speedInKph = speedInKph = speedInKnot;
		
		while(speedInKph>pow(10,(double)speedCharecterSize))
		{
			speedCharecterSize++;
		}
		
		speed[(int)speedCharecterSize] = 0;
		
		while(speedCharecterSize != 0)
		{
			speedCharecterSize--;
			speed[(int)speedCharecterSize] = speedInKph % 10 +'0';
			speedInKph /= 10;
		}
	}
	char* GPS::getLongitudeAndLatitude()
	{
		if (!readGps())
		{
			return 0;
		}
		else if(!gpsSignal())
		{
			return 0;
		}
		getLongitude();
		getLatitude();
		gpsSpeed();
		
		strcpy(latitudeLongitude,latitude);
		latitudeLongitude[strlen(latitude)] = ',';
		strcpy(latitudeLongitude+strlen(latitude)+1,longitude);
		return latitudeLongitude;
	}
	char* GPS::getTime()
	{
		int hour = 0;
		if (readGps())
		{
			for (int i = 0; i < 2; i++)
			{
				hour *= 10;
				hour += gpsData[i] - '0';
			}
			if (hour == 22)
			{
				hour = 0;
			}
			else if (hour == 23)
			{
				hour = 1;
			}
			time[0] = hour/10 + '0';
			time[1] = hour%10 + '0';
			time[2] = ':';
			time[3] = gpsData[2];
			time[4] = gpsData[3];
			time[5] = ':';
			time[6] = gpsData[4];
			time[7] = gpsData[5];
			time[8] = 0;
		}
		return time;
	}
	char* GPS::getSpeed()
	{
		if (!readGps())
		{
			return 0;
		}
		else if(!gpsSignal())
		{
			return 0;
		}
		return speed;
	}
	int GPS::getDegLatit()
	{
		return _degLatitude;
	}
	int GPS::getDegLongit()
	{
		return _deglongitude;
	}
	unsigned long int GPS::getLatit()
	{
		return _latitude;
	}
	unsigned long int GPS::getLongit()
	{
		return _longitude;
	}
	int GPS::getSpeedKph()
	{
		return _speedInKph;
	}
