//PatientRecord.h
#ifndef PATIENT_RECORD_H
#define PATIENT_RECORD_H

#include "MyDate.h"
#define MAX_NAME_LEN 128

class PatientRecord
{
	int recordID;
	char patientsFirstName[MAX_NAME_LEN];
	char patientsLastName[MAX_NAME_LEN];
	char diseaseID[MAX_NAME_LEN];
	char country[MAX_NAME_LEN];
	MyDate* entryDate;
	MyDate* exitDate;

public:
	PatientRecord(int recordID, char* patientsFirstName, char* patientsLastName,
		          char* diseaseID, char* country, char* entryDate, char* exitDate);
	~PatientRecord();
	int getRecordID();
	char* getPatientsFirstName();
	char* getPatientsLastName();
	char* getDiseaseID();
	char* getCountry();
	MyDate* getEntryDate();
	MyDate* getExitDate();
};

#endif