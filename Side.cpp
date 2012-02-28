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

void Side::removePriceLevel(int price)
{
    priceLevel::iterator it;
    it = levels.find(price);
    if (it != levels.end())
    {
        levels[price].erase (price);
    }

}

void Side::updatePriceLevel(int price, Order order)
{
    priceLevel::iterator it;
    it = levels.find(price);
    if (it != levels.end())
    {
        levels[price].insert (make_pair(order.getOrderId(), order));
    }

}


int Side::getMaxPrice()
{
    if (levels.empty())
    {
        return -1;
    }
    else
    {
        return (levels.rbegin())->first;
    }

}

int Side::getMinPrice()
{
    if (levels.empty())
    {
        return -1;
    }
    else
    {
        return (levels.begin())->first;
    }

}
