//MyBST.cpp
#include "myBST.h"
#include <cstring>
#include <iostream>

using namespace std;
/*********************** MyBSTNode *************************/

MyBSTNode::MyBSTNode(PatientRecord* record) {
	this->record = record;
	left  = NULL;
	right = NULL;
}

//poly pi8ano na paei sto tree
MyBSTNode::~MyBSTNode() {
	if( left != NULL )
		delete left;
	if ( right != NULL )
		delete right;
	if( !global_DataDeleted && record != NULL) {
		delete record;
	}
}

/***********************************************************/

/************************* MyBST ***************************/

MyBST::MyBST() {
	root = NULL;
	numOfRecords = 0;
}

MyBST::~MyBST() {
	if( root != NULL )
		delete root;
}
bool MyBST::addRecord(PatientRecord* record) {
	if( findRecord(record) ){
		return false;
	}
	recursiveAddRecord(record, &root);
	return true;
}

void MyBST::recursiveAddRecord(PatientRecord* record, MyBSTNode** currNode) {

	if( (*currNode) == NULL ) {
		(*currNode) = new MyBSTNode(record);
		numOfRecords++;
		return;
	}

	if( (*(record->getEntryDate())) <= (*((*currNode)->record->getEntryDate())) ) {
		recursiveAddRecord(record, &((*currNode)->left));
	} else {
		recursiveAddRecord(record, &((*currNode)->right));
	}
}

bool MyBST::recursiveFindRecord(PatientRecord* record, MyBSTNode* currNode) {
	if(currNode == NULL ) {
		return false;
	}

	if(currNode->record->getRecordID() == record->getRecordID()) {
		return true;
	}

	if( (*(record->getEntryDate())) <= (*(currNode->record->getEntryDate())) ) {
		return recursiveFindRecord(record, currNode->left);
	} else {
		return recursiveFindRecord(record, currNode->right);
	}
}

bool MyBST::findRecord(PatientRecord* record) {
	return recursiveFindRecord(record, root);
}

int MyBST::globalDiseaseStats(char* date1, char* date2) {
	if( date1 == NULL || date2 == NULL)
		return numOfRecords;
	MyDate mydate1 = MyDate(date1);
	MyDate mydate2 = MyDate(date2);
	//traverse with date1 <= entryDate <= date2
	return traverse(root, mydate1, mydate2, NULL);
}
int MyBST::diseaseFrequency(char* date1, char* date2, char* country) {
	if( country == NULL )
		return globalDiseaseStats(date1, date2);

	MyDate mydate1 = MyDate(date1);
	MyDate mydate2 = MyDate(date2);
	//traverse with country kai date1 <= entryDate <= date2
	return traverse(root, mydate1, mydate2, country);
}

int MyBST::traverse(MyBSTNode* currNode, MyDate& date1, MyDate& date2, char* country) {
	if(currNode == NULL ) {
		return 0;
	}
	int result = 0;
	bool check1 = (*(currNode->record->getEntryDate())) >= date1;
	bool check2 = (*(currNode->record->getEntryDate())) <= date2;
	if( check1 ) //there is no need to check the left subtree if entryDate < date1
		result += traverse(currNode->left, date1, date2, country);
	if( check2 ) //there is no need to check the left subtree if entryDate > date2
		result += traverse(currNode->right, date1, date2, country);


	if( check1 && check2 ) {
		if( country == NULL || !strcmp(country, currNode->record->getCountry() ))
			result ++;
	}
	
	return result;
}

int MyBST::recursiveNumCurrentPatients(MyBSTNode* currNode) {
	if(currNode == NULL ) {
		return 0;
	}
	int result = 0;
	result += recursiveNumCurrentPatients(currNode->left);
	result += recursiveNumCurrentPatients(currNode->right);


	if( currNode->record->getExitDate() == NULL ) {
		result ++;
	}
	
	return result;
}
int MyBST::numCurrentPatients() {
	return recursiveNumCurrentPatients(root);
}
bool MyBST::recordPatientExit(int recordID, char* exitDate) {
	PatientRecord* target = recursiveFindRecord(recordID, root);
	if ( target != NULL ) {
		target->setExitDate(exitDate);
		return true;
	}
	return false;
}
PatientRecord* MyBST::recursiveFindRecord(int recordID, MyBSTNode* currNode) {
	if(currNode == NULL ) {
		return NULL;
	}

	if(currNode->record->getRecordID() == recordID) {
		return currNode->record;
	}

	PatientRecord* target = recursiveFindRecord(recordID, currNode->left);
	if (target != NULL ) {
		return target;
	}
	else {
		return recursiveFindRecord(recordID, currNode->right);
	}
}

/***********************************************************/
