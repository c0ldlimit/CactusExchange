#include "Exchange.h"
#include <map>
#include <string>
#include "OrderBook.h"
#include "Order.h"
#include "Participant.h"

Exchange::Exchange()
{
    //ctor
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

