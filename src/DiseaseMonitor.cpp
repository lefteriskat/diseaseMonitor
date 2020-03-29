//DiseaseMonitor.cpp

#include "DiseaseMonitor.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;

unsigned int global_BucketSize;
bool global_DataDeleted;

DiseaseMonitor::DiseaseMonitor() {
	patientRecordsFile[0] = '\0';
	diseaseHashTableNumOfEntries = 0;
	countryHashTableNumOfEntries = 0;
	bucketSize = 0;

	diseaseHashTable = NULL;
	countryHashTable = NULL;

	global_BucketSize = 0;
	global_DataDeleted = false;
}

DiseaseMonitor::~DiseaseMonitor() {
	cout << "Deleting DiseaseMonitor1!" << endl;
	if( diseaseHashTable != NULL )
		delete diseaseHashTable;
	global_DataDeleted = true;
	if( countryHashTable != NULL )
		delete countryHashTable;
	cout << "Deleting DiseaseMonitor2!" << endl;
}

bool DiseaseMonitor::readArguments(int argc, char* argv[]) {
	if(argc != 9){
		cerr << "Number of arguments is Invalid!" << endl;
		return false;
	}
	else {
		for(int i=1;i <= 7; i+=2){
			if( strcmp("-p", argv[i]) == 0) {
				//bitCoinBalancesFile
				strncpy(patientRecordsFile, argv[i+1], 256);
			}
			else if(strcmp("-h1", argv[i]) == 0){
				//senderEntries
				diseaseHashTableNumOfEntries = (unsigned int) atoi(argv[i+1]);
			}
			else if(strcmp("-h2", argv[i]) == 0){
				//receiverEntries
				countryHashTableNumOfEntries = (unsigned int) atoi(argv[i+1]);
			}
			else if(strcmp("-b", argv[i]) ==0){
				//BucketSize
				bucketSize = (unsigned int) atoi(argv[i+1]);
				global_BucketSize = bucketSize;
			}
			else{
				cerr << "Invalid Argument!" << endl;
				return false;
			}
		}
	}

	diseaseHashTable = new DCHashTable(diseaseHashTableNumOfEntries);
	countryHashTable = new DCHashTable(countryHashTableNumOfEntries);
	if (!diseaseHashTable || !countryHashTable) {
		cerr << "Could not allocate memory! Exiting . . ." << endl;
		return false;
	}

	return true;
}

bool DiseaseMonitor::readPatientRecordsFile() {

	ifstream in(patientRecordsFile);
	if(!in) {
		cerr << "Cannot open input file.\n";
		return false;
	}
	unsigned int maxLineSize = MAX_NUMBER_OF_ARGUMENTS * MAX_SIZE_OF_ARGUMENT;
	char line[maxLineSize];
	char** arguments = new char* [MAX_NUMBER_OF_ARGUMENTS];
	for( int i = 0; i < MAX_NUMBER_OF_ARGUMENTS; i++) {
		arguments[i] = new char [MAX_SIZE_OF_ARGUMENT];
	}
	int numOfArguments = 0;
	while( in ) {
		in.getline(line, maxLineSize);
		
		clearArguments((char**) arguments);
		splitInput(line, (char**) arguments, numOfArguments);
		if( numOfArguments != 7 ) {
			continue;
		}

		if( !insertPatientRecord( atoi(arguments[0]), arguments[1], arguments[2], arguments[3],
										  arguments[4], arguments[5], arguments[6] ) ) {


			for( int i = 0; i < MAX_NUMBER_OF_ARGUMENTS; i++) {
				delete [] arguments[i];
			}
			delete [] arguments;
			in.close();
			return false;
		}
	}



	for( int i = 0; i < MAX_NUMBER_OF_ARGUMENTS; i++) {
		delete [] arguments[i];
	}
	delete [] arguments;
	in.close();
	return true;
}

void DiseaseMonitor::splitInput(char* input, char** arguments,int& numOfArguments) {
	int j=0; 
	numOfArguments = 0;
    for(int i=0; i <= (strlen(input)) && numOfArguments < MAX_NUMBER_OF_ARGUMENTS ; i++)
    {
        // if space or NULL found, assign NULL into splitStrings[count]
        if(input[i] == ' ' || input[i] == '\0' || input[i] == '\n')
        {
            arguments[numOfArguments][j]='\0';
            numOfArguments++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
        	if( j < MAX_SIZE_OF_ARGUMENT-1)
            	arguments[numOfArguments][j++]=input[i];
        }
    }
}

void DiseaseMonitor::clearArguments(char** arguments) {
	for( int i = 0; i < MAX_NUMBER_OF_ARGUMENTS; i++) {
		arguments[i][0] = '\0';
	}
}

