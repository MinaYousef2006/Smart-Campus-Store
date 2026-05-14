#include "food.h"

food::food(int id, string n, double p, int q, string ex, string c)
    :Resource(id, n, p, q)
{
    expire = ex;
    category = c;
}

void food::display()
{
    cout<<"Food ID: " << ID
        << " | Name: " << name
        << " | Price: " << price << " EGP"
        << " | Stock: " << quantity
        << " | ExpireDate: " << expire
        << " | Category: " << category<<endl;
}

string food::GetCategory()
{
    return "Food";
}

string food::getexpire() const
{
    return expire;
}

string food::getcategoryFood() const
{
    return category;
}
