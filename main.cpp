#include <iostream>
#include <map>
#include <string>
#include "Side.h"
#include "Order.h"
#include "Participant.h"
#include "Exchange.h"

using namespace std;

typedef map<int,int> test;
typedef map< string,int > test2;

int main()
{
    //Participant Conway(1,3000);
    //Conway.addTradeTransaction("IBM",3,32.33);
    //cout << Conway.getSymbolQuantity("IBM");

    Exchange Cactus;
    Cactus.addParticipant(1,10000.0); // add participant 1
    Cactus.addParticipant(2,30000.0); // add participant 2
   // Cactus.updateParticipant(2,"IBM",5,100);
    Cactus.addParticipant(3,20000.0); // add participant 3
    Cactus.addOrderBook("IBM");  // add IBM order book
    Cactus.addOrderBook("JNJ"); // add JNJ order book

    cout << "Initial 1 " << Cactus.getParticipantCash(1) << endl;
    cout << "Initial 2 " << Cactus.getParticipantCash(2) << endl;
    cout << "Initial 3 " << Cactus.getParticipantCash(3) << endl;

    Cactus.addSellOrder(3,"IBM", 100.0,-5);
    Cactus.addBuyOrder(1,"IBM",99.0,8); // add buy order
    Cactus.addBuyOrder(2,"IBM",100.0,10); // add buy order - 2 will trade with 3 and add 11 to a new bid level


    cout << "New 1 " << Cactus.getParticipantCash(1) << endl;
    cout << "New 2 " << Cactus.getParticipantCash(2) << endl; // should -500
    cout << "New 3 " << Cactus.getParticipantCash(3) << endl; // should be +500
    cout << "3 IBM position " << Cactus.getParticipantPosition(3,"IBM") << endl; // should be short 5
    cout << "2 IBM position " << Cactus.getParticipantPosition(2,"IBM") << endl; // should be long 5


    return 0;
}
