//DCHashTable.cpp
#include "DCHashTable.h"
#include <cstring>
#include <iostream>

using namespace std;
/******************** DCHashTableEntry **********************/
DCHashTableEntry::DCHashTableEntry() {
	key[0] = '\0';
	records = new MyBST(); 
}
DCHashTableEntry::DCHashTableEntry(char* key) {
	if( key != NULL ) {
		strncpy(this->key, key, MAX_NAME_LEN);
		key[MAX_NAME_LEN-1] = '\0';
	}
	records = new MyBST();
}

DCHashTableEntry::~DCHashTableEntry() {
	delete records;
}

MyBST* DCHashTableEntry::getRecords() {
	return records;
}

char* DCHashTableEntry::getKey() {
	return key;
}

void DCHashTableEntry::setKey(char* key) {
	if( key != NULL ) {
		strncpy(this->key, key, MAX_NAME_LEN);
		key[MAX_NAME_LEN-1] = '\0';
	}
}

bool DCHashTableEntry::equals(char* key) {
	return !strncmp(this->key, key, MAX_NAME_LEN);
}

bool DCHashTableEntry::addRecord(PatientRecord* patientRecord) {
	return records->addRecord(patientRecord);
}
void DCHashTableEntry::printNumberOfRecords(char* date1, char* date2, char* country) {
	int numOfRecords = records->diseaseFrequency(date1, date2, country);
	cout << key << " " << numOfRecords << endl;
}

void DCHashTableEntry::numCurrentPatients() {
	int currPatients = records->numCurrentPatients();
	cout << key << " " << currPatients << endl;
}
bool DCHashTableEntry::recordPatientExit(int recordID, char* exitDate) {
	bool success = records->recordPatientExit(recordID, exitDate);
}
/***********************************************************/

/******************* DCHashTableBucket *********************/
DCHashTableBucket::DCHashTableBucket() {
	maxEntries = global_BucketSize / sizeof(DCHashTableEntry);
	if (maxEntries == 0) maxEntries = 1;
	numOfEntries = 0;
	next = NULL;
	entries = new DCHashTableEntry[maxEntries];
}
DCHashTableBucket::~DCHashTableBucket() {
	if ( next != NULL ) {
		delete next;
		next = NULL;
	}

	delete[] entries;
}
DCHashTableEntry* DCHashTableBucket::findEntry(char* key) {
	for (int i = 0; i < numOfEntries; i++ ){
		if ( entries[i].equals(key))
			return &entries[i];
	}
	return NULL;
}
DCHashTableEntry* DCHashTableBucket::addEntry(char* key) {
	entries[numOfEntries++].setKey(key);
	return &(entries[numOfEntries-1]);
}
bool DCHashTableBucket::isFull() {
	return (numOfEntries == maxEntries);
}
void DCHashTableBucket::printNumberOfRecords(char* date1, char* date2, char* country) {
	for( int i = 0; i < numOfEntries; i++) {
		entries[i].printNumberOfRecords(date1, date2, country);
	}
}
void DCHashTableBucket::numCurrentPatients() {
	for( int i = 0; i < numOfEntries; i++) {
		entries[i].numCurrentPatients();
	}
}
bool DCHashTableBucket::recordPatientExit(int recordID, char* exitDate) {
	for( int i = 0; i < numOfEntries; i++) {
		if (entries[i].recordPatientExit(recordID, exitDate))
			return true;
	}
	return false;
}
/***********************************************************/

