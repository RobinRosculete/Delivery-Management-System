#ifndef MAINHELPER_H
#define MAINHELPER_H
enum OptioMenu { DEFAULT_OPTION, DISPLAY_DETAILS, RECIEVE_ORDER, CLOSE_DAY, QUIT };
#include "pQueue.h"
void optionMenu(int& optionNum);
void receiveOrderMenu(pQueue& pQueueObj);
void displayInventoryDetails(pQueue pQueueObj);
void closeDay(pQueue& pQueueObj);
void prinrushStausMenu(int& orderStatus);
void Swap(Order& parent, Order& bottom);
void PrintOrders(pQueue& pQueueObj);
#endif MAINHELPER_H

