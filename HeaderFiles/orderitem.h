#ifndef ORDERITEM_H
#define ORDERITEM_H

#include "Resource.h"

class OrderItem{

private:
    Resource* item;
    int quantity;
    Resource* getItem();
    int getQuantity();
public:
    OrderItem(Resource* i, int q);
    
    double getTotal();

    void display();
};

#endif