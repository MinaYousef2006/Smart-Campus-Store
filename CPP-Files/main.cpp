#include "LoginForm.h"
#include "MainMenuForm.h"
#include "InventoryForm.h"
#include "OrderForm.h"
#include "InventoryFile.h"
#include <vector>

using namespace System;
using namespace System::Windows::Forms;
using namespace Project1;
using namespace std;

[STAThread]
int main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Load inventory
    vector<Resource*> inventory;
    loadInventory(inventory);
    if (inventory.empty()) {
        inventory.push_back(new LabHardware(101, "Oscilloscope", 1500.0, 10, "Tektronix", 24));
        inventory.push_back(new LabHardware(102, "Microscope", 800.0, 5, "Olympus", 12));
        inventory.push_back(new LabHardware(103, "3D-Printer", 2000.0, 3, "Creality", 18));
        inventory.push_back(new food(201, "Sandwich", 15.0, 50, "2026-05-20", "Cafeteria"));
        inventory.push_back(new food(202, "Orange-Juice", 10.0, 30, "2026-05-15", "Cafeteria"));
        inventory.push_back(new food(203, "Yogurt", 8.0, 20, "2026-05-18", "Dairy"));
        inventory.push_back(new BookStore(301, "Data-Structures", 120.0, 15, "Mark-Weiss", 650));
        inventory.push_back(new BookStore(302, "Operating-Systems", 95.0, 10, "Tanenbaum", 900));
        inventory.push_back(new BookStore(303, "Clean-Code", 85.0, 8, "Robert-Martin", 431));
        saveInventory(inventory);
    }

    // Users
    vector<User*> users;
    users.push_back(new Student("Mina", "20242363"));
    users.push_back(new Student("Maria", "20240438"));
    users.push_back(new Student("Shourk", "20240275"));
    users.push_back(new Staff("Khaled", "STA001"));
    users.push_back(new Staff("Mona", "STA002"));
    users.push_back(new Staff("Ali", "STA003"));

    // Login loop
    while (true) {
        LoginForm^ loginForm = gcnew LoginForm(&users);
        if (loginForm->ShowDialog() != System::Windows::Forms::DialogResult::OK)
            break;

        User* loggedUser = loginForm->loggedUser;
        int role = loginForm->role;

        // Main menu loop
        while (true) {
            MainMenuForm^ menu = gcnew MainMenuForm(loggedUser, role, &inventory, &users);
            menu->ShowDialog();

            // Check which button was clicked via tag
            if (menu->Tag == nullptr) break;

            String^ action = (String^)menu->Tag;

            if (action == "logout") break;
            else if (action == "display")
                (gcnew InventoryForm(&inventory, role, "display"))->ShowDialog();
            else if (action == "search")
                (gcnew InventoryForm(&inventory, role, "search"))->ShowDialog();
            else if (action == "add")
                (gcnew InventoryForm(&inventory, role, "add"))->ShowDialog();
            else if (action == "restock")
                (gcnew InventoryForm(&inventory, role, "restock"))->ShowDialog();
            else if (action == "compare")
                (gcnew InventoryForm(&inventory, role, "compare"))->ShowDialog();
            else if (action == "order")
                (gcnew OrderForm(loggedUser, role, &inventory))->ShowDialog();
            else if (action == "history") {
                loadOrders();
                MessageBox::Show(L"Check console for order history.", L"History",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }
    }

    for (auto item : inventory) delete item;
    for (auto u : users) delete u;

    return 0;
}