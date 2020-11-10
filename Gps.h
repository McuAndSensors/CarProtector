
#ifndef GPS_H_
#define GPS_H_
class GPS
{
	private:
	char gpsData[90];
	char time[9];
	char speed[4];
	char latitude[14];
	char longitude[14];
	char latitudeLongitude[25];
	int _speedInKph, _degLatitude, _deglongitude;
	unsigned long int _longitude, _latitude;
	int getPart(char part);
	int cmp(char *str1, const char *str2);
	int read();
	int readGps();
	int aountOfNumberTillThePoint(char part);
	int sizeOfChrechterInPart(char part);
	unsigned long int degCalculator(char min, unsigned long int sec);
	char gpsSignal();
	void getLongitude();
	void getLatitude();
	void gpsSpeed();
	public:
	char *getLongitudeAndLatitude();
	char *getTime();
	char *getSpeed();
	int getDegLatit();
	int getDegLongit();
	unsigned long int getLatit();
	unsigned long int getLongit();
	int getSpeedKph();
};


#endif /* GPS_H_ */