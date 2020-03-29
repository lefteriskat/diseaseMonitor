//MyDate.h
#ifndef MY_DATE_H
#define MY_DATE_H

class MyDate
{
	long dateNum;
	char dateStr[11];
	long charDateToLong();

public:
	MyDate(char* date);
	~MyDate();
	char* getDateStr();
	long  getDateNum();
	bool operator <(const MyDate& date2);
	bool operator >(const MyDate& date2);
	bool operator <=(const MyDate& date2);
	bool operator >=(const MyDate& date2);
};

#endif
