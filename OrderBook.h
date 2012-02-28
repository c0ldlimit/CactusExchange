#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include <string>
#include "Side.h"
#include "Order.h"

using namespace std;

class OrderBook
{
    public:
        OrderBook(string symbol);
        string getSymbol(){ return symbol; }
        int getBestBid();
        int getBestAsk();
        void appendBuyOrder(int price, Order order);
        void appendSellOrder(int price, Order order);
        int tradeBuyOrder(int price, Order order);
        int tradeSellOrder(int price, Order order);

    protected:
    private:
        string symbol;
        Side Bid;
        Side Ask;
};

#endif // ORDERBOOK_H
