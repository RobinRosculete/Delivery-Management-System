#include <iostream>
#include"mainHelper.h"

using namespace std;

int main() {
	int optionNum = DEFAULT_OPTION;
	pQueue pQueueObj;
	cout << setprecision(2)<<fixed;

	while (optionNum != QUIT) {
		optionMenu(optionNum);
		switch (optionNum)
		{
		case DISPLAY_DETAILS:displayInventoryDetails(pQueueObj);
			break;
		case RECIEVE_ORDER:receiveOrderMenu(pQueueObj);
			break;
		case CLOSE_DAY: closeDay(pQueueObj);
			break;

		case QUIT: break;
		default:
			cout << "Error, please enter an option below!" << endl;
			break;
		}
	}
}

//Pre:NA
//Post:Display option menu to screen and return optionNum
void optionMenu(int& optionNum) {
	cout << "\n\tPlease enter an option below\n\t"
		 << DISPLAY_DETAILS << ".Display inventory\n\t"
		 << RECIEVE_ORDER << ".Order\n\t"
		 << CLOSE_DAY << ".Close day\n\t"
		 << QUIT << ".Quit" << endl;
	
	if (!(cin >> optionNum)) {
		cin.clear();
		cin.ignore(2000, '\n');

	}
}//end optionMenu()

//Pre:Priority Que is initialized
//Post:Ask user for order details, add the new order to the Priority Queue
void receiveOrderMenu(pQueue &pQueueObj) {
	int numWidgetsOrdered = 0;
	int orderStatus = DEFAULT_RUSH;

	cout << "\tHow many widgets will you like to order? :";
	while (!(cin >> numWidgetsOrdered) || numWidgetsOrdered < 1) {
		cout << "Error, please enter a positive number!" << endl;
		cin.clear();
		cin.ignore(2000, '\n');
	}
	prinrushStausMenu(orderStatus);
	pQueueObj.Enquque(numWidgetsOrdered, static_cast<RushStatus>(orderStatus));
	
}//end receiveOrder()

//Pre:NA
//Post:Display the details of the inventory
void displayInventoryDetails(pQueue pQueueObj) {
	cout << setw(WIDTH_SIZE) << "Qty of widgets:"
		<< setw(WIDTH_SIZE) << "Widget Price $:\n"
		<< setw(WIDTH_SIZE) << WIDGET_STOCK - pQueueObj.getCountWidgetsOrdered()
		<< setw(WIDTH_SIZE-1) << WIDGET_PRICE << endl;
}//end displayDetailsInventory

//Pre:NA
//Post:Print deltails regarding total oreders processed for that day
void closeDay(pQueue &pQueueObj) {
	if (pQueueObj.IsEmpty())cout << "There are no oreders to process today." << endl;
	else {
		cout << "Total orders processed: " << setw(WIDTH_SIZE) << pQueueObj.getCountWidgetsOrdered()
			<< "\nTotal cost to warehouse: " << setw(WIDTH_SIZE - 1) << WIDGET_PRICE * pQueueObj.getCountWidgetsOrdered()
			<< "\nTotal pofit:" << setw(WIDTH_SIZE + 12) << pQueueObj.calculateTotalCostToCustomer() - (WIDGET_PRICE * pQueueObj.getCountWidgetsOrdered())
			<< "\nTotal cost To customer:" << setw(WIDTH_SIZE + 1) << pQueueObj.calculateTotalCostToCustomer() 
			 <<"\nInventor on Hand"<< setw(WIDTH_SIZE + 8)<< WIDGET_STOCK - pQueueObj.getCountWidgetsOrdered() << endl;
		    PrintOrders(pQueueObj);
			pQueueObj.MakeEmpty();
	}
}//End closeDay()


