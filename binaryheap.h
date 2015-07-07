/**
* File: binaryheap.h
* Author: Scott Barcus
* Implementation of a max binary heap
**/

#ifndef _BH_H
#define _BH_H 

#include <iostream>
#include <string>

using namespace std;


template<class T>
class BinaryHeap
{
private:

	/**
	* Nodes of binary heap abstract data structure.  Pointers of type Node* point to left and right nodes
	**/
	class Node
	{
	public:
		/**
		* Default constructor for node object with filled with the following data:
		* left - pointer to the left node
		* right - pointer to the right node
		* parent - pointer the the parent node
		* next - pointer to the next node in the linked list threaded through the tree
		* prev - pointer to the previous node in the linked list threaded through the tree
		* data - type T is user defined and is left unitialized by this default constructor
		* id   - unique id for each node.  Necessary for the generateDotFile method
		**/
		Node() {
			left = NULL;
			right = NULL;
			parent = NULL;
			next = NULL;
			prev = NULL;
			id = 0;
		}
		T data;
		int id;
		Node *left;
		Node *right;
		Node *parent;
		Node *next;
		Node *prev;
	};


	/**
	* Private data members for list
	* head - pointer to first node in linked list
	* root - pointer to root node in tree
	* tail - pointer to last node
	* nodeCount - number of nodes in the list
	**/
	Node* head;
	Node* root;
	Node* tail;
	int nodeCount;

	/**
	* Private version of a public method of same name.  The public version does not have access to nodes.
	* Details for how to create the dot file are explained with the public version.
	* @param node - public version must call this private method by passing in the root of the tree as node
	**/
	void generateDotFile(Node* node);
	/**
	* Private version of public method of same name.  
	* @param node* = pointer to a node
	**/
	//void remove(Node* node);


	/**
	* Private utility function - swaps two data values
	* @param *d1 - pointer to data 1
	* @param *d2 = pointer to data 2 
	**/
	void swap(T *d1, T *d2) {
		T tmp = *d1;
		*d1 = *d2;
		*d2 = tmp;
	}

	/**
	* Compare function 
	* Called by insert to bubble data up toward the top of the heap
	* @param *node - pointer to a node in the tree
	* @param *parent - pointer to the parent of the node in parameter 1 
	**/
	void compare(Node *node, Node *parent) {
		if (!parent) return;
		if (node->data < parent->data) {
			return;
		}
		swap(&(node->data), &(parent->data));
		compare(parent, parent->parent);
	}

	void trickleDown(Node * node);

public:
	/**
	* Default constructor for the DoublyLinked list
	**/
	BinaryHeap() {
		nodeCount = 0;
		head = NULL;
		tail = NULL;
		root = NULL;
	}
	~BinaryHeap() {}

	/**
	* Public insert function.  This function assumes that data can be ordered and compared using <, > and ==.
	* @param dataToInsert - data of type T to insert.
	**/
	void insert(T dataToInsert);


	/**
	* Public remove funciton.
	* PreCondition - binary heap
	* PostCondition - previous root is removed from heap, a binary heap is maintained
	**/
	void remove();

	/**
	* Public peek function.  Output the value of the root of tree.
	* Pre and Post conditions identical.  This function should not alter the tree.
	**/
	void peek() {
		cout << root->data << endl;
	}

	/**
	* Public generateDotFile method.  Calls the private version with root passed in.  To create a visualization of the tree follow the following steps.
	* download the dot program from graphiz.org
	* call generateDotFile with all other code that passes a stream to stdout commented out
	* compile the program and re-direct the stdout to a file like foo.txt
	* call dot, eg dot -Tpng foo.txt > foo.png will generate a png file
	* open the png file
	**/
	void generateDotFile() {

		cout << "digraph {" << endl;
		generateDotFile(root);
		cout << "}" << endl;
	}


};

