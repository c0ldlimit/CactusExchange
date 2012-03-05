#include "Order.h"
#include <string>

using namespace std;

Order::Order(int accountID, string symbol, int quantity) :
accountID(accountID), symbol(symbol), quantity(quantity)
{
    orderID = ++lastOrderID;
}

void Order::updateQuantity(int deltaQuantity)
{
    quantity+=deltaQuantity;
}

int Order::lastOrderID = 0;