//Pre:An order exists 
//Post:Display all the orders in pQueue
void PrintOrders(pQueue& pQueueObj) {
	if (pQueueObj.IsEmpty()) cout << "Order  queue is empty, nothing to display!" << endl;
	else {

		int tempLength = pQueueObj.getLength();
		Order tempOrder;
		
		cout << setw(WIDTH_SIZE) << "\nOrder #:"
			<< setw(WIDTH_SIZE) << "Rush Status: "
			<< setw(WIDTH_SIZE) << "Qty shipped: "
			<< setw(WIDTH_SIZE) << "Qty ordered: "
			<< setw(WIDTH_SIZE) << "Markup %: "
			<< setw(WIDTH_SIZE) << "Cost to customer: "
			<< setw(WIDTH_SIZE) << "Cost to warehouse: "
			<< setw(WIDTH_SIZE) << "Amount markup: "
			<< setw(WIDTH_SIZE) << "Warehouse profit: " << endl;
		for (int x = 0; x < tempLength; ++x) {
			pQueueObj.Dequeue(tempOrder);
		
			cout << setw(WIDTH_SIZE - 12) << tempOrder.getOrderTrakingNum()
				<< setw(WIDTH_SIZE - 1) << rushStatusArray[tempOrder.getRushStatus()]
				<< setw(WIDTH_SIZE - 1) << tempOrder.getNumwidgetsOrdered()
				<< setw(WIDTH_SIZE) << tempOrder.getNumwidgetsOrdered()
				<< setw(WIDTH_SIZE) << setprecision(0) << markUpPrecentage[tempOrder.getRushStatus()] * 100 << "%" << setprecision(2)
				<< setw(WIDTH_SIZE) << pQueueObj.calculateOrderPrice(tempOrder)
				<< setw(WIDTH_SIZE) << tempOrder.getNumwidgetsOrdered() * WIDGET_PRICE
				<< setw(WIDTH_SIZE) << pQueueObj.calculateOrderPrice(tempOrder) - (tempOrder.getNumwidgetsOrdered() * WIDGET_PRICE)
				<< setw(WIDTH_SIZE) << pQueueObj.calculateOrderPrice(tempOrder) - (tempOrder.getNumwidgetsOrdered() * WIDGET_PRICE) << endl;

		}
	}
}//End Print Orders


//Pre:NA
//Post:Print the status options, and return the option selected
void prinrushStausMenu(int &orderStatus) {
	cout << "\tWhat rush status would you like?\n\t"
		<< STANDARD_RUSH << ". " << rushStatusArray[STANDARD_RUSH] << "\n\t"
		<< EXPEDITE_RUSH << ". " << rushStatusArray[EXPEDITE_RUSH] << "\n\t"
		<< EXTREME_RUSH << ". " << rushStatusArray[EXTREME_RUSH] << endl;

	while (!(cin >> orderStatus) || orderStatus < STANDARD_RUSH || orderStatus > EXTREME_RUSH) {
		cout << "Error, please enter an option form below!\n"
			"\tWhat rush status would you like?\n\t"
			<< STANDARD_RUSH << ". " << rushStatusArray[STANDARD_RUSH] << "\n\t"
			<< EXPEDITE_RUSH << ". " << rushStatusArray[EXPEDITE_RUSH] << "\n\t"
			<< EXTREME_RUSH << ". " << rushStatusArray[EXTREME_RUSH] << endl;
		cin.clear();
		cin.ignore(2000, '\n');
	}

}//end prinrushStausMenu()


//Pre:Order object is initialized
//Post:Swap objects
void Swap(Order& parent, Order& bottom) {
	Order tempOrder;
	tempOrder = parent;
	parent = bottom;
	bottom = tempOrder;
}//end Swap()



//Test Data

