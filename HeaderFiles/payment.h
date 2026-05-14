#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
#include <string>

using namespace std;

class Payment{

protected:
    double amount;

public:
    Payment(double a);

    virtual void pay() = 0;

    virtual ~Payment() {}
};

class CashPayment : public Payment{

public:
    CashPayment(double a);

    void pay() override;
};

class CardPayment : public Payment{

private:
    string cardNumber;

public:
    bool isValidCard(const string& card);
    CardPayment(double a, string c);

    void pay() override;
};

#endif