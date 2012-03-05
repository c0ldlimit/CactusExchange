#include <iostream>
#include <map>
#include <string>
#include "Side.h"
#include "Order.h"
#include "Participant.h"
#include "Exchange.h"

using namespace std;



int main()
{
    Exchange Conway;
    Conway.addParticipant(1,10000);
    Conway.addParticipant(2,30000);
    Conway.addOrderBook("IBM");
    Conway.addBuyOrder(1,"IBM",103.33,44);
    Conway.addBuyOrder(2,"IBM",103.33,34);


    cout << Conway.getParticipantCash(2) << endl;

    return 0;
}