//1.Testing menu option 1.Display inventory
/*
        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
1
     Qty of widgets:    Widget Price $:
                1000               2.00

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
2
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 101                  10           Expedite

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :8
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 102                   8            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :29
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 103                  29           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
1
     Qty of widgets:    Widget Price $:
                 953               2.00

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 104                  10            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 105                  10           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 106                  10            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
1
     Qty of widgets:    Widget Price $:
                 923               2.00

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
3
Total orders processed:                   77
Total cost to warehouse:              154.00
Total pofit:                           79.60
Total cost To customer:               233.60
Inventor on Hand                         923

Order #:       Rush Status:        Qty shipped:        Qty ordered:           Markup %:   Cost to customer:  Cost to warehouse:      Amount markup:   Warehouse profit:
     102            Extreme                  8                   8                 100%               32.00               16.00               16.00               16.00
     104            Extreme                 10                  10                 100%               40.00               20.00               20.00               20.00
     106            Extreme                 10                  10                 100%               40.00               20.00               20.00               20.00
     101           Expedite                 10                  10                  40%               28.00               20.00                8.00                8.00
     103           Standard                 29                  29                  20%               69.60               58.00               11.60               11.60
     105           Standard                 10                  10                  20%               24.00               20.00                4.00                4.00

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
1
     Qty of widgets:    Widget Price $:
                1000               2.00

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
*/

//2.Testing menu option 2.Order()
/*
        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :2
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 101                   2            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :fd
Error, please enter a positive number!
3
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
ree
Error, please enter an option form below!
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
0
Error, please enter an option form below!
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
-1
Error, please enter an option form below!
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 102                   3            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 103                  10            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 104                  10           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 105                  10            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
2
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 106                  10           Expedite

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 107                  10            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit*/




/*
        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :3
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 101                   3           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :5
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 102                   5            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :2
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 103                   2            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :2
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 104                   2           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :4
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
2
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 105                   4           Expedite

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :6
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 106                   6            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :3
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
2
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 107                   3           Expedite

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :1
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 108                   1           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :7
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
2
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 109                   7           Expedite

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :5
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 110                   5           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :6
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 111                   6           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
3
Total orders processed:                   44
Total cost to warehouse:               88.00
Total pofit:                           44.00
Total cost To customer:               132.00
Inventor on Hand                         956

Order #:       Rush Status:        Qty shipped:        Qty ordered:           Markup %:   Cost to customer:  Cost to warehouse:      Amount markup:   Warehouse profit:
     102            Extreme                  5                   5                 100%               20.00               10.00               10.00               10.00
     103            Extreme                  2                   2                 100%                8.00                4.00                4.00                4.00
     106            Extreme                  6                   6                 100%               24.00               12.00               12.00               12.00
     105           Expedite                  4                   4                  40%               11.20                8.00                3.20                3.20
     107           Expedite                  3                   3                  40%                8.40                6.00                2.40                2.40
     109           Expedite                  7                   7                  40%               19.60               14.00                5.60                5.60
     101           Standard                  3                   3                  20%                7.20                6.00                1.20                1.20
     104           Standard                  2                   2                  20%                4.80                4.00                0.80                0.80
     108           Standard                  1                   1                  20%                2.40                2.00                0.40                0.40
     110           Standard                  5                   5                  20%               12.00               10.00                2.00                2.00
     111           Standard                  6                   6                  20%               14.40               12.00                2.40                2.40

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
*/






