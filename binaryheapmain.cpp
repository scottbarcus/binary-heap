/**
* File: binaryheapmain.cpp
* Author: Scott Barcus
* Driver for binary heap.h
**/

#include <iostream>
#include "binaryheap.h"

using namespace std;

int main(int argc, char const *argv[])
{
	/**
	* Create an <int> binary heap and insert come numbers
	**/
	BinaryHeap<int> intHeap;
	intHeap.insert(52);
	intHeap.insert(10);
	intHeap.insert(4);
	intHeap.insert(22);
	intHeap.insert(35);
	intHeap.insert(46);
	intHeap.insert(17);

	/**
	* Destroy the tree to make sure that all special cases in remove function are handled
	**/
	intHeap.remove();
	intHeap.remove();
	intHeap.remove();
	intHeap.remove();
	intHeap.remove();
	intHeap.remove();
	intHeap.remove();

	/**
	* Prove that we can re-build the tree
	**/
	intHeap.insert(52);
	intHeap.insert(10);
	intHeap.insert(4);
	intHeap.insert(22);
	intHeap.insert(35);
	intHeap.insert(46);
	intHeap.insert(17);

	//intHeap.peek();

	/**
	* Dot file generated to visualize the tree.  Comment out if there is no need to visualize the tree
	**/
	intHeap.generateDotFile();
	

	return 0;
}