//DCHashTable.h
#ifndef MY_BST_H
#define MY_BST_H

#include "MyBST.h"

extern int global_BucketSize;

class DCHashTableEntry {
	char key[MAX_NAME_LEN];
	MyBST* records;

public:
	DCHashTableEntry(char* key);
	~DCHashTableEntry();
	MyBST* getRecords();
	char* getKey();
	void setKey(char* key);
	bool equals(char* key);
    bool addRecord(PatientRecord* patientRecord);
    void printNumberOfRecords(char* date1, char* date2, char* country);
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
	bool addRecord(char* key, PatientRecord* patientRecord);
	void addEntry(char* key);
	bool isFull();
	void printNumberOfRecords(char* date1, char* date2, char* country);
};

class DCHashTableBucketList {
	DCHashTableBucket* firstNode;
	int numOfNodes;
public:
	DCHashTableBucketList();
	~DCHashTableBucketList();
	void addEntry(char* key);
	DCHashTableEntry* findEntry(char* key);
	bool addRecord(char* key, PatientRecord* patientRecord);
	void printNumberOfRecords(char* key,char* date1, char* date2, char* country);
}

class DCHashTable {
	DCHashTableBucketList* dcHashTable;
	unsigned int numOfEntries;
public:
	DCHashTable(int numOfEntries);
	~DCHashTable();
	bool addRecord(char* key, patientRecord* record);
	DCHashTableEntry* findEntry();
	void addEntry(char* key);
	void printNumberOfRecords(char* key,char* date1, char* date2, char* country);
	int hashFunction(char* key);
};


#endif