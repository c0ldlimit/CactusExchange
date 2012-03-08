#include <iostream>
#include <map>
#include <string>
#include "Side.h"
#include "Order.h"
#include "Participant.h"
#include "Exchange.h"

using namespace std;

typedef map<int,int> test;

int main()
{
    Exchange Conway;
    Conway.addParticipant(1,10000);
    Conway.addParticipant(2,30000);
    Conway.addOrderBook("IBM");
    Conway.addBuyOrder(1,"IBM",103.33,44);
    Conway.addBuyOrder(2,"IBM",103.33,34);

    cout << Conway.getParticipantCash(2) << endl;

    test blah;
    test::iterator it;

    blah.insert (make_pair(3,4));
    blah.insert (make_pair(5,66));

    it = blah.begin();
    cout << (*it).second << endl;
    blah.erase(it);
    it = blah.begin();
    cout << (*it).second << endl;
    cout << (++it==blah.end()) << endl;


    return 0;
}
