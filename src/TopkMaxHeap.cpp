//TopkMaxHeap.cpp
#include "TopkMaxHeap.h"
#include <iostream>

using namespace std;

TopkMaxHeapNode::TopkMaxHeapNode(TopkArrayListNode* data) {
	this->data = data;
	parent = NULL;
	left = NULL;
	right = NULL;

}
TopkMaxHeapNode::~TopkMaxHeapNode() {

}



TopkMaxHeap::TopkMaxHeap() {
	root = NULL;
}
TopkMaxHeap::~TopkMaxHeap() {
	TopkArrayListNode* x = pop();
	while( x != NULL ){
		x = pop();
	}
}
void TopkMaxHeap::insert(TopkArrayListNode* data) {
	if( root == NULL ) {
		root = new TopkMaxHeapNode(data);
	}
	else
	{
		TopkMaxHeapNode* lastNode = findLastNodeToInsert();
		TopkMaxHeapNode** newNode = (lastNode->left == NULL)?&(lastNode->left):&(lastNode->right);
		
		*newNode = new TopkMaxHeapNode(data);
		(*newNode)->parent = lastNode;

		lastNode = *newNode;
		
		while( lastNode->parent && lastNode->data->getNumOfRecords() > lastNode->parent->data->getNumOfRecords()) {
			swap(lastNode->parent, lastNode);
		}
	}
}
TopkMaxHeapNode* TopkMaxHeap::findLastNodeToInsert() {
	int limit = 0;
	TopkMaxHeapNode* lastNode = idfsInsert(root,limit);
	while( lastNode == NULL) {
		lastNode = idfsInsert(root,++limit);
	}
	return lastNode;
}
TopkMaxHeapNode* TopkMaxHeap::idfsInsert(TopkMaxHeapNode* currNode, int limit) {
	if( currNode->left == NULL )
		return currNode;
	if( currNode->right == NULL )
		return currNode;
	if( limit <= 0)
		return NULL;
	TopkMaxHeapNode* target = idfsInsert(currNode->left , limit-1);
	if( target != NULL )
		return target;
	return idfsInsert(currNode->right, limit-1);
}
void TopkMaxHeap::traverse() {
	int limit = 0;
	traverse(root,limit);
}
void TopkMaxHeap::traverse(TopkMaxHeapNode* currNode, int limit) {
	if(currNode == NULL){
		return;
	}
	cout << limit << " " << currNode->data->getNumOfRecords() << endl;
 	traverse(currNode->left , limit+1);
	traverse(currNode->right, limit+1);
}
TopkMaxHeapNode* TopkMaxHeap::findLastNodeToDelete() {
	int limit = 0;
	TopkMaxHeapNode* lastNode = idfsDelete(root,limit);
	while( lastNode == NULL ) {
		lastNode = idfsDelete(root,++limit);
	}
	return lastNode;
}
TopkMaxHeapNode* TopkMaxHeap::idfsDelete(TopkMaxHeapNode* currNode, int limit) {
	if( currNode == NULL)
		return NULL;
	if( currNode->left == NULL && currNode->right == NULL)
		return currNode;

	if( limit <= 0)
		return NULL;
	TopkMaxHeapNode* target = idfsDelete(currNode->right , limit-1);
	if( target != NULL )
		return target;
	return idfsDelete(currNode->left, limit-1);
}
TopkArrayListNode* TopkMaxHeap::pop() {
	if( root == NULL )
		return NULL;
	TopkArrayListNode* mydata = root->data;
	TopkMaxHeapNode* lastNode = findLastNodeToDelete();
	if( lastNode == root ){
		delete root;
		root = NULL;
	}
	else{
		if(lastNode->parent->left == lastNode){
			lastNode->parent->left = NULL;
		}
		else if(lastNode->parent->right == lastNode){
			lastNode->parent->right = NULL;
		}
		lastNode->parent = NULL;
		lastNode->right = root->right;
		if( lastNode->right != NULL ){
			lastNode->right->parent = lastNode;
		}
		lastNode->left = root->left;
		if( lastNode->left != NULL ){
			lastNode->left->parent = lastNode;
		}


		TopkMaxHeapNode* tempRoot = root;
		root = lastNode;
		delete tempRoot;
		tempRoot = lastNode;
		bool swapped = true;
		while ( swapped ) {
			if( tempRoot->left && tempRoot->data->getNumOfRecords() < tempRoot->left->data->getNumOfRecords() &&
			 (tempRoot->right == NULL || tempRoot->left->data->getNumOfRecords() > tempRoot->right->data->getNumOfRecords()) )  {
				swap(tempRoot, tempRoot->left);
			}
			else if( tempRoot->right && tempRoot->data->getNumOfRecords() < tempRoot->right->data->getNumOfRecords() ) {
				swap(tempRoot, tempRoot->right);
			}
			else {
				swapped = false;
			}
		}
	}

	return mydata;
}
void TopkMaxHeap::swap(TopkMaxHeapNode* node1,TopkMaxHeapNode* node2) {
	TopkMaxHeapNode* tempNode1Left = node1->left;
	TopkMaxHeapNode* tempNode1Right = node1->right;
	
	node1->left = node2->left;
	node1->right = node2->right;
	if(node1->left)
		node1->left->parent = node1;
	if(node1->right)
		node1->right->parent = node1;
	
	node2->left = (tempNode1Left == node2)?node1:tempNode1Left;
	node2->right = (tempNode1Right == node2)?node1:tempNode1Right;

	
	node2->parent = node1->parent;
	if( node2->left )
		node2->left->parent = node2;
	if( node2->right )
		node2->right->parent = node2;

	
	if( node2->parent == NULL)
		root = node2;
	else {
		if(node2->parent->left == node1)
			node2->parent->left = node2;
		else if(node2->parent->right == node1)
			node2->parent->right = node2;
	}
}