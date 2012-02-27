#ifndef SIDE_H
#define SIDE_H
#include <iostream>
#include <map>
#include <string>
#include "Order.h"

using namespace std;

typedef map< int,Order > orderSet;
typedef map< int,orderSet > priceLevel;


class Side
{
    public:
        Side(string sideName);
        string sideName;
        priceLevel levels;

        void addPriceLevel(int price, Order order);
        void removePriceLevel();

    protected:
    private:
};

#endif // SIDE_H
