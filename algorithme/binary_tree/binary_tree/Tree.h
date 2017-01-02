#pragma once

#include "Stack.h"

class Tree
{
private:
	Node* mParent = NULL;
	Node* mLeftChild = NULL;
	Node* mRightChild = NULL;

	Node* mHeadNode = NULL;
	Node* mEndNode = NULL;

	Stack* mStack = NULL;
public:
	Tree();
	~Tree();

	void MakeTree();
	
	void Traverse();//���� ��ȸ

	void RecursiveTraverse(Node *ptrNode);//���ȣ��
	
	//���� ��ȸ
	void MediumStackTraverse();//����

	//���� ��ȸ
	void RearStackTraverse();//����

	void Visit(Node *);

	Node *GetHeadNode();
};

