#include "OrderItem.h"
#include <iostream>

using namespace std;

Resource* OrderItem::getItem()
{
    return item;
}

int OrderItem::getQuantity()
{
    return quantity;
}

OrderItem::OrderItem(Resource* i, int q)
{
    item = i;
    quantity = q;
}

double OrderItem::getTotal()
{
    return item->getPrice() * quantity;
}

void OrderItem::display()
{
    cout << item->getName()
         << " | Quantity: " << quantity
         << " | Total Price: " << getTotal()
         << endl;
}