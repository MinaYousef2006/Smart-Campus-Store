#include <fstream>
#include "Resource.h"

int Resource::totalproducts = 0;
Resource::Resource() {}
Resource::Resource(int id, string n, double p, int q)
{
    ID = id;
    name = n;
    price = p;
    quantity = q;
    totalproducts++;
}

void Resource::restock(int amount)
{
    if (amount <= 0)
        throw invalid_argument("Restock amount must be positive!");
    quantity += amount;

}

void Resource::purchase(int amount)
{
    if (amount < 0){
        throw invalid_argument("Quantity can not be negative!.. choose at least one");
    }
    else if(amount > quantity){
        cout<< "NOTE!! Avaliable Quantity:"<< getQuantity() << endl;
        throw runtime_error ("SORRY! Not Enough Stock") ;
    }
    else if(amount == 0){
        throw runtime_error ("SORRY! You must buy at least ONE Stock") ;
    }
    else{
        quantity -= amount;
        cout << "Purchase successful" <<endl;
        cout<< "Remaining Quantity: "<< getQuantity()<< endl;
    }
}

void Resource::setQuantity(int amount)
{
    quantity = amount;
}

void Resource::setPrice(double p)
{
    price = p;
}

int Resource::getId()
{
    return ID;
}

int Resource::getQuantity()
{
    return quantity;
}

double Resource::getPrice()
{
    return price;
}

string Resource::getName()
{
    return name;
}

double Resource::getCostBurden()
{
    return price * quantity;;
}

int Resource::getTotalProducts()
{
    return totalproducts;
}

void comparePrice(const Resource &p1, const Resource &p2)
{
    double cost1 = p1.price * p1.quantity;
    double cost2 = p2.price * p2.quantity;
    cout << p1.name << " cost burden: " << cost1 << endl;
    cout << p2.name << " cost burden: " << cost2 << endl;
    if (cost1 > cost2)
        cout << ">>> " << p1.name << " has higher cost burden." << endl;
    else if (cost2 > cost1)
        cout << ">>> " << p2.name << " has higher cost burden." << endl;
    else
        cout << ">>> Both have the same cost burden." << endl;
}
ostream &operator<<(ostream &output, Resource &p)
{
    output << p.ID << " " << p.name << " " << p.price << " " << p.quantity;
    return output;
}