template<class T>
void BinaryHeap<T>::trickleDown(Node * node) {
	if (!node->left && !node->right) {
		return;
	}	

	T bigger;
	Node *biggerNode;


	if (!node->right) {
		if (node->left->data > node->data)
			swap(&(node->left->data), &(node->data));
		return;
	}

	// find bigger child data and node
	if (node->left->data > node->right->data) {
		bigger = node->left->data;
		biggerNode = node->left;
	}
	else {
		bigger = node->right->data;
		biggerNode = node->right;
	}

	// if no child is greater than the node's data, return.  We are done.
	if (bigger <= node->data) return;

	// swap and call remove again on the node that now contains the data from the parent node
	swap(&(node->data), &(biggerNode->data));
	trickleDown(biggerNode);

}

template<class T>
void BinaryHeap<T>::remove() {

	if (!root->left && !root->right) { // we are deleting the only node in the tree
		Node * tmp = root;
		head = NULL;
		tail = NULL;
		root = NULL;
		delete tmp;
		nodeCount--;
		return;
	}

	//copy tail data to root
	root->data = tail->data;
	//remove old tail 
	tail->prev->next = NULL;
	if (tail->parent->right) {
		tail->parent->right = NULL;
	}
	else {
		tail->parent->left = NULL;
	}
	Node* tmp = tail;
	tail = tmp->prev;
	delete tmp;
	nodeCount--;
	
	trickleDown(root);

}

template<class T>
void BinaryHeap<T>::insert(T item) {
	// Node *ptrToTail = tail;
	Node* node = new Node();
	nodeCount++;
	node->id = nodeCount;  //used to generate the dot file
	node->data = item;

	if (!tail) //empty tree
	{
		root = node;
		head = node;
		tail = node;
		return;
	}
	if (!tail->parent) // inserting as L-child after root
	{
		tail->left = node;  //assign left pointer
		node->parent = tail; //assign parent pointer
		tail->next = node; // assign next pointer
		tail = node;       // move tail
		tail->prev = node->parent;  //assign prev pointer
		//compare and swap if needed
		compare(node, node->parent);
		// if (node->data > head->data) {
		// 	swap(&(node->data), &(head->data));
		// }
		return;
	}
	if (tail->parent->left && tail->parent->right) { // insert new node as l-child of tail->parent->next
		tail->parent->next->left = node;  //left pointer
		node->parent = tail->parent->next;  //parent poitner
		tail->next = node;					//next pointer
		node->prev = tail;					//prev
		tail = node;						//move tail
		compare(node, node->parent);			//compare and swap


	}
	else { //insert new node as r-child
		tail->parent->right = node; //assign right pointer
		node->parent = tail->parent;	//parent pointer
		tail->next = node;				//next pointer
		node->prev = tail;				//prev ptr
		tail = node;
		//compare and swap if needed
		compare(node, node->parent);
	}
}

template <class T>
void BinaryHeap<T>::generateDotFile(Node* node) {
	if (node == NULL) {
		return;
	}

	//make root node
	if (!node->parent) {
		cout << "n" << node->id << ";" << endl;
		cout << "n" << node->id << " [label = \"" << node->data << "\" ];" << endl;
	}

	// make node to left and draw edge
	if (node->left) {
		cout << "n" << node->left->id << ";" << endl;
		cout << "n" << node->left->id << " [label = \"" << node->left->data << "\" ];" << endl;
		cout << "n" << node->id << " -> " << "n" << node->left->id << ";" << endl;
	}
	else { // no node to left, make null node and link
		cout << "null" << node->id << " [shape= \"point\" width = \"0\"];" << endl;
		cout << "n" << node->id << "-> null" << node->id << " [arrowsize = \"0\", pendwidth = \"0\"];" << endl;
	}

	// make node to right and draw edge
	if (node->right) {
		cout << "n" << node->right->id << ";" << endl;
		cout << "n" << node->right->id << " [label = \"" << node->right->data << "\" ];" << endl;
		cout << "n" << node->id << " -> " << "n" << node->right->id << ";" << endl;
	}
	else { // no node to right, make null node and link
		cout << "nullr" << node->id << " [shape= \"point\" width = \"0\"];" << endl;
		cout << "n" << node->id << "-> nullr" << node->id << " [arrowsize = \"0\", pendwidth = \"0\"];" << endl;
	}

	generateDotFile(node->left);
	generateDotFile(node->right);
}

#endif