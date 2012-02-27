#include <iostream>
#include <map>
#include <string>
#include "Side.h"
#include "Order.h"

using namespace std;

typedef map< string,int > asdf;


int main()
{
    asdf::iterator it;
    asdf x;
    int y;
    y=55;
    y+=3;
    cout << y << endl;
    x["hello"] = 3;
    it = x.find("hellodd");
    if (it == x.end())
    {
        cout << "what" << endl;
    }


    Order order(5,6,"IBM",-400);
    Side BuySide("BUY");
    BuySide.addPriceLevel(5,order);
    cout << order.getAccountID() << endl;
    return 0;
}
