#ifndef EXCHANGE_H
#define EXCHANGE_H
#include <map>
#include <string>
#include "OrderBook.h"
#include "Order.h"
#include "Participant.h"

using namespace std;

typedef map< int,Participant > participantContainer;
typedef map< string,OrderBook > orderBookContainer;

class Exchange
{
    public:
        Exchange();
        void addParticipant(int accountID, double initialCash);
        double getParticipantCash(int accountID);
        int getParticipantPosition(string symbol);
        void addBuyOrder(int accountID, string symbol, double price, int size);
        void addSellOrder(int accountID, string symbol, double price, int size);

    protected:
    private:
        participantContainer participants;
        orderBookContainer orderBooks;
};

#endif // EXCHANGE_H
