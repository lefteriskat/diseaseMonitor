//MyBST.h
#ifndef MY_BST_H
#define MY_BST_H

#include "PatientRecord.h"
#include "MyDate.h"

extern bool global_DataDeleted;
class MyBSTNode {
	PatientRecord* record;
	MyBSTNode* right;
	MyBSTNode* left;

public:
	MyBSTNode(PatientRecord* record);
	~MyBSTNode();
};


class MyBST {

	MyBSTEntry* root;
	int numOfRecords;

public:
	MyBST();
	~MyBST();
	bool addRecord(PatientRecord* record);
	bool findRecord(PatientRecord* record);
	int globalDiseaseStats(char* date1, char* date2);
	int diseaseFrequency(char* date1, char* date2, char* country);
	int numCurrentPatients();
};

#endif