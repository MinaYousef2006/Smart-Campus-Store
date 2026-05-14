#include "Lab Hardware.h"

LabHardware::LabHardware(int id, string n, double p, int q, string br, int w)
    :Resource(id, n, p, q)
{
    brand = br;
    warranty = w;
}

void LabHardware::display()
{
    cout<<"Lab Device ID: " << ID
        << " | Name: " << name
        << " | Price: " << price << " EGP"
        << " | Stock: " << quantity
        << " | Brand: " << brand
        << " | Warranty: " << warranty<<endl;
}

string LabHardware::GetCategory()
{
    return "Lab HardWare";
}

int LabHardware::getWarranty() const
{
    return warranty;
}

string LabHardware::getBrand() const
{
    return brand;
}
