#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include "OrderItem.h"
#include "user.h"

using namespace std;

class Order{

private:
    vector<OrderItem> items;

    User* customer;

    string deliveryType;

public:
    Order(User* u, string d);

    void addItem(Resource* item, int quantity);

    double calculateTotal();

    void displayOrder();

    string getCustomerName();   
    string getCustomerID();   

    string getDeliveryType(); 

    ~Order();
};

#endif