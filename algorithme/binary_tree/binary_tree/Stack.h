#pragma once

#include "Node.h"

#define MAX 100


class Stack
{
private:
	Node *mStackArray[MAX];//������ �迭�� ����
	int mTop = 0;

public:
	Stack();
	~Stack();

	void InitializeStack();
	void Push(Node *);
	Node* Pop();
	bool IsStackEmpty();
};