void DiseaseMonitor::readUserInput() {
	unsigned int maxLineSize = MAX_NUMBER_OF_ARGUMENTS * MAX_SIZE_OF_ARGUMENT;
	char line[maxLineSize];
	char** arguments = new char* [MAX_NUMBER_OF_ARGUMENTS];
	for( int i = 0; i < MAX_NUMBER_OF_ARGUMENTS; i++) {
		arguments[i] = new char [MAX_SIZE_OF_ARGUMENT];
	}
	int numOfArguments = 0;

	while( 1 ) {
		cin.getline(line, maxLineSize);
		
		clearArguments((char**) arguments);
		splitInput(line, (char**) arguments, numOfArguments);
		if( numOfArguments > 8 || numOfArguments < 1) {
			cerr << "Invalid input" << endl;
			return ;
		}

		if( !strcmp(arguments[0], "/exit")) {
			break;
		} 
		else if ( !strcmp(arguments[0], "/globalDiseaseStats") ) {
			if( numOfArguments == 3)
				globalDiseaseStats(arguments[1], arguments[2]);
			else if( numOfArguments == 1 )
				globalDiseaseStats(NULL, NULL);
			else 
				cout << "error" << endl;
		} 
		else if ( !strcmp(arguments[0], "/diseaseFrequency") ) {
			if( numOfArguments == 4)
				diseaseFrequency( arguments[1], NULL, arguments[2], arguments[3]);
			else if ( numOfArguments == 5 )
				diseaseFrequency( arguments[1], arguments[4], arguments[2], arguments[3]);
			else
				cout << "error" << endl;
		} 
		else if ( !strcmp(arguments[0], "/insertPatientRecord") ) {
			if( numOfArguments >= 7 )
				insertPatientRecord(atoi(arguments[1]), arguments[2], arguments[3],
									arguments[4], arguments[5],arguments[6], arguments[7]);
			else
				cout << "error" << endl;

		} 
		else if ( !strcmp(arguments[0], "/recordPatientExit") ) {
			if( numOfArguments == 3 )
				recordPatientExit(atoi(arguments[1]), arguments[2]);
			else
				cout << "error" << endl;
		} 
		else if ( !strcmp(arguments[0], "/numCurrentPatients") ) {
			if( numOfArguments == 1 )
				numCurrentPatients(NULL);
			else if (numOfArguments == 2 )
				numCurrentPatients(arguments[1]);
			else
				cout << "error" << endl;
		} 
		else {
			cout << "error" << endl;
		}
	}

	for( int i = 0; i < MAX_NUMBER_OF_ARGUMENTS; i++) {
		delete [] arguments[i];
	}
	delete [] arguments;
}

bool DiseaseMonitor::insertPatientRecord(PatientRecord* patientRecord) {
	//cout << "Inserting " << patientRecord->getRecordID ()<< " into diseaseHashTable [" << patientRecord->getDiseaseID() << "]" << endl;
	bool noDuplicate = diseaseHashTable->addRecord(patientRecord->getDiseaseID(), patientRecord);
	if( noDuplicate ){
		//cout << "Inserting " << patientRecord->getRecordID ()<< " into countryHashTable [" << patientRecord->getCountry() << "]" << endl;
		return countryHashTable->addRecord(patientRecord->getCountry(), patientRecord);
	}
	else {
		cout << "error" << endl;
		return false;		   
	}
}

bool DiseaseMonitor::insertPatientRecord(int recordID, char* patientsFirstName, char* patientsLastName,
		                    char* diseaseID, char* country, char* entryDate, char* exitDate) {

	PatientRecord* tempRecord = new PatientRecord(recordID, patientsFirstName, patientsLastName,
		                                          diseaseID, country, entryDate, exitDate);
	//check for entryDate > exitDate
	if( tempRecord->getExitDate() && *(tempRecord->getEntryDate()) > *(tempRecord->getExitDate()) ) {
		cout << tempRecord->getEntryDate()->getDateStr() << " " << tempRecord->getEntryDate()->getDateNum() << endl;
		cout << tempRecord->getExitDate()->getDateStr() << " " << tempRecord->getExitDate()->getDateNum() << endl;
		delete tempRecord;
		cerr << "error" << endl;
		return true;
	}

	if( !insertPatientRecord(tempRecord) ) {
		cerr << "error" << endl;
		delete tempRecord;
		return false;
	}

	return true;
}

void DiseaseMonitor::recordPatientExit(int recordID, char* exitDate) {
	diseaseHashTable->recordPatientExit(recordID, exitDate);
}

void DiseaseMonitor::numCurrentPatients( char* disease ) {
	diseaseHashTable->numCurrentPatients(disease);
}

void DiseaseMonitor::globalDiseaseStats(char* date1, char* date2) {
	diseaseHashTable->printNumberOfRecords(NULL, date1, date2, NULL);
}

void DiseaseMonitor::diseaseFrequency(char* virusName, char* country, char* date1, char* date2) {
	diseaseHashTable->printNumberOfRecords(virusName, date1, date2, country);
}

void DiseaseMonitor::exit() {

}
