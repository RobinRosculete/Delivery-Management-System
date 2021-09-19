#ifndef PQUEUE_H
#define PQUEUE_H
#include"Order.h"
#include <iomanip>

const int WIDTH_SIZE = 20;
class pQueue{
public:
	pQueue():length(0),orderCounter(0), countWidgetsOrdered(0){}

	void ReheapDown(int root, int bottom);
	void ReheapUp(int root, int bottom);

	void Enquque(int numwidgetsOrdered, RushStatus Status);
	void Dequeue(Order& Order);
	double calculateOrderPrice(Order tepmOrder);
	double calculateTotalCostToCustomer();

	//Pre:NA
	//Post:return true if queue is empty, else return false
	bool IsEmpty()const { return length == 0; };

	//Pre:NA
	//Post:return true if queue is full, else return false
	bool IsFull()const { return length == WIDGET_STOCK;};

	//Pre:An order exists
    //Post:return the total number of widgets ordered
	int getCountWidgetsOrdered()const { return countWidgetsOrdered; }

	//Pre:an order exists in pQueue
	//Post:return the latest order object added topQueue
	Order getLatestOrder() { return heapArray[length-1];}

	//Pre:NA
	//Post:Return length of queue 
	int getLength()const { return length; }

	//Pre:pQueue is initialized
    //Post:Make priority Queue empty
	void MakeEmpty();

private:
	Order heapArray[WIDGET_STOCK];
	int length;
	int orderCounter;
	int countWidgetsOrdered;
};

#endif PQUEUE_H

