#ifndef HEAP_H
#define HEAP_H
#include "Order.h"

const int ARRAY_SIZE = 1000;
class Heap {
public:
	Heap() : numElements(0) {}
	void ReheapDown(int root, int bottom);
	void ReheapUp(int root, int bottom);
	void addOrder(Order newOrder);
	void Print();
	void Heapify();

protected:

	int numElements;
};


#endif HEAP_H
