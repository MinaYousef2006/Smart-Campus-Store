#ifndef PRODUCTS_H
#define PRODUCTS_H
#include <iostream>
#include <string>

using namespace std;
class Resource {
    protected:
    int ID;
    string name;
    double price;
    int quantity;
    static int totalproducts;

    public:
    Resource();
    Resource(int i, string n, double p, int q);
    virtual void display() = 0;
    virtual string GetCategory() = 0;
    void restock(int amount);
    void purchase(int amount);
    void setQuantity(int amount);
    void setPrice(double p);
 
    int getId();
    int getQuantity();
    double getPrice();
    string getName();
    double getCostBurden() ;
 
    static int getTotalProducts();
    friend void comparePrice(const Resource& p1, const Resource& p2);
    friend ostream& operator<<(ostream& output, Resource& p);
    virtual ~Resource() {}
};
#endif
