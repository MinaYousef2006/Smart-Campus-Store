#include "Payment.h"

Payment::Payment(double a)
{
    amount = a;
}

CashPayment::CashPayment(double a)
    : Payment(a)
{
}

void CashPayment::pay()
{
    cout << "Cash Payment Successful!" << endl;
    cout << "Amount Paid: " << amount << endl;
}

bool CardPayment::isValidCard(const string &card)
{
    if (card.length() != 16) {
        cout << "Card number must be exactly 16 digits!\n";
        return false;
    }
    for (char c : card) {
        if (!isdigit(c)) {
            cout << "Card must contain digits only!\n";
            return false;
        }
    }
    return true;
}

CardPayment::CardPayment(double a, string c)
    : Payment(a)
{
    cardNumber = c;
}


void CardPayment::pay()
{
    try {

       do {
        cout << "Enter Card Number (16 digits): ";
        cin >> cardNumber;
    } while (!isValidCard(cardNumber)); 

    cout << "Card Payment Successful!\n";
    cout << "Amount Paid: " << amount << "\n";
    }

    catch (runtime_error& e) {
        cout << e.what() << endl;
    }
}