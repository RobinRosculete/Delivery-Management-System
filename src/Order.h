#ifndef ORDER_H
#define ORDER_H
#include<iostream>
using namespace std;
enum RushStatus {DEFAULT_RUSH,STANDARD_RUSH, EXPEDITE_RUSH, EXTREME_RUSH };

const string rushStatusArray[]{ "Default","Standard", "Expedite", "Extreme" };
const double markUpPrecentage[]{0, 0.2,0.4,1};//0%, 20%, 40%, 100%

const double WIDGET_PRICE = 2;
const int WIDGET_STOCK = 1000;

class Order {
public:
	Order():orderTrakingNum(0),numWidgetsOrdered(0), rushStatus(STANDARD_RUSH){}

	//Pre:An order has been initialized
    //Post:set the order status
	void setRushStatus(RushStatus orderStatus) { this->rushStatus = orderStatus; }

	//Pre:An order has been initialized
    //Post:set the num widget ordered 
	void setnumwidgetsOrdered(int numWidgetsOrdered) { this->numWidgetsOrdered = numWidgetsOrdered;}

	//Pre:An order has been initialized
	//Post:return the order traking num
	int getOrderTrakingNum()const { return orderTrakingNum; }

	//Pre:An order has been initialized
    //Post:return number of widgets ordere
	int getNumwidgetsOrdered()const { return numWidgetsOrdered; }

	//Pre:An order has been initialized
    //Post:return the order Status!
	RushStatus getRushStatus()const { return rushStatus; }
    
	void setOrderTrakingNum(int ordertrakingNum);
private:
	int orderTrakingNum;
	int numWidgetsOrdered;
	RushStatus rushStatus;
};
#endif ORDER_H

