
#ifndef GPSLOCATION_H_
#define GPSLOCATION_H_

class MovedFromLocation
{
	private:
	char _locationData[200];
	unsigned long int _longitude, _latitude;
	int _degLongitude, _degLatitude;
	int _index, _indexReset;
	unsigned long int locationMemory[2][19];
	int _avrSum, _minDeviation;
	void updateLocation();
	char firstAvrage();
	void storeNewData();
	int avrageCalculator(int latitude0Longetude1);
	int checkAvrageOfMovment();
	int convertNegToPositive(int negetiveOrPositive);
	int memoriesLastGoodLocationOrCheckSignalInteruption(int speed = 1, int checkCall = 0);
	public:
	MovedFromLocation();
	char *getLongitudeAndLatitude();
	char *getGoogleMapsLink();
	char checkIfMoved();
};

#endif /* GPSLOCATION_H_ */