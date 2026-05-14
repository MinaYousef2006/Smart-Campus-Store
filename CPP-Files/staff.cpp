#include "staff.h"
#include <iostream>
Staff::Staff(string n, string id): User(n, id)
{
}

double Staff::applyDiscount(double subtotal)
{
    return subtotal * 0.10;
}

void Staff::display()
{
    cout<< "====Staff Information======"<<endl;
    cout<< " | DiscountRate: 10%";
    User::display();
}
