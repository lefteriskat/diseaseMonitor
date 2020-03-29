//TopkArrayList.h
#ifndef TOPKMARRAYLIST_H
#define TOPKMARRAYLIST_H

#define INITIAL_ARRAY_LIST_SIZE 64

class TopkArrayListNode {
	int numOfRecords;
	char key[64];
public:
	TopkArrayListNode();
	TopkArrayListNode(char* mykey, int records);
	~TopkArrayListNode();
	char* getKey();
	int getNumOfRecords();
	void increaseNumOfRecords();
	void setKey(char* key);
	friend class TopkArrayList;	
};

class TopkArrayList {
	TopkArrayListNode* topkArrayList;
	int numOfNodes;
	int size;
public:
	TopkArrayList();
	~TopkArrayList();
	int length();
	TopkArrayListNode* get(int index);
	TopkArrayListNode* find(char* key);
	void insert(char* key);
};

#endif