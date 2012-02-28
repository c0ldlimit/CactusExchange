#include "Order.h"
#include <string>

using namespace std;

Order::Order(int orderID, int accountID, string symbol, int quantity) :
orderID(orderID), accountID(accountID), symbol(symbol), quantity(quantity)
{

}

void Order::updateQuantity(int deltaQuantity)
{
    quantity+=deltaQuantity;
}
