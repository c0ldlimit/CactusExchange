#include "Exchange.h"
#include <map>
#include <string>
#include "OrderBook.h"
#include "Order.h"
#include "Participant.h"

Exchange::Exchange() : orderID(0)
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

void Exchange::addBuyOrder(int accountID, string symbol, double price, int quantity)
{
    Order newOrder(++orderID,accountID,symbol,quantity);
    int intPrice = int(price*100);

    OrderBook* orderBookPtr;
    orderBookContainer::iterator it;
    it = orderBooks.find(symbol);
    if (it == orderBooks.end()) // new symbol
    {
        orderBooks.insert (make_pair(symbol,OrderBook(symbol)));
    }
    else
    {
        orderBookPtr = &(it->second);
        if (intPrice < orderBookPtr->getBestAsk() ) // add to order book
        {
            orderBookPtr->appendBuyOrder(intPrice,newOrder);
        }
        else // trade
        {
            orderBookPtr->tradeBuyOrder(intPrice,newOrder);
        }

    }


    // if bid > best offer then trade will occur
    // start with best offer

}
