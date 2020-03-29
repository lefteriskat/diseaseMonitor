//MyDate.cpp
#include "MyDate.h"
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

MyDate::MyDate(char* date) {
	strncpy(dateStr, date, 11);
	dateStr[10] = '\0';
	dateNum = charDateToLong();
}

MyDate::~MyDate() {
	return;
}

char* MyDate::getDateStr() {
	return dateStr;
}

long  MyDate::getDateNum() {
	return dateNum;
}

long MyDate::charDateToLong() {
	long sum = 0L;
	char tmpDate[11];
	strcpy(tmpDate, dateStr);
	//splitting date to day month year
	char* ddmmyy = strtok(tmpDate,"-");
	int i = 0;
	while (ddmmyy != NULL){
		switch (i){
			case 0:
				sum += atoi(ddmmyy) * 1L; //day
				break;
			case 1:
				sum += atoi(ddmmyy) * 1000L; //month
				break;
			case 2:
				sum += atoi(ddmmyy) * 1000000L; //year
				break;
			default: 
				cout << "Error on reading date" << endl;
		}
		i++;
		ddmmyy = strtok(NULL, "- \n");
	}
	return sum;
}

bool MyDate::operator <(const MyDate& date2) {

 if(dateNum < date2.dateNum)
    return true;

 return false;
}

bool MyDate::operator >(const MyDate& date2) {
 if(dateNum > date2.dateNum)
    return true;

 return false;
}

bool MyDate::operator <=(const MyDate& date2) {

 if(dateNum <= date2.dateNum)
    return true;

 return false;
}

bool MyDate::operator >=(const MyDate& date2) {

 if(dateNum >= date2.dateNum)
    return true;

 return false;
}