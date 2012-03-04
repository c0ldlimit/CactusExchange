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

        void addPriceLevel(int price, Order order);
        void removePriceLevel(int price);
        void updatePriceLevel(int price, Order order);
        string getSideName(){ return sideName; }
        int getMaxPrice();
        int getMinPrice();
        orderSet* getOrderSet(int price);

    protected:
    private:
        string sideName;
        priceLevel levels;
};

#endif // SIDE_H
