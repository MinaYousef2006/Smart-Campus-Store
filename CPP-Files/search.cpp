#include "search.h"

search::search(vector<Resource*>& inventory)
{
    items = inventory;
}

void search::searchId(int id)
{
    bool found = false;
    for (auto item : items) {
        if (item->getId() == id) {
            cout << "\n--- current Stock ---" << endl;
            cout << "Name:     " << item->getName() << endl;
            cout << "Price:    $" << item->getPrice() << endl;
            cout << "Stock:    " << item->getQuantity() << " units" << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Error: Resource with ID " << id << " not found!" << endl;
    }
}