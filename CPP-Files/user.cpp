#include "user.h"
#include <iostream>
using namespace std;


User::User(string n, string id)
{
    name = n ;
    campusID = id;
}

string User::getName()
{
    return name;
}

string User::getCampusID()
{
    return campusID;
}

double User::applyDiscount(double subtotal)
{
    return subtotal;
}

void User::display()
{
    cout<< " | Name: " << name
        << " | CampusID: " << campusID<< endl;
}
