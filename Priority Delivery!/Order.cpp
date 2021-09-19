#include"Order.h"

//Pre:An order exists
//Post: Set an order traking, base traking number is 100
void Order::setOrderTrakingNum(int orderTrakingNum)
{	const int baseTrakingNum = 101;
	this->orderTrakingNum = orderTrakingNum + baseTrakingNum;
}//End setOrderTrakingNum()


