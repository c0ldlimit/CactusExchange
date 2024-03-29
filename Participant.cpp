#include "Participant.h"
#include <string>
#include <map>

using namespace std;

Participant::Participant(int accountID, double cash) : accountID(accountID), cash(cash)
{
    //ctor
}


void Participant::addTradeTransaction(string symbol, int quantity, double tradePrice)
{
    double tradeCash;

    positionMap::iterator it;
    it = positions.find(symbol);
    if (it == positions.end())
    {
        positions.insert (make_pair(symbol,quantity)); // if not existing position add new position
    }
    else // position exists
    {
        positions[symbol] += quantity; // if existing adjust position
        if (positions[symbol] == 0)
        {
            positions.erase (symbol); // if position becomes zero, delete position
        }
    }

    tradeCash = quantity*tradePrice;
    cash -= tradeCash; // cash changes in the opposite direction of quantity
}

int Participant::getSymbolQuantity(string symbol)
{
    positionMap::iterator it;
    it = positions.find(symbol);
    if (it == positions.end())
    {
        return 0;
    }
    else
    {
        return positions[symbol];
    }

}
