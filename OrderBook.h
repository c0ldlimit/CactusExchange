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
        orderSet* getBidOrderSet(int price);
        orderSet* getAskOrderSet(int price);
        void removeBidPriceLevel(int price);
        void removeAskPriceLevel(int price);



    protected:
    private:
        string symbol;
        Side Bid;
        Side Ask;
};

#endif // ORDERBOOK_H
