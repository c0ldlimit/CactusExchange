#include "Exchange.h"
#include <map>
#include <string>
#include <algorithm>
#include "OrderBook.h"
#include "Order.h"
#include "Participant.h"

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
    if (it == orderBooks.end()) // new symbol, create new order book
    {
        orderBooks.insert (make_pair(symbol,OrderBook(symbol)));
    }
    else
    { // TODO not sure how to encapsulate when we also need to update Participant objects
        orderBookPtr = &(it->second);
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
                        // remove order
                    }
                    (*lastOrderPtr).updateQuantity(tradeQty); // update order
                    updateParticipant(accountID,symbol,tradeQty,price); // update buyer
                    updateParticipant((*lastOrderPtr).getAccountID(),symbol,-tradeQty,price); //update seller
                    ++itOrderSet;
                }
                lastBestAskPrice = orderBookPtr->getBestAsk();
                lastOrderSetPtr = orderBookPtr->getAskOrderSet(lastBestAskPrice);
            }
            // if unallocatedQty !=0 then add to bid book


        }

    }


    // if bid > best offer then trade will occur
    // start with best offer

}
