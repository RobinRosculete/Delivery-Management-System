#include "PQueue.h"

void Swap(Order& parent, Order& bottom);//Helper Function

//Pre:pQueue has been initialized
//Post:A new order is added to the queue
void pQueue::Enquque(int numwidgetsOrdered, RushStatus rushStatus) {
	if (IsFull()) cout << "Order queue is full. No more order can be added" << endl;
	else {
		heapArray[length].setnumwidgetsOrdered(numwidgetsOrdered);
		heapArray[length].setRushStatus(rushStatus);
		heapArray[length].setOrderTrakingNum(orderCounter);
	
		cout << "\t***Your Order Was Received***" << endl;
		cout << setw(WIDTH_SIZE) << "Order #"
			<< setw(WIDTH_SIZE) << "Qty ordered"
			<< setw(WIDTH_SIZE) << "Rush status\n"
			<< setw(WIDTH_SIZE) << heapArray[length].getOrderTrakingNum()
			<< setw(WIDTH_SIZE) << heapArray[length].getNumwidgetsOrdered()
			<< setw(WIDTH_SIZE - 1) << rushStatusArray[heapArray[length].getRushStatus()] << endl;

		countWidgetsOrdered += numwidgetsOrdered;
		++orderCounter;
		++length;
		ReheapUp(0, length - 1);
	}
}//end Enqueue()

//Pre:pQueue has been initialized
//Post:Highest Priority element has been removed, for pQueue, a copy is returned in orderWidget
void pQueue::Dequeue(Order& orderWidget) {
	if (IsEmpty())cout << "Queue is empty, no orders are available!" << endl;
	else {
	
		orderWidget = heapArray[0];
		heapArray[0] = heapArray[length - 1];
		--length;	
		ReheapDown(0, length - 1);
	}
}//end Dequeue()

//Pre:orderArray is  initialized
//Post:Heap property is restored
void pQueue::ReheapUp(int root, int bottom) {
	int parent;	
	if (bottom > root) {
		parent = (bottom-1) / 2;
		if (heapArray[parent].getRushStatus() < heapArray[bottom].getRushStatus()) {
			Swap(heapArray[parent], heapArray[bottom]);
			ReheapUp(root, parent);
		}
	}
}//end ReheapUp()

//Pre:orderArray is  initialized
//Post:Heap property is restored
void pQueue::ReheapDown(int root, int bottom) {
	int maxChild;
	int leftChild = root * 2 + 1;
	int rightChild = root * 2 + 2;

	if (leftChild <= bottom) 
	{
		if (leftChild == bottom)
			maxChild = leftChild;

		else {
			if(heapArray[leftChild].getRushStatus() == heapArray[rightChild].getRushStatus() ){
				if (heapArray[leftChild].getOrderTrakingNum() < heapArray[rightChild].getOrderTrakingNum())
				{
					maxChild = leftChild;
				}
				else 
				{ 
					maxChild = rightChild; 
				}

			}else if (heapArray[leftChild].getRushStatus() < heapArray[rightChild].getRushStatus()) {
				{
					maxChild = rightChild; 
				}

			}
			else 
			{
				maxChild = leftChild;
			}
		}

	  if (heapArray[root].getRushStatus() == heapArray[maxChild].getRushStatus()  ) {
			if (heapArray[root].getOrderTrakingNum() > heapArray[maxChild].getOrderTrakingNum()) {
				Swap(heapArray[root], heapArray[maxChild]);
				ReheapDown(maxChild, bottom);
			}else ReheapDown(maxChild, bottom);

		}else if (heapArray[root].getRushStatus() < heapArray[maxChild].getRushStatus()) {

			Swap(heapArray[root], heapArray[maxChild]);
			ReheapDown(maxChild, bottom);
		}	
	
	}	
}//End ReheapDown()

//Pre:An order exists
//Post:return the total cost for order
double pQueue::calculateOrderPrice(Order tepmOrder) {
	return (tepmOrder.getNumwidgetsOrdered() * WIDGET_PRICE * (1 + markUpPrecentage[tepmOrder.getRushStatus()]));
}//end calculateOrderPrice()

//Pre:pQueue is initialized
//Post:Make priority Queue empty
void pQueue:: MakeEmpty() { 
	length = 0; 
	countWidgetsOrdered = 0;
}//end Makeempty()

//Pre:pQueue is initialized
//Post:return the total cost to the customer
double pQueue:: calculateTotalCostToCustomer() {
	double totalCost = 0;
	for (int x = 0; x < length; ++x) {
		totalCost += heapArray[x].getNumwidgetsOrdered() * WIDGET_PRICE * (1 + markUpPrecentage[heapArray[x].getRushStatus()]);
	}return totalCost;

}//end calculateTotalCostToCustomer()
