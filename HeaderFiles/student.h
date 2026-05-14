#ifndef STUDENT_H
#define STUDENT_H
#include "user.h"
using namespace std;

class Student : public User{
    public:
    Student(string n, string id);
    double applyDiscount(double subtotal) override;
    void display() override;

};
#endif