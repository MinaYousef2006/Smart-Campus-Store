#include "Order.h"
#include "OrderItem.h"
#include "Resource.h"
#include "user.h"
#include <iostream>

using namespace std;

Order::Order(User* u, string d)
{
    customer = u;
    deliveryType = d;
}

void Order::addItem(Resource* item, int quantity)
{
    try{

        OrderItem newItem(item, quantity);

        items.push_back(newItem);
    }

    catch(exception& e){
        cout << e.what() << endl;
    }
}

double Order::calculateTotal()
{
    double total = 0;

    for(auto item : items){
        total += item.getTotal();
    }

    total = total - customer->applyDiscount(total);

    if(deliveryType == "delivery"){
        total += 50;
    }

    return total;
}

void Order::displayOrder()
{
    cout << "\n===== ORDER DETAILS =====\n";

    customer->display();

    cout << "\nItems:\n";

    for(auto item : items){
        item.display();
    }

    if(deliveryType == "delivery"){
        cout << "\nDelivery Fee: 50\n";
    }
    else{
        cout << "\nPickup Selected\n";
    }

    cout << "\nFinal Total: "
         << calculateTotal()
         << endl;
}

string Order::getCustomerName() {
    return customer->getName();
}

string Order::getCustomerID()
{
    return customer->getCampusID();
}

string Order::getDeliveryType() {
    return deliveryType;
}

Order::~Order() {  }
