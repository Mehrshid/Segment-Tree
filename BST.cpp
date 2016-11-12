//
//  main.cpp
//  BST Projct
//
//  Created by Mehrshid Fadaei Nejad on 2/26/1394 AP.
//  Copyright (c) 1394 Mehrshid Fadaei Nejad. All rights reserved.
//

#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <ctime>

using namespace std;

typedef int value;

class Node {
	
public:
	
	value data;
	
	Node *leftChild;
	Node *rightChild;
	
	Node(value);
	Node();
	
};

class BinarySearchTree {
	
public:
	
	value getTreeHeight(Node*);
	value getNodeDepth(Node*);
	
	Node *key;
	
	Node *searchNodeByValue(value);
	Node *findParentOfNode(value);
	Node *findRightMostChild(Node*);
	Node *findLeftMostChild(Node*);
	Node *minNode();
	Node *maxNode();
	Node *current;
	
	
	void deleteMinNode();
	void deleteMaxNode();
	void traverseTree();
	
	void preOrderTree(Node*);
	void preOrderToQueue(Node*,value,value);
	void inOrderTree(Node*);
	void postOrderTree(Node*);
	void levelOrderPrint(Node*);
	void insert(value);
	void remove(value);
	long calculateTime();
	
	BinarySearchTree();
	
};


Node::Node (){
	
	leftChild = rightChild = NULL;
	
	
}

Node::Node (value val) {
	
	data = val;
	leftChild = rightChild = NULL;
	
}

BinarySearchTree::BinarySearchTree(){
	
	key = current = NULL;
	
}


// :::: Insert in Binary Search Tree ::::

void BinarySearchTree::insert (value val){
	
	
	if (key == NULL)
		key = new Node (val);
	
	else {
		Node *position = searchNodeByValue(val);
		
		if (position == 0) {
			Node *parent = key;
			
			if (position != key) {
				parent = findParentOfNode(val);
				
				if( val > parent->data)
					parent->rightChild = new Node(val);
				
				else
					parent->leftChild = new Node(val);
			}
		}
	}
}


// :::: Removing in Binary Search Tree ::::

void BinarySearchTree::remove (value val) {
	
	Node *nodeToBeDeleted = searchNodeByValue(val);
	
	
	// Case 1: If We Don't have Any Root
	if (key == NULL)
		cout << "There is No Node to Delete";
	
	else {
		
		
		// Case 2: Node has No Children
		if (nodeToBeDeleted != 0) {
			
			if ((nodeToBeDeleted->leftChild == NULL) && (nodeToBeDeleted->rightChild == NULL)) {
				
				if(nodeToBeDeleted != key) {
					Node *parent = findParentOfNode(val);
					
					if(val < parent->data)
						parent->leftChild = NULL;
					
					else
						parent->rightChild = NULL;
				}
				
				else
					key = NULL;
				
				delete (nodeToBeDeleted);
			}
			
			
			
			// Case 3: Node has Only LEFT Child
			else if((nodeToBeDeleted->leftChild == NULL) && (nodeToBeDeleted->rightChild != NULL)) {
				
				if(nodeToBeDeleted != key) {
					Node *parent = findParentOfNode(val);
					
					if(val < parent->data)
						parent->leftChild = nodeToBeDeleted->leftChild;
					
					else
						parent->rightChild = nodeToBeDeleted->leftChild;
				}
				
				else
					key = NULL;
				
				delete (nodeToBeDeleted);
				
			}
			
			
			// Case 4: Node has Only RIGHT Child
			else if ((nodeToBeDeleted->leftChild != NULL) && (nodeToBeDeleted->rightChild == NULL)) {
				
				if (nodeToBeDeleted != key) {
					Node *parent = findParentOfNode(val);
					
					if (val < parent->data)
						parent->leftChild = nodeToBeDeleted->rightChild;
					else
						parent->rightChild = nodeToBeDeleted->rightChild;
				}
				
				else
					key = NULL;
				delete (nodeToBeDeleted);
				
			}
			
			
			// Case 5: Node has 2 Childeren
			else {
				
				Node *rightest = findRightMostChild (nodeToBeDeleted->leftChild);
				Node *parent = findParentOfNode (rightest->data);
				nodeToBeDeleted->data = rightest->data;
				
				if (parent != nodeToBeDeleted)
					parent->rightChild = rightest->leftChild;
				
				else
					nodeToBeDeleted->leftChild = rightest->leftChild;
				
				delete rightest;
				
				
			}
			
		}
		
	}
}


// :::: Search in Binary Search Tree ::::

Node* BinarySearchTree::searchNodeByValue (value k) {
	
	Node *node = key;
	
	while ((node != NULL) && (node->data != k)) {
		
		if(k < node->data)
			node = node->leftChild;
		else
			node = node->rightChild;
	}
	
	return node;
}


Node* BinarySearchTree::findParentOfNode (value k) {
	
	Node *node = key;
	Node *parentofNode = NULL;
	
	while ((node != NULL) && (node->data != k)) {
		
		parentofNode = node;
		
		if (k < node->data)
			node = node->leftChild;
		
		else
			node = node->rightChild;
	}
	
	return parentofNode;
}


Node* BinarySearchTree::findRightMostChild (Node *node) {
	
	Node *rightest = node;
	
	while (rightest->rightChild != NULL)
		
		rightest = rightest->rightChild;
	
	return rightest;
}


