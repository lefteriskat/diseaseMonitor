//DiseaseMonitor.h
#ifndef DISEASE_MONITOR_H
#define DISEASE_MONITOR_H

#include "MyBST.h"
#include "PatientRecord.h"
#include "MyDate.h"
#include "DCHashTable.h"

#define MAX_NUMBER_OF_ARGUMENTS 8
#define MAX_SIZE_OF_ARGUMENT 128

class DiseaseMonitor {
	char patientRecordsFile[256];
	unsigned int diseaseHashTableNumOfEntries;
	unsigned int countryHashTableNumOfEntries;
	unsigned int bucketSize;

	DCHashTable* diseaseHashTable;
	DCHashTable* countryHashTable;

public:

	DiseaseMonitor();
	~DiseaseMonitor();
	bool readArguments(int argc, char* argv[]);
	bool readPatientRecordsFile();
	void splitInput(char* input, char** arguments,int& numOfArguments);
	void clearArguments(char** arguments);
	void readUserInput();
	bool insertPatientRecord(PatientRecord* patientRecord);
	bool insertPatientRecord(int recordID, char* patientsFirstName, char* patientsLastName,
		                    char* diseaseID, char* country, char* entryDate, char* exitDate);
	void recordPatientExit(int recordID, char* exitDate);
	void numCurrentPatients( char* disease);
	void globalDiseaseStats(char* date1, char* date2);
	void diseaseFrequency(char* virusName, char* country, char* date1, char* date2);
	void topkDiseases(char* country, int k, char* date1, char* date2);
	void topkCountries(char* disease, int k, char* date1, char* date2);
	void exit();



};

#endif