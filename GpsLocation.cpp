#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <math.h>
#include "GpsLocation.h"
#include "UART.h"
#include "Gps.h"

GPS Location;
Uart Move;
	void MovedFromLocation::updateLocation()
	{
		_degLatitude = Location.getDegLatit();
		_degLongitude = Location.getDegLongit();

		_latitude = Location.getLatit();
		_longitude = Location.getLongit();
	}
	void MovedFromLocation::storeNewData()
	{
		if (_index >= 19)
		{
			_index = 0;
		}
		locationMemory[0][_index] = _latitude;
		locationMemory[1][_index] = _longitude;
		_index++;
	}
	//set the first Average in order to compare new income location data
	char MovedFromLocation::firstAvrage()
	{
		static char firstLearning = 0;
		int arrSize = sizeof(locationMemory[0])/sizeof(unsigned long int);
		if (firstLearning)
		{
			return 1;
		}
		else
		{
			if (_index < (arrSize-1))
			{
				return 0;
			}
			_avrSum = avrageCalculator(0);
			_avrSum += avrageCalculator(1);
			_avrSum /= 2;
			firstLearning = 1;
			return 1;
		}
	}
	/********************************************************************/
	/*make average from the arr consider his size and return the average*/
	/********************************************************************/
	int MovedFromLocation::avrageCalculator(int latitude0Longetude1)
		{
			int arrSize = sizeof(locationMemory[latitude0Longetude1])/sizeof(unsigned long int);
			int sum = 0;
			int currentValue = 0;
			for (int i = 0; i < (arrSize - 1); i++)
			{
				currentValue =  locationMemory[latitude0Longetude1][i] - locationMemory[latitude0Longetude1][i+1];
				currentValue = convertNegToPositive(currentValue);
				if (currentValue < 60000)
				{
					sum += currentValue;
				}
			}
			currentValue =  locationMemory[latitude0Longetude1][0] - locationMemory[latitude0Longetude1][arrSize - 1];
			currentValue = convertNegToPositive(currentValue);
			if (currentValue < 60000)
			{
				sum += currentValue;
			}
			return (sum/(arrSize));
		}
		/**************************************************************/
		/*this function get the average of the latitude & Longitude   */
		/*from avrageCalculator(), function while latitude =0 and     */
		/*Longitude=1,and check if it is exceed from average of arr+50%*/
		/*this function return 1 if fail, 0 if OK                     */
		/**************************************************************/
	int MovedFromLocation::checkAvrageOfMovment()
	{
		int avr = 0;
		avr = avrageCalculator(0);
		avr += avrageCalculator(1);
		avr /= 2;
		_avrSum += avr;
		_avrSum /= 2;
		//Move.UARTstring("Now Average is: ");//*************************remove
		//Move.printDecimalNumInAscii(avr);
		//Move.UARTstring("\n");
		if (avr > (_avrSum + (_avrSum/2)))
		{
			return avr;                   //souled be "return 1; //return avr is just for test
		}
		else
		{
			return 0;
		}
		return 0;
	}
	int MovedFromLocation::convertNegToPositive(int negetiveOrPositive)
	{
		if (negetiveOrPositive < 0)
		{
			return negetiveOrPositive *= -1;
		}
		else
		{
			return negetiveOrPositive;
		}
	}
	/*****************************************************************************************/
	/*this function set average of 10 latitude & longitude values and keep it.               */
	/*this function check if there is a different between memory location & new location.    */
	/*                                                                                       */
	/*if one of the next fail it would send a massage of movement, and reset the value.      */
	/*1. the speed is over 70 Kph.                                                           */
	/*2. the current deg value is different from memory.                                     */
	/*3. value of latitude & longitude is different from memory+50%(tolerance) of average.   */
	/*4. if fail to succeed clause 3 more then 15 times.                                     */
	/*5. average not competed, and compare action took place.                                */
	/*****************************************************************************************/
	int MovedFromLocation::memoriesLastGoodLocationOrCheckSignalInteruption(int speed, int checkCall)
	{
		static unsigned long int latitude = 0, longitude = 0;
		static int degLatitude = 0, degLongitude = 0;
		static char indexMemory = 0, tryTimes = 0, stop = 0;
		
		//if checkCall = 1, it will compare data, else it will update data if it is not up to date
		if (checkCall)
		{
			if (speed > 70 || latitude == 0 || longitude == 0)
			{
				indexMemory = 0;
				return 1;
			}
			//Move.UARTstring("Chance number:");//*******************************remove
			//Move.printDecimalNumInAscii(tryTimes);
			//Move.UARTstring(" !/n");
			if (tryTimes <= 60)//#####################################################change to 60
			{
				//Move.UARTstring("part 1");//*****************************
				if (convertNegToPositive(_latitude - latitude) > (_avrSum + _avrSum/2) || convertNegToPositive(_longitude- longitude) > (_avrSum+_avrSum/2))
				{
					//Move.UARTstring("part 2");//***********************
					if (convertNegToPositive(degLatitude - _degLatitude) > 1 || convertNegToPositive(degLongitude - _degLongitude) > 1)
					{
						//Move.UARTstring("part 3");//*****************
						stop = 0;
						indexMemory = 0;
						latitude = 0;
						longitude = 0;
						return 1;
					}
					//Move.UARTstring("part 4");//*******************	*
					tryTimes++;
					return 0;
				}
				//Move.UARTstring("part 5");//****************************
				return 0;
			}
			stop = 0;
			indexMemory = 0;
			latitude = 0;
			longitude = 0;
			return 1;
		} 
		else
		{
			tryTimes = 0;
			
			if (stop) //if stop = 1, the data is up to date
			{
				return 0;
			}
			else if (speed <= 1)        //data will be updated only if speed is 1Kph or lower.
			{                           //other way it will start over the process
				degLatitude = _degLatitude;
				degLongitude = _degLongitude;
				if (indexMemory <= 10)
				{
					latitude += _latitude;
					longitude += _longitude;
					indexMemory++;
				}
				else
				{
					latitude /= 10;
					longitude /= 10;
					stop = 1;
					//Move.UARTstring("Compare Data is accomplished!\n");//*******************remove
					//Move.printDecimalNumInAscii(latitude);
					//Move.printDecimalNumInAscii(longitude);
				}
			}
			else
			{
				degLatitude = 0;
				degLongitude = 0;
				latitude = 0;
				longitude = 0;
				indexMemory = 0;
			}
		}
		return 0;
	}
	MovedFromLocation::MovedFromLocation()
		{
			_index =  _avrSum = 0;
			_degLongitude = _degLatitude = 0;
			_longitude = _latitude = 0;
		}
	char* MovedFromLocation::getLongitudeAndLatitude()
	{
		return Location.getLongitudeAndLatitude();
	}
	char* MovedFromLocation::getGoogleMapsLink()
	{
		char arr[80];
	    strcpy(arr,"www.google.co.il/maps/place/");
		strcpy(arr+strlen(arr),getLongitudeAndLatitude());
		strcpy(_locationData+50,arr);
	    return _locationData+50;
	}
    /********************************************************************************/
    /*this function check if there is a movement by setting an average of a location*/
    /*and checking if there is a difference between the arr average and the location*/
    /*that just received.                                                           */
    /*it is checking if the speed of GPS is bigger then 2 Kph, if so it will        */
    /*compare the current location with the memory stored location.                 */
    /********************************************************************************/
    //return 1 for car moving, 0 if it is not moving
	char MovedFromLocation::checkIfMoved()
	{
		int speed = 0, average = 0; 
		//check if there is any data or maybe there is no signal. NULL = no data
		if (Location.getLongitudeAndLatitude())
		{
		    
			speed = Location.getSpeedKph();
			if (speed > 2)
			{
				//checking if the location that stored in the memory is the same one from 
				//the "Location.getLongitudeAndLatitude()", if not, you have 15 chances to 
				//pull it together! other way, a movement massage will be sent.
				return memoriesLastGoodLocationOrCheckSignalInteruption(speed,1);
			}
			updateLocation(); //updating the new "Location.getLongitudeAndLatitude()" data
			storeNewData();    //move the new value into the average arr
	
			//before any data is saved, we are calculating the first average witch is the arr
			if (firstAvrage())
			{
				average = checkAvrageOfMovment(); //temporary, just for test. 
			}
			if(average)			//original = if(checkAvrageOfMovment())	
			{
				//Move.UARTstring("Check Average Problem... ");
				return memoriesLastGoodLocationOrCheckSignalInteruption(speed,1);
			}
			else
			{
				memoriesLastGoodLocationOrCheckSignalInteruption(speed);
				return 0;
			}
		
		}
		return 0;
	}