#include "Exchange.h"
#include <map>
#include <string>
#include <algorithm>
#include "OrderBook.h"
#include "Order.h"
#include "Participant.h"
#include <list>




Exchange::Exchange()
{
    //ctor
}

void Exchange::addOrderBook(string symbol)
{
    orderBooks.insert (make_pair(symbol,OrderBook(symbol)));
}

void Exchange::addParticipant(int accountID, double initialCash)
{
    participants.insert (make_pair(accountID, Participant(accountID,initialCash)));
}

double Exchange::getParticipantCash(int accountID)
{
    participantContainer::iterator it;
    it = participants.find(accountID);
    if (it != participants.end())
    {
        return (it->second).getCash();
    }
    else
    {
        return 0.0;
    }
}


int Exchange::getParticipantPosition(int accountID, string symbol)
 {
     Participant* participantPtr;

     participantContainer::iterator it;
     it = participants.find(accountID);
     if (it != participants.end())
     {
        participantPtr = &(it->second);
        return (*participantPtr).getSymbolQuantity(symbol);
     }
     else
     {
        return 0; // participant does not exist!
     }


 }

 void Exchange::updateParticipant(int accountID, string symbol, int deltaQuantity, double tradePrice)
{
    Participant* participantPtr;

    participantContainer::iterator it;
    it = participants.find(accountID);
    if (it != participants.end())
    {
        participantPtr = &(it->second);
        (*participantPtr).addTradeTransaction(symbol,deltaQuantity,tradePrice);
    }
    else
    {
       // exception: participant does not exist!
    }
}


void Exchange::addBuyOrder(int accountID, string symbol, double price, int quantity)
{
    Order newOrder(accountID,symbol,quantity);
    int intPrice = int(price*100);

    OrderBook* orderBookPtr;
    orderBookContainer::iterator it;
    it = orderBooks.find(symbol);
    orderBookPtr = &(it->second);
    if (it == orderBooks.end()) // new symbol, create new order book
    {
        orderBooks.insert (make_pair(symbol,OrderBook(symbol)));
        orderBookPtr->appendBuyOrder(intPrice,newOrder);
    }
    else
    { // TODO not sure how to encapsulate when we also need to update Participant objects

        if (intPrice < orderBookPtr->getBestAsk() ) // add to top of order book
        {
            orderBookPtr->appendBuyOrder(intPrice,newOrder);
        }
        else // trade
        {
            orderSet* lastOrderSetPtr;
            Order* lastOrderPtr;
            int lastBestAskPrice;
            orderSet::iterator itOrderSet;
            list<int> ordersToRemove;

            // intialized loop vars
            int unallocatedQty = quantity;
            int tradeQty;
            lastBestAskPrice = orderBookPtr->getBestAsk();
            lastOrderSetPtr = orderBookPtr->getAskOrderSet(lastBestAskPrice);

            while(lastBestAskPrice!=-1 && unallocatedQty!=0 && lastBestAskPrice<=intPrice) // iterate through price levels
            {
                // TODO How do I make priceLevel and orderSet "read-only"?
                itOrderSet = (*lastOrderSetPtr).begin();
                while(itOrderSet != (*lastOrderSetPtr).end() && unallocatedQty!=0) // iterate through orders
                {
                    lastOrderPtr = &(*itOrderSet).second;
                    if (abs(unallocatedQty) < abs((*lastOrderPtr).getQuantity()))
                    {
                        tradeQty = unallocatedQty;
                        unallocatedQty = 0;
                    }
                    else
                    {
                        tradeQty = -(*lastOrderPtr).getQuantity();
                        unallocatedQty -= tradeQty;
                        ordersToRemove.push_front(itOrderSet->first);
                    }
                    (*lastOrderPtr).updateQuantity(tradeQty); // update order
                    updateParticipant(accountID,symbol,tradeQty,price); // update buyer
                    updateParticipant((*lastOrderPtr).getAccountID(),symbol,-tradeQty,price); //update seller
                    ++itOrderSet;
                }
                eraseOrders(lastOrderSetPtr,ordersToRemove); // erase depleted orders
                ordersToRemove.clear();

                if (itOrderSet == (*lastOrderSetPtr).end()) // depleted price level
                {
                    orderBookPtr->removeAskPriceLevel(lastBestAskPrice);
                }
                lastBestAskPrice = orderBookPtr->getBestAsk();
                lastOrderSetPtr = orderBookPtr->getAskOrderSet(lastBestAskPrice);
            }

            if (unallocatedQty != 0) // remaining quantity add to order book
            {
                newOrder.updateQuantity(unallocatedQty-newOrder.getQuantity());
                orderBookPtr->appendBuyOrder(intPrice,newOrder);
            }


        }

    }

}

