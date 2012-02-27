#include <iostream>
#include <map>
#include <string>
#include "Side.h"
#include "Order.h"
#include "Participant.h"

using namespace std;


int main()
{

    Participant conway(5,444444);

    cout << conway.getCash() << endl;
    conway.addTradeTransaction("IBM",444,343);

    cout << conway.getCash() << endl;

    Order order(5,6,"IBM",-400);
    Side BuySide("BUY");
    BuySide.addPriceLevel(5,order);
    cout << order.getAccountID() << endl;
    return 0;
}
