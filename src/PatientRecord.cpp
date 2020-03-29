//PatientRecord.cpp

#include "PatientRecord.h"
#include <cstring>
#include <iostream>

using namespace std;

PatientRecord::PatientRecord(int recordID, char* patientsFirstName, char* patientsLastName,
		                    char* diseaseID, char* country, char* entryDate, char* exitDate) {

this->recordID = recordID;

if( patientsFirstName != NULL ) {
	strncpy(this->patientsFirstName, patientsFirstName, MAX_NAME_LEN);
	patientsFirstName[MAX_NAME_LEN-1] = '\0';
}
if( patientsLastName != NULL ) {
	strncpy(this->patientsLastName, patientsLastName, MAX_NAME_LEN);
	patientsLastName[MAX_NAME_LEN-1] = '\0';
}
if( diseaseID != NULL ) {
	strncpy(this->diseaseID, diseaseID, MAX_NAME_LEN);
	diseaseID[MAX_NAME_LEN-1] = '\0';
}
if( country != NULL ) {
	strncpy(this->country, country, MAX_NAME_LEN);
	country[MAX_NAME_LEN-1] = '\0';
}

this->entryDate = new MyDate(entryDate);

if( strlen(exitDate) >= 8) {
	this->exitDate = new MyDate(exitDate);
}
else {
	this->exitDate = NULL;
}

}

PatientRecord::~PatientRecord() {
	delete entryDate;
	if( exitDate != NULL )
		delete exitDate;
}
int PatientRecord::getRecordID() {
	return recordID;
}
char* PatientRecord::getPatientsFirstName() {
	return patientsFirstName;
}
char* PatientRecord::getPatientsLastName() {
	return patientsLastName;
}
char* PatientRecord::getDiseaseID() {
	return diseaseID;
}
char* PatientRecord::getCountry() {
	return country;
}
MyDate* PatientRecord::getEntryDate() {
	return entryDate;
}
MyDate* PatientRecord::getExitDate() {
	return exitDate;
}
bool PatientRecord::setExitDate(char* exitDate) {
	if( (this->exitDate == NULL) && strlen(exitDate) >= 8) {
		this->exitDate = new MyDate(exitDate);
		cout << "Record updated" << endl;
		return true;
	}
	else {
		if (this->exitDate) {
			cout << "This record has already an Exit Date." << endl;
		} else {
			cout << "error" << endl;
		}
		return false;
	}
}