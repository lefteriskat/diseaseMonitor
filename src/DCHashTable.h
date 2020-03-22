//DCHashTable.h
#ifndef DC_HASHTABLE_H
#define DC_HASHTABLE_H

#include "MyBST.h"
#include "PatientRecord.h"

extern unsigned int global_BucketSize;

class DCHashTableEntry {
	char key[MAX_NAME_LEN];
	MyBST* records;

public:
	DCHashTableEntry();
	DCHashTableEntry(char* key);
	~DCHashTableEntry();
	MyBST* getRecords();
	char* getKey();
	void setKey(char* key);
	bool equals(char* key);
    bool addRecord(PatientRecord* patientRecord);
    void printNumberOfRecords(char* date1, char* date2, char* country);
    void numCurrentPatients();
};

class DCHashTableBucket {
	DCHashTableEntry* entries;
	int numOfEntries;
	int maxEntries;
	DCHashTableBucket* next;

public:
	DCHashTableBucket();
	~DCHashTableBucket();
	DCHashTableEntry* findEntry(char* key);
	DCHashTableEntry* addEntry(char* key);
	bool addRecord(char* key, PatientRecord* patientRecord);
	bool isFull();
	void printNumberOfRecords(char* date1, char* date2, char* country);
	void numCurrentPatients();

	friend class DCHashTableBucketList;
};

class DCHashTableBucketList {
	DCHashTableBucket* firstNode;
	int numOfNodes;
public:
	DCHashTableBucketList();
	~DCHashTableBucketList();
	DCHashTableEntry* addEntry(char* key);
	DCHashTableEntry* findEntry(char* key);
	bool addRecord(char* key, PatientRecord* patientRecord);
	void printNumberOfRecords(char* key,char* date1, char* date2, char* country);
	void numCurrentPatients(char* key);
};

class DCHashTable {
	DCHashTableBucketList* dcHashTable;
	unsigned int numOfEntries;
public:
	DCHashTable(unsigned int numOfEntries);
	~DCHashTable();
	bool addRecord(char* key, PatientRecord* record);
	DCHashTableEntry* findEntry();
	void addEntry(char* key);
	void printNumberOfRecords(char* key,char* date1, char* date2, char* country);
	void numCurrentPatients(char* key);
	unsigned int hashFunction(const char* key);
};


#endif