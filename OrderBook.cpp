#include "OrderBook.h"
#include <string>
#include "Side.h"
#include "Order.h"

using namespace std;

OrderBook::OrderBook(string symbol) : symbol(symbol), Bid("BID"), Ask("ASK")
{
}


int OrderBook::getBestBid()
{
    return Bid.getMaxPrice();
}

int OrderBook::getBestAsk()
{
    return Ask.getMinPrice();
}

void OrderBook::appendBuyOrder(int price, Order order)
{
    if (price>Bid.getMaxPrice()) // new price level
    {
        Bid.addPriceLevel(price,order);
    }
    else // add order to existing price level
    {
        Bid.updatePriceLevel(price,order);
    }

}

void OrderBook::appendSellOrder(int price, Order order)
{
    if (price<Ask.getMinPrice()) // new price level
    {
        Ask.addPriceLevel(price,order);
    }
    else
    {
        Ask.updatePriceLevel(price,order);
    }

}

orderSet* OrderBook::getBidOrderSet(int price)
{
    return Bid.getOrderSet(price);
}

orderSet* OrderBook::getAskOrderSet(int price)
{
    return Ask.getOrderSet(price);
}