Node* BinarySearchTree::findLeftMostChild (Node *node) {
	
	Node *leftest = node;
	
	while (leftest->leftChild != NULL)
		
		leftest = leftest->leftChild;
	
	return leftest;
	
}


Node* BinarySearchTree::minNode() {
	
	return findLeftMostChild(key);
	
}


Node* BinarySearchTree::maxNode() {
	
	return findRightMostChild(key);
	
}


void BinarySearchTree::deleteMaxNode() {
	
	Node *nodeToBeDeleted = findRightMostChild(key);
	
	remove(nodeToBeDeleted->data);
	
}


void BinarySearchTree::deleteMinNode() {
	
	Node *nodeToBeDeleted = findLeftMostChild(key);
	
	remove(nodeToBeDeleted->data);
	
}


void BinarySearchTree::preOrderTree(Node* k) {
	
	if (k != NULL) {
		
		cout << k->data << " ";
		preOrderTree (k->leftChild);
		preOrderTree (k->rightChild);
		
	}
}


void BinarySearchTree::inOrderTree(Node* k) {
	
	if (k != NULL) {
		
		inOrderTree (k->leftChild);
		cout << k->data << " ";
		inOrderTree (k->rightChild);
		
	}
}


void BinarySearchTree::postOrderTree(Node* k) {
	
	if (k != NULL) {
		
		postOrderTree (k->leftChild);
		postOrderTree (k->rightChild);
		cout << k->data << " ";
		
	}
}


void BinarySearchTree::traverseTree() {
	
	cout << "Preorder: ";
	preOrderTree(key);
	
	cout << endl << "Inorder: ";
	inOrderTree(key);
	
	cout << endl << "PostOrder: ";
	postOrderTree(key);
	
	cout << endl;
}


value BinarySearchTree::getTreeHeight (Node* k) {
	
	if (k == 0)
		return -1;
	
	value leftHeight = getTreeHeight (k->leftChild);
	value rightHeight = getTreeHeight (k->rightChild);
	
	if (leftHeight > rightHeight)
		return leftHeight + 1;
	
	else
		return rightHeight + 1;
	
}

void BinarySearchTree::levelOrderPrint (Node* root) {
	
	if ( root == NULL )
		return;
	
	int counter = 0;
	int level = 0;
	int maxInLevel;
	Node nullNode;
	nullNode.data = -1;
	Node* nullNodePtr = &nullNode;
	
	int allNodes = (int)pow(2,getTreeHeight(key)+1) - 1;
	int height = getTreeHeight(key);
	
	queue<Node*> Q;
	Q.push(root);
	
	while ( counter != allNodes ){
		
		maxInLevel = (int)pow(2,level+1) - 1;
		
		if ( counter == maxInLevel ) {
			cout << endl;
			level++;
		}
		
		if ( counter == ((int)pow(2,level)-1) ){
			cout << setw ((height-level)*5);
		}
		
		Node* current = Q.front();
		cout << current->data << setw((height+1-level)*8);
		
		
		if ( current->leftChild != NULL )
			Q.push ( current->leftChild );
		if ( current->leftChild == NULL )
			Q.push ( nullNodePtr );
		
		if ( current->rightChild != NULL )
			Q.push ( current->rightChild );
		if ( current->rightChild == NULL )
			Q.push ( nullNodePtr );
		
		Q.pop();
		counter++;
	}
}



long BinarySearchTree::calculateTime () {
	
	time_t prev = time(0);
	
	time_t now = time(0);
	
	return now-prev;
	
}



int main (int argc, const char * argv[]) {
	
	
	value num,nodeValue, running = 1;
	
	BinarySearchTree tree;
	
	
	cout << endl << endl;
	cout << " Binary Search Tree Operations Menu " << endl;
	cout << " ---------------------------------- " << endl;
	cout << " 1. Insert a Node " << endl;
	cout << " 2. Search a Node " << endl;
	cout << " 3. In-Order/Pre-Oder/Post-Order Traversal " << endl;
	cout << " 4. Maximum & Minimum of Tree " << endl;
	cout << " 5. Delete Min and Max Value of Binary Search Tree " << endl;
	cout << " 6. Delete a Node " << endl;
	cout << " 7. Exit " << endl << endl;
	
	while (running == 1) {
		
		
		cout << endl << " Enter your choice : ";
		cin >> num;
		
		switch (num) {
				
			case 1 : cout << " Enter Number to be Inserted : ";
				
				cin >> nodeValue;
				tree.insert(nodeValue);
				break;
				
				
			case 2 : cout << " Enter a Number to be Searched : ";
				
				cin >> nodeValue;
				if (tree.searchNodeByValue(nodeValue))
					cout << "Node Available in Tree";
				break;
				
				
			case 3 : cout << endl;
				
				cout << " Pre-Order/In-Order/Post-Order Traversal " << endl;
				cout << " -------------------" << endl;
				tree.traverseTree();
				break;
				
				
			case 4 : cout << endl;
				
				cout << " Maximum of Tree is : " << tree.maxNode()->data << " and Minimum of Tree is : " << tree.minNode()->data;
				break;
				
				
			case 5 : cout << endl;
				
				tree.deleteMaxNode();
				tree.deleteMinNode();
				break;
				
				
			case 6 : cout << " Enter a Number to be Deleted";
				
				cin >> nodeValue;
				tree.remove(nodeValue);
				break;
				
				
			case 7 : cout << endl;
				
				system("pause");
				running = 0;
				break;
		}
		
		
		tree.levelOrderPrint(tree.key);
	}
	
	
	return 0;
}







