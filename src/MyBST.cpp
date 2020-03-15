//MyBST.cpp

/*********************** MyBSTNode *************************/

MyBSTNode::MyBSTNode(PatientRecord* record) {
	this->record = record;
	left  =  NULL;
	right = NULL;
}

//poly pi8ano na paei sto tree
MyBSTNode::~MyBSTNode() {
	if( left != NULL )
		delete left;
	if ( right != NULL )
		delete right;
	if( !global_DataDeleted )
		delete record;
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
	if( findRecord(record) )
		return false;

	recursiveAddRecord(record, root);
}

void MYBST::recursiveAddRecord(PatientRecord* record, MyBSTNode*& currNode) {

	if(currNode == NULL ) {
		currNode = new MyBSTNode(record);
		numOfRecords++;
		return;
	}

	if( (*(record->getEntryDate())) < (*(currNode->record->getEntryDate())) ) {
		recursiveAddRecord(record, currNode->left);
	} else {
		recursiveAddRecord(record, currNode->right);
	}
}

bool recursiveFindRecord(PatientRecord* record, MyBSTNode* currNode) {
	if(currNode == NULL ) {
		return false;
	}

	if(currNode->record->getRecordID() == record->getRecordID())
		return true;

	if( (*(record->getEntryDate())) < (*(currNode->record->getEntryDate())) ) {
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
	//treverse with date1 <= entryDate <= date2
	return 0; 
}
int MyBST::diseaseFrequency(char* date1, char* date2, char* country) {
	if( country == NULL )
		return globalDiseaseStats(date1, date2);
	//traverse me country kai date1 <= entryDate <= date2
}
int MyBST::numCurrentPatients() {
	//traverse me exitDate == NULL
	return 0;
}

/***********************************************************/
