#include "Side.h"
#include <iostream>
#include <map>
#include <string>
#include "Order.h"

using namespace std;

Side::Side(string sideName) : sideName(sideName)
{
}

void Side::addPriceLevel(int price, Order order)
{
    levels[price].insert (make_pair(order.getOrderId(), order));
}

void Side::removePriceLevel()
{

}
