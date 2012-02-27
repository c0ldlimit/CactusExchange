#include <iostream>
#include <map>
#include <string>
#include "Side.h"
#include "Order.h"
#include "Participant.h"

using namespace std;


int main()
{
    Order order(5,6,"IBM",-400);
    Side BuySide("BUY");
    BuySide.addPriceLevel(5,order);
    cout << order.getSymbol() << endl;
    BuySide.removePriceLevel(6);
    cout << order.getSymbol() << endl;
    return 0;
}
