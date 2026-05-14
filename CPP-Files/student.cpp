#include "student.h"
#include <iostream>
Student::Student(string n, string id): User(n, id)
{
}

double Student::applyDiscount(double subtotal)
{
    return 0;
}

void Student::display()
{
    cout<< "====Student Information======"<<endl;
    User::display();
}
