#ifndef LAB_HARDWARE_H
#define LAB_HARDWARE_H
#include "Resource.h"
using namespace std;
class LabHardware: public Resource{
    private:
    string brand;
    int warranty;

    public:
    LabHardware(int id, string n, double p,int q, string br, int wMonths);
    void display()  override;
    string GetCategory() override;
    int getWarranty() const ;
    string getBrand()  const ;
};
#endif