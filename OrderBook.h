#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include <string>
#include "Side.h"

using namespace std;

class OrderBook
{
    public:
        OrderBook(string symbol);
        string getSymbol(){ return symbol; }
    protected:
    private:
        string symbol;
        Side Bid;
        Side Ask;
};

#endif // ORDERBOOK_H
