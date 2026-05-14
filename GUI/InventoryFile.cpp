#include <fstream>
#include <iostream>
#include "Book Store.h"
#include "food.h"
#include "Lab Hardware.h"
#include "InventoryFile.h"

using namespace std;


void saveInventory(vector<Resource*> items)
{
    try
    {
        ofstream file("inventory.txt");
        if (!file)
            throw runtime_error("Error: Cannot open inventory.txt for writing!");

        for (auto item : items)
        {
            if (BookStore* b = dynamic_cast<BookStore*>(item))
            {
                file << "BOOK "
                    << b->getId() << "|"
                    << b->getName() << "|"
                    << b->getPrice() << "|"
                    << b->getQuantity() << "|"
                    << b->GetAuthor() << "|"
                    << b->GetPages()
                    << endl;
            }
            else if (food* f = dynamic_cast<food*>(item))
            {
                file << "FOOD "
                    << f->getId() << "|"
                    << f->getName() << "|"
                    << f->getPrice() << "|"
                    << f->getQuantity() << "|"
                    << f->getexpire() << "|"
                    << f->getcategoryFood()
                    << endl;
            }
            else if (LabHardware* l = dynamic_cast<LabHardware*>(item))
            {
                file << "LAB "
                    << l->getId() << "|"
                    << l->getName() << "|"
                    << l->getPrice() << "|"
                    << l->getQuantity() << "|"
                    << l->getBrand() << "|"
                    << l->getWarranty()
                    << endl;
            }
        }

        file.close();
        cout << "Inventory saved successfully.\n";
    }
    catch (exception& e)
    {
        cout << "Save Error: " << e.what() << endl;
    }
}


void loadInventory(vector<Resource*>& items)
{
    try
    {
        ifstream file("inventory.txt");
        if (!file)
            throw runtime_error("No inventory file found. Starting fresh.");

        string type;
        while (file >> type)
        {
            string line;
            getline(file, line);  

            if (!line.empty() && line[0] == ' ')
                line = line.substr(1);

            
            vector<string> parts;
            stringstream ss(line);
            string token;
            while (getline(ss, token, '|'))
                parts.push_back(token);

            if (type == "BOOK" && parts.size() == 6)
            {
                int id = stoi(parts[0]);
                string nm = parts[1];
                double pr = stod(parts[2]);
                int qty = stoi(parts[3]);
                string au = parts[4];
                int pg = stoi(parts[5]);
                items.push_back(new BookStore(id, nm, pr, qty, au, pg));
            }
            else if (type == "FOOD" && parts.size() == 6)
            {
                int id = stoi(parts[0]);
                string nm = parts[1];
                double pr = stod(parts[2]);
                int qty = stoi(parts[3]);
                string exp = parts[4];
                string cat = parts[5];
                items.push_back(new food(id, nm, pr, qty, exp, cat));
            }
            else if (type == "LAB" && parts.size() == 6)
            {
                int id = stoi(parts[0]);
                string nm = parts[1];
                double pr = stod(parts[2]);
                int qty = stoi(parts[3]);
                string br = parts[4];
                int war = stoi(parts[5]);
                items.push_back(new LabHardware(id, nm, pr, qty, br, war));
            }
        }

        file.close();
        cout << "Inventory loaded. Items: " << items.size() << endl;
    }
    catch (exception& e)
    {
        cout << "Load Error: " << e.what() << endl;
    }
}


void saveOrder(Order& order)
{
    try
    {
        ofstream file("orders.txt", ios::app);
        if (!file)
            throw runtime_error("Error: Cannot open orders.txt for writing!");

        file << "===== NEW ORDER =====\n";
        file << "Customer: " << order.getCustomerName() << "\n";
        file << "Customer: " << order.getCustomerID() << "\n";
        file << "Delivery: " << order.getDeliveryType() << "\n";
        file << "Total: " << order.calculateTotal() << "\n";
        file << "=====================\n \n";

        file.close();
    }
    catch (exception& e)
    {
        cout << "Order Save Error: " << e.what() << endl;
    }
}


void loadOrders()
{
    try
    {
        ifstream file("orders.txt");
        if (!file)
            throw runtime_error("No previous orders found.");

        string line;
        cout << "\n===== ORDER HISTORY =====\n";
        while (getline(file, line))
            cout << line << endl;

        file.close();
    }
    catch (exception& e)
    {
        cout << "Load Orders Error: " << e.what() << endl;
    }
}