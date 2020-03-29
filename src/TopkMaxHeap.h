// TopkMaxHeap.h
#ifndef TOPKMAXHEAP_H
#define TOPKMAXHEAP_H
#include "TopkArrayList.h"

class TopkMaxHeapNode
{
	TopkArrayListNode* data;
	TopkMaxHeapNode* parent;

	TopkMaxHeapNode* left;
	TopkMaxHeapNode* right;

public:
	TopkMaxHeapNode(TopkArrayListNode* data);
	~TopkMaxHeapNode();
	friend class TopkMaxHeap;
};



class TopkMaxHeap
{
	TopkMaxHeapNode* root;
public:
	TopkMaxHeap();
	~TopkMaxHeap();
	void insert(TopkArrayListNode* data);
	TopkArrayListNode* pop();
	TopkMaxHeapNode* findLastNodeToInsert();
	TopkMaxHeapNode* idfsInsert(TopkMaxHeapNode* currNode, int limit);
	TopkMaxHeapNode* findLastNodeToDelete();
	TopkMaxHeapNode* idfsDelete(TopkMaxHeapNode* currNode, int limit);
	void swap(TopkMaxHeapNode* node1,TopkMaxHeapNode* node2);
	void traverse();
	void traverse(TopkMaxHeapNode* currNode, int limit);
};

#endif