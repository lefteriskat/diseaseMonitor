//MyBST.h
#ifndef MY_BST_H
#define MY_BST_H

#include "PatientRecord.h"
#include "MyDate.h"
#include "TopkArrayList.h"

extern bool global_DataDeleted;
class MyBSTNode {
	PatientRecord* record;
	MyBSTNode* right;
	MyBSTNode* left;
public:
	MyBSTNode(PatientRecord* record);
	~MyBSTNode();
	friend class MyBST;
};


class MyBST{

	MyBSTNode* root;
	int numOfRecords;
	bool recursiveFindRecord(PatientRecord* record, MyBSTNode* currNode);
	void recursiveAddRecord(PatientRecord* record, MyBSTNode** currNode);
	int recursiveNumCurrentPatients(MyBSTNode* currNode);
	PatientRecord* recursiveFindRecord(int recordID, MyBSTNode* currNode);
public:
	MyBST();
	~MyBST();
	bool addRecord(PatientRecord* record);
	bool findRecord(PatientRecord* record);
	int globalDiseaseStats(char* date1, char* date2);
	int diseaseFrequency(char* date1, char* date2, char* country);
	int traverse(MyBSTNode* currNode, MyDate& date1, MyDate& date2, char* country);
	int numCurrentPatients();
	bool recordPatientExit(int recordID, char* exitDate);
	void topk(char* date1, char* date2, int k, int mode);
	void topkTraverse(MyBSTNode* currNode,TopkArrayList* topkArrayList, MyDate* date1, MyDate* date2, int mode);
};

#endif