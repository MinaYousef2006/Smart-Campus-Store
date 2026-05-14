#ifndef STAFF_H
#define STAFF_H
#include "user.h"
using namespace std;

class Staff : public User{
    public:
    Staff(string n, string id);
    double applyDiscount(double subtotal) override;
    void display() override;

};
#endif