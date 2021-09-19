#include "Heap.h"

//Helper functions
void Swap(Order& parent, Order& bottom);



void pQueue::Print() {

	cout << "Printing " << endl;
	cout << numElements;
	Heapify();
	for (int x = 0; x < numElements; ++x) {

		cout << "\nTraking Number: " << orderArray[x].getOrderTrakingNum()
			 << "\nQuantity ordered: " << orderArray[x].getNumwidgetsOrdered()
			 << "\nRush Status: " << rushStatusArra[orderArray[x].getOrderStatus()] << endl;
	}

}

//Pre:Order object is initialized
//Post:Swap objects
void Swap(Order& parent, Order& bottom) {
	Order tempOrder;

	tempOrder = parent;
	parent = bottom;
	bottom = tempOrder;
}//end Swap()

//Pre:
//Post:
void pQueue::addOrder(Order newOrder) {
	orderArray[numElements] = newOrder;
	++numElements;
}//end addOrder()

//Pre:Heap is  initialized
//Post:Heap property is restored
void pQueue::ReheapUp(int root, int bottom) {
	int parent;
	if (bottom > root) {
		parent = (bottom - 1) / 2;
		if (orderArray[parent].getOrderStatus() < orderArray[bottom].getOrderStatus()) {

			Swap(orderArray[parent], orderArray[bottom]);
			ReheapUp(root, parent);
		}

	}


}//end ReheapUp()

//Pre:orderArray is initialized
//Post:turn orderArray into a heap 
void pQueue::Heapify() {
	int index = 0;
	for (index = numElements / 2 - 1; index >= 0; index--) {

		ReheapDown(index, numElements - 1);
	}


}// end Heapify()


//Pre:Heap is  initialized
//Post:Heap property is restored
void pQueue::ReheapDown(int root, int bottom) {
	int maxChild;
	int rightChild = root * 2 + 2;
	int leftChild = root * 2 + 1;
	if (leftChild <= bottom) {
		maxChild = leftChild;
	}
	else {
		if (orderArray[leftChild].getOrderStatus() <= orderArray[rightChild].getOrderStatus()) {
			maxChild = rightChild;
		}
		else
		{
			maxChild = leftChild;
		}

		if (orderArray[root].getOrderStatus() < orderArray[maxChild].getOrderStatus()) {

			Swap(orderArray[root], orderArray[maxChild]);
			ReheapDown(maxChild, bottom);
		}

	}


}//End ReheapDown()