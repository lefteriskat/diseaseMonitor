//TopkArrayList.cpp
#include "TopkArrayList.h"
#include <cstdlib>
#include <cstring>
using namespace std;

TopkArrayListNode::TopkArrayListNode() {
	numOfRecords = 0;
	key[0] = '\0';
}
TopkArrayListNode::TopkArrayListNode(char* mykey, int records) {
	numOfRecords = records;
	strncpy(this->key, mykey, 64);
}
TopkArrayListNode::~TopkArrayListNode() {
}
char* TopkArrayListNode::getKey() {
	return key;
}
int TopkArrayListNode::getNumOfRecords() {
	return numOfRecords;
}
void TopkArrayListNode::increaseNumOfRecords() {
	numOfRecords++;
}
void TopkArrayListNode::setKey(char* key) {
	strncpy(this->key, key, 64);
}


TopkArrayList::TopkArrayList() {
	size =  INITIAL_ARRAY_LIST_SIZE;
	topkArrayList = (TopkArrayListNode*) malloc(size * sizeof(TopkArrayListNode));
	numOfNodes = 0;
}
TopkArrayList::~TopkArrayList() {
	free(topkArrayList);
}
void TopkArrayList::insert(char* key) {
	TopkArrayListNode* target = find(key);
	if( target != NULL) {
		target->increaseNumOfRecords();
	} 
	else {
		if(numOfNodes >= size) {
			size*=2;
			topkArrayList = (TopkArrayListNode*) realloc(topkArrayList, size * sizeof(TopkArrayListNode));
		}

		topkArrayList[numOfNodes].setKey(key);
		topkArrayList[numOfNodes].numOfRecords = 0;
		topkArrayList[numOfNodes].increaseNumOfRecords();
		numOfNodes++;
	}
}
int TopkArrayList::length() {
	return numOfNodes;
}
TopkArrayListNode* TopkArrayList::get(int index) {
	return &(topkArrayList[index]);
}
TopkArrayListNode* TopkArrayList::find(char* key) {
	for( int i = 0; i < numOfNodes; i++) {
		if(strcmp(topkArrayList[i].key, key) == 0)
			return &(topkArrayList[i]);
	}
	return NULL;
}