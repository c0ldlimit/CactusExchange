#ifndef PARTICIPANT_H
#define PARTICIPANT_H
#include <string>
#include <map>

using namespace std;

typedef map< string,int > positionMap;  // TODO use unordered_map

class Participant
{
    public:
        Participant(int accountID, double cash);
        double getCash(){ return cash; }
        int getAccountID(){ return accountID; }
        void addTradeTransaction(string symbol, int quantity, double tradePrice);
    protected:
    private:
        int accountID;
        double cash;
        positionMap positions;


};

#endif // PARTICIPANT_H
