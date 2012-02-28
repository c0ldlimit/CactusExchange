#ifndef ORDER_H
#define ORDER_H
#include <string>

using namespace std;

class Order
{
    public:
        Order(int orderID, int accountID, string symbol, int quantity);
        int getOrderId() { return orderID; }
        int getAccountID() { return accountID; }
        string getSymbol() { return symbol; }
        int getQuantity() { return quantity; }
        void updateQuantity(int deltaQuantity);

    protected:
    private:
        int orderID;
        int accountID;
        string symbol;
        int quantity;
};

#endif // ORDER_H