/***************** DCHashTableBucketList *******************/
DCHashTableBucketList::DCHashTableBucketList() {
	firstNode = NULL;
	numOfNodes = 0;
}
DCHashTableBucketList::~DCHashTableBucketList() {
	if( firstNode != NULL )
		delete firstNode;
}
DCHashTableEntry* DCHashTableBucketList::addEntry(char* key) {
	DCHashTableBucket** currNode = &firstNode;
	while ( (*currNode) != NULL && (*currNode)->isFull() ) {
		currNode = &((*currNode)->next);
	}
	if ( (*currNode) == NULL) {
		(*currNode) = new DCHashTableBucket();
		numOfNodes++;
	}
	return (*currNode)->addEntry(key);
}
DCHashTableEntry* DCHashTableBucketList::findEntry(char* key) {
	DCHashTableBucket* currNode = firstNode;
	DCHashTableEntry* entry = NULL;
	while ( currNode != NULL ) {
		entry = currNode->findEntry(key);
		if( entry != NULL )
			break;
		currNode = currNode->next;
	}
	return entry;
}
bool DCHashTableBucketList::addRecord(char* key,
                                      PatientRecord* patientRecord) {
	DCHashTableEntry* entry = findEntry(key);
	if ( entry == NULL ) {
		entry = addEntry(key);
	}
	return entry->addRecord(patientRecord);
}
void DCHashTableBucketList::printNumberOfRecords(char* key,char* date1, char* date2, char* country) {
	if( key != NULL ) {
		DCHashTableEntry* entry = findEntry(key);
		if ( entry != NULL )
			entry->printNumberOfRecords(date1, date2, country);
		else
			cout << key << " 0" << endl; 
	} else {

		DCHashTableBucket* currNode = firstNode;
		while ( currNode != NULL ) {
			currNode->printNumberOfRecords(date1, date2, country);
			currNode = currNode->next;
		}
	}
}
void DCHashTableBucketList::numCurrentPatients(char* key) {
	if( key != NULL ) {
		DCHashTableEntry* entry = findEntry(key);
		if ( entry != NULL )
			entry->numCurrentPatients();
		else
			cout << key << " 0" << endl; 
	} else {

		DCHashTableBucket* currNode = firstNode;
		while ( currNode != NULL ) {
			currNode->numCurrentPatients();
			currNode = currNode->next;
		}
	}
}
bool DCHashTableBucketList::recordPatientExit(int recordID, char* exitDate) {
	DCHashTableBucket* currNode = firstNode;
	while ( currNode != NULL ) {
		if (currNode->recordPatientExit(recordID, exitDate))
			return true;
		currNode = currNode->next;
	}
	return false;
}
/***********************************************************/

/***********************************************************/
DCHashTable::DCHashTable(unsigned int numOfEntries) {
	this->numOfEntries = numOfEntries;
	dcHashTable = new DCHashTableBucketList[numOfEntries];
}
DCHashTable::~DCHashTable() {
	delete [] dcHashTable;
}
bool DCHashTable::addRecord(char* key, PatientRecord* record) {
	unsigned int index = hashFunction(key);
	return dcHashTable[index].addRecord(key, record);
}
void DCHashTable::printNumberOfRecords(char* key,char* date1, char* date2, char* country) {
	if( key != NULL ) {
		unsigned int index = hashFunction(key);
	    dcHashTable[index].printNumberOfRecords(key, date1, date2, country);
	}
	else {
		for( unsigned int i = 0 ; i < numOfEntries; i++ ) {
			dcHashTable[i].printNumberOfRecords(key, date1, date2, country);
		}
	}
}
void DCHashTable::numCurrentPatients(char* key) {
	if( key != NULL ) {
		unsigned int index = hashFunction(key);
	    dcHashTable[index].numCurrentPatients(key);
	}
	else {
		for( unsigned int i = 0 ; i < numOfEntries; i++ ) {
			dcHashTable[i].numCurrentPatients(key);
		}
	}
}

bool DCHashTable::recordPatientExit(int recordID, char* exitDate) {
	for( unsigned int i = 0 ; i < numOfEntries; i++ ) {
		if (dcHashTable[i].recordPatientExit(recordID, exitDate))
			return true;
	}
	//cout << "No record with recordID = " << recordID << "." <<endl;
	cout << "error" << endl;
	return false;
}

unsigned int DCHashTable::hashFunction(const char* key) {
	unsigned int hash = 1315423911;

	for(size_t i = 0; i < strlen(key); i++) {
		hash ^= ((hash << 5) + key[i] + (hash >> 2));
	}
	return (hash & 0x7FFFFFFF) % numOfEntries;
}

/***********************************************************/