//3.Testing menu option 3.Close day
/*
        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
3
There are no oreders to process today.

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
3
There are no oreders to process today.

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
2
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 101                  10           Expedite

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 102                  10            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
2
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 103                  10           Expedite

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 104                  10            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 105                  10           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
2
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 106                  10           Expedite

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 107                  10            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 108                  10           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
3
Total orders processed:                   80
Total cost to warehouse:              160.00
Total pofit:                           92.00
Total cost To customer:               252.00
Inventor on Hand                         920

Order #:       Rush Status:        Qty shipped:        Qty ordered:           Markup %:   Cost to customer:  Cost to warehouse:      Amount markup:   Warehouse profit:
     102            Extreme                 10                  10                 100%               40.00               20.00               20.00               20.00
     104            Extreme                 10                  10                 100%               40.00               20.00               20.00               20.00
     107            Extreme                 10                  10                 100%               40.00               20.00               20.00               20.00
     101           Expedite                 10                  10                  40%               28.00               20.00                8.00                8.00
     103           Expedite                 10                  10                  40%               28.00               20.00                8.00                8.00
     106           Expedite                 10                  10                  40%               28.00               20.00                8.00                8.00
     105           Standard                 10                  10                  20%               24.00               20.00                4.00                4.00
     108           Standard                 10                  10                  20%               24.00               20.00                4.00                4.00

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
3
There are no oreders to process today.

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 109                  10           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 110                  10            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :5
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 111                   5           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :6
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 112                   6           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :7
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
2
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 113                   7           Expedite

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :7
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 114                   7           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :4
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 115                   4            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :1
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 116                   1           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
3
Total orders processed:                   50
Total cost to warehouse:              100.00
Total pofit:                           45.20
Total cost To customer:               145.20
Inventor on Hand                         950

Order #:       Rush Status:        Qty shipped:        Qty ordered:           Markup %:   Cost to customer:  Cost to warehouse:      Amount markup:   Warehouse profit:
     110            Extreme                 10                  10                 100%               40.00               20.00               20.00               20.00
     115            Extreme                  4                   4                 100%               16.00                8.00                8.00                8.00
     113           Expedite                  7                   7                  40%               19.60               14.00                5.60                5.60
     109           Standard                 10                  10                  20%               24.00               20.00                4.00                4.00
     111           Standard                  5                   5                  20%               12.00               10.00                2.00                2.00
     112           Standard                  6                   6                  20%               14.40               12.00                2.40                2.40
     114           Standard                  7                   7                  20%               16.80               14.00                2.80                2.80
     116           Standard                  1                   1                  20%                2.40                2.00                0.40                0.40

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
*/







/*
*      Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
2
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 101                  10           Expedite

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :5
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 102                   5           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :6
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 103                   6            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :4
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 104                   4           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :9
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
2
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 105                   9           Expedite

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :1
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 106                   1            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :5
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 107                   5           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :3
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
2
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 108                   3           Expedite

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :1
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 109                   1            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :6
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 110                   6           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :18
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
2
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 111                  18           Expedite

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :10
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
3
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 112                  10            Extreme

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
2
        How many widgets will you like to order? :7
        What rush status would you like?
        1. Standard
        2. Expedite
        3. Extreme
1
        ***Your Order Was Received***
             Order #         Qty ordered        Rush status
                 113                   7           Standard

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
3
Total orders processed:                   85
Total cost to warehouse:              170.00
Total pofit:                           78.80
Total cost To customer:               248.80
Inventor on Hand                         915

Order #:       Rush Status:        Qty shipped:        Qty ordered:           Markup %:   Cost to customer:  Cost to warehouse:      Amount markup:   Warehouse profit:
     103            Extreme                  6                   6                 100%               24.00               12.00               12.00               12.00
     106            Extreme                  1                   1                 100%                4.00                2.00                2.00                2.00
     109            Extreme                  1                   1                 100%                4.00                2.00                2.00                2.00
     112            Extreme                 10                  10                 100%               40.00               20.00               20.00               20.00
     101           Expedite                 10                  10                  40%               28.00               20.00                8.00                8.00
     105           Expedite                  9                   9                  40%               25.20               18.00                7.20                7.20
     108           Expedite                  3                   3                  40%                8.40                6.00                2.40                2.40
     111           Expedite                 18                  18                  40%               50.40               36.00               14.40               14.40
     102           Standard                  5                   5                  20%               12.00               10.00                2.00                2.00
     104           Standard                  4                   4                  20%                9.60                8.00                1.60                1.60
     107           Standard                  5                   5                  20%               12.00               10.00                2.00                2.00
     110           Standard                  6                   6                  20%               14.40               12.00                2.40                2.40
     113           Standard                  7                   7                  20%               16.80               14.00                2.80                2.80

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
*/


//Testing option menu with wrong input!
/*
        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
6
Error, please enter an option below!

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
f
Error, please enter an option below!

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
-2
Error, please enter an option below!

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
u
Error, please enter an option below!

        Please enter an option below
        1.Display inventory
        2.Order
        3.Close day
        4.Quit
4

C:\Users\Robin\Desktop\Scoala\Anul 2\SEM #2\CS 136\LABS\Lab 9\Debug\Lab 9.exe (process 32720) exited with code 0.
Press any key to close this window . . .
*/