void Exchange::addSellOrder(int accountID, string symbol, double price, int quantity)
{

    Order newOrder(accountID,symbol,quantity);
    int intPrice = int(price*100);

    OrderBook* orderBookPtr;
    orderBookContainer::iterator it;
    it = orderBooks.find(symbol);
    orderBookPtr = &(it->second);
    if (it == orderBooks.end()) // new symbol, create new order book
    {
        orderBooks.insert (make_pair(symbol,OrderBook(symbol)));
        orderBookPtr->appendSellOrder(intPrice,newOrder);
    }
    else
    { // TODO not sure how to encapsulate when we also need to update Participant objects

        if (intPrice > orderBookPtr->getBestAsk() ) // add to top of order book
        {
            orderBookPtr->appendSellOrder(intPrice,newOrder);
        }
        else // trade
        {
            orderSet* lastOrderSetPtr;
            Order* lastOrderPtr;
            int lastBestBidPrice;
            orderSet::iterator itOrderSet;
            list<int> ordersToRemove;

            // intialized loop vars
            int unallocatedQty = quantity;
            int tradeQty;
            lastBestBidPrice = orderBookPtr->getBestAsk();
            lastOrderSetPtr = orderBookPtr->getBidOrderSet(lastBestBidPrice);

            while(lastBestBidPrice!=-1 && unallocatedQty!=0 && lastBestBidPrice>=intPrice) // iterate through price levels
            {
                // TODO How do I make priceLevel and orderSet "read-only"?
                itOrderSet = (*lastOrderSetPtr).begin();
                while(itOrderSet != (*lastOrderSetPtr).end() && unallocatedQty!=0) // iterate through orders
                {
                    lastOrderPtr = &(*itOrderSet).second;
                    if (abs(unallocatedQty) < abs((*lastOrderPtr).getQuantity()))
                    {
                        tradeQty = unallocatedQty;
                        unallocatedQty = 0;
                    }
                    else
                    {
                        tradeQty = -(*lastOrderPtr).getQuantity();
                        unallocatedQty -= tradeQty;
                        //(*lastOrderSetPtr).erase(itOrderSet); // remove order
                    }

                    (*lastOrderPtr).updateQuantity(tradeQty); // update order
                    updateParticipant(accountID,symbol,tradeQty,price); // update seller
                    updateParticipant((*lastOrderPtr).getAccountID(),symbol,-tradeQty,price); //update buyer
                    ++itOrderSet;
                }
                eraseOrders(lastOrderSetPtr,ordersToRemove); // erase depleted orders
                ordersToRemove.clear();
                if (itOrderSet == (*lastOrderSetPtr).end()) // depleted price level
                {
                    orderBookPtr->removeBidPriceLevel(lastBestBidPrice);
                }
                lastBestBidPrice = orderBookPtr->getBestBid();
                lastOrderSetPtr = orderBookPtr->getBidOrderSet(lastBestBidPrice);
            }


            if (unallocatedQty != 0) // remaining quantity add to order book
            {
                newOrder.updateQuantity(unallocatedQty-newOrder.getQuantity());
                orderBookPtr->appendBuyOrder(intPrice,newOrder);
            }


        }

    }

}


void Exchange::eraseOrders(orderSet* orderSetPtr, list<int> orderList)
{
    list<int>::iterator it;

    for(it=orderList.begin(); it!=orderList.end(); ++it)
    {
        (*orderSetPtr).erase(*it);
    }
}

