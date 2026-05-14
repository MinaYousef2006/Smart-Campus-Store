#ifndef FOOD_H
#define FOOD_H
using namespace std;
#include "Resource.h"
class food : public Resource{
    private:
    string expire;
    string category;

    public:
    food(int id, string n, double p,int q, string ex, string c);
    void display()  override;
    string GetCategory() override;
    string getexpire() const ;
    string getcategoryFood()  const ;
};
#endif