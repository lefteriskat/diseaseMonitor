

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
	cout << key << " : " << numOfRecords << endl;
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
	return &entries[numOfEntries-1];
}
bool DCHashTableBucket::isFull() {
	return (numOfEntries == maxEntries-1);
}
void DCHashTableBucket::printNumberOfRecords(char* date1, char* date2, char* country) {
	for( int i = 0; i < numOfEntries; i++) {
		entries[i].printNumberOfRecords(date1, date2, country);
	}
}
/***********************************************************/

/***************** DCHashTableBucketList *******************/
DCHashTableBucketList::DCHashTableBucketList() {
	firstNode = new DCHashTableBucket();
	numOfNodes = 1;
}
DCHashTableBucketList::~DCHashTableBucketList() {
	delete firstNode;
}
DCHashTableEntry* DCHashTableBucketList::addEntry(char* key) {
	DCHashTableBucket*& currNode = firstNode;
	while ( currNode != NULL && currNode->isFull() ) {
		currNode = currNode->next;
	}
	if ( currNode == NULL) {
		currNode = new DCHashTableBucket();
		numOfNodes++;
	}
	return currNode->addEntry(key);
}
DCHashTableEntry* DCHashTableBucketList::findEntry(char* key) {
	DCHashTableBucket* currNode = firstNode;
	DCHashTableEntry* entry = NULL;
	while ( currNode != NULL ) {
		entry = currNode->findEntry(key);
		if( entry != NULL )
			break;
	}
	return entry;
}
bool DCHashTableBucketList::addRecord(char* key,
                                      PatientRecord* patientRecord) {
	DCHashTableEntry* entry = findEntry(key);
	if ( entry!= NULL ) {
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
			cout << key << " : 0" << endl; 
	} else {

		DCHashTableBucket* currNode = firstNode;
		while ( currNode != NULL ) {
			currNode->printNumberOfRecords(date1, date2, country);
			currNode = currNode->next;
		}
	}
}
/***********************************************************/

/***********************************************************/
DCHashTable::DCHashTable(unsigned int numOfEntries) {
	dcHashTable = new DCHashTableBucketList[numOfEntries];
	this->numOfEntries = numOfEntries;
}
DCHashTable::DCHashTable::~DCHashTable() {
	delete [] dcHashTable;
}
bool DCHashTable::addRecord(char* key, patientRecord* record) {
	unsigned int index = hashFunction(key);
	dcHashTable[index].addRecord(key, record);
}
void DCHashTable::printNumberOfRecords(char* key,char* date1, char* date2, char* country) {
	if( key != NULL ) {
		unsigned int index = hashFunction(key);
	    dcHashTable[index].printNumberOfRecords(key, date1, date2, country);
	}
	else {
		for( unsigned int i =0 ; i < numOfEntries; i++ ) {
			dcHashTable[index].printNumberOfRecords(key, date1, date2, country);
		}
	}
}
unsigned int DCHashTable::hashFunction(const char* str) {
	unsigned int hash = 1315423911;

	for(size_t i = 0; i < strlen(str); i++) {
		hash ^= ((hash << 5) + str[i] + (hash >> 2));
	}
	return (hash & 0x7FFFFFFF) % numOfEntries;
}

/***********************************************************/