#ifndef USER_H
#define USER_H
using namespace  std;
#include <string>
class User{
    protected:
    string name;
    string campusID;
public:
    User(string n, string id);
    string getName();
    string getCampusID();
    virtual double applyDiscount(double subtotal);
    virtual void display();
    virtual ~User() {}
};

#endif