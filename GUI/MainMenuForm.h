#pragma once
#include "user.h"
#include "student.h"
#include "staff.h"
#include "Resource.h"
#include "Book Store.h"
#include "food.h"
#include "Lab Hardware.h"
#include "InventoryFile.h"
#include <vector>
#using <System.Windows.Forms.dll>
#using <System.dll>
#using <System.Drawing.dll>

namespace Project1 {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace std;

    public ref class MainMenuForm : public Form {
    public:
        vector<User*>* users;
        vector<Resource*>* inventory;
        User* loggedUser;
        int role;

        MainMenuForm(User* u, int r, vector<Resource*>* inv, vector<User*>* us) {
            loggedUser = u;
            role = r;
            inventory = inv;
            users = us;
            InitializeComponent();
            UpdateWelcome();
        }

    private:
        Label^ lblWelcome;
        Label^ lblRole;
        Button^ btnDisplay;
        Button^ btnSearch;
        Button^ btnOrder;
        Button^ btnHistory;
        Button^ btnAdd;
        Button^ btnRestock;
        Button^ btnCompare;
        Button^ btnLogout;

        void InitializeComponent() {
            this->Text = L"Smart Campus - Main Menu";
            this->Size = Drawing::Size(420, 600);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::FromArgb(245, 247, 250);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;

            // Welcome
            lblWelcome = gcnew Label();
            lblWelcome->Font = gcnew Drawing::Font("Segoe UI", 14, FontStyle::Bold);
            lblWelcome->ForeColor = Color::FromArgb(30, 80, 160);
            lblWelcome->Size = Drawing::Size(380, 35);
            lblWelcome->Location = Drawing::Point(20, 20);
            lblWelcome->TextAlign = ContentAlignment::MiddleCenter;

            lblRole = gcnew Label();
            lblRole->Font = gcnew Drawing::Font("Segoe UI", 10);
            lblRole->ForeColor = Color::Gray;
            lblRole->Size = Drawing::Size(380, 25);
            lblRole->Location = Drawing::Point(20, 55);
            lblRole->TextAlign = ContentAlignment::MiddleCenter;

            // Buttons
            btnDisplay = CreateButton(L"Display Resources", Color::FromArgb(30, 80, 160));
            btnSearch = CreateButton(L"Search Resource", Color::FromArgb(30, 80, 160));
            btnOrder = CreateButton(L"Create Order", Color::FromArgb(30, 80, 160));
            btnHistory = CreateButton(L"View Orders History", Color::FromArgb(0, 140, 80));
            btnAdd = CreateButton(L"Add Resource", Color::FromArgb(0, 140, 80));
            btnRestock = CreateButton(L"Restock Resource", Color::FromArgb(0, 140, 80));
            
            btnCompare = CreateButton(L"Compare Resources", Color::FromArgb(30, 80, 160));
            btnLogout = CreateButton(L"Logout", Color::FromArgb(180, 40, 40));

            // Positions
            btnDisplay->Location = Drawing::Point(90, 100);
            btnSearch->Location = Drawing::Point(90, 155);
            btnOrder->Location = Drawing::Point(90, 210);
            btnHistory->Location = Drawing::Point(90, 430);
            btnAdd->Location = Drawing::Point(90, 320);
            btnRestock->Location = Drawing::Point(90, 375);
            btnCompare->Location = Drawing::Point(90, 265);
            btnLogout->Location = Drawing::Point(90, 485);

            // Events
            btnDisplay->Click += gcnew EventHandler(this, &MainMenuForm::btnDisplay_Click);
            btnSearch->Click += gcnew EventHandler(this, &MainMenuForm::btnSearch_Click);
            btnOrder->Click += gcnew EventHandler(this, &MainMenuForm::btnOrder_Click);
            btnHistory->Click += gcnew EventHandler(this, &MainMenuForm::btnHistory_Click);
            btnAdd->Click += gcnew EventHandler(this, &MainMenuForm::btnAdd_Click);
            btnRestock->Click += gcnew EventHandler(this, &MainMenuForm::btnRestock_Click);
            btnCompare->Click += gcnew EventHandler(this, &MainMenuForm::btnCompare_Click);
            btnLogout->Click += gcnew EventHandler(this, &MainMenuForm::btnLogout_Click);

            this->Controls->Add(lblWelcome);
            this->Controls->Add(lblRole);
            this->Controls->Add(btnDisplay);
            this->Controls->Add(btnSearch);
            this->Controls->Add(btnOrder);
            this->Controls->Add(btnHistory);
            this->Controls->Add(btnAdd);
            this->Controls->Add(btnRestock);
            this->Controls->Add(btnCompare);
            this->Controls->Add(btnLogout);
        }

        Button^ CreateButton(String^ text, Color color) {
            Button^ btn = gcnew Button();
            btn->Text = text;
            btn->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
            btn->Size = Drawing::Size(230, 40);
            btn->BackColor = color;
            btn->ForeColor = Color::White;
            btn->FlatStyle = FlatStyle::Flat;
            btn->FlatAppearance->BorderSize = 0;
            btn->Cursor = Cursors::Hand;
            return btn;
        }

        void UpdateWelcome() {
            String^ name = gcnew String(loggedUser->getName().c_str());
            lblWelcome->Text = L"Welcome, " + name + L"!";
            lblRole->Text = (role == 1) ? L"[ Student ]" : L"[ Staff ]";

            // Staff-only buttons
            bool isStaff = (role == 2);
            btnAdd->Enabled = isStaff;
            btnRestock->Enabled = isStaff;
            btnHistory->Enabled = isStaff;
            if (!isStaff) {
                btnAdd->BackColor = Color::LightGray;
                btnRestock->BackColor = Color::LightGray;
                btnHistory->BackColor = Color::LightGray;
            }
        }

        void btnDisplay_Click(Object^ sender, EventArgs^ e) { this->Tag = "display";  this->Close(); }
        void btnSearch_Click(Object^ sender, EventArgs^ e) { this->Tag = "search";   this->Close(); }
        void btnOrder_Click(Object^ sender, EventArgs^ e) { this->Tag = "order";    this->Close(); }
        void btnHistory_Click(Object^ sender, EventArgs^ e) { this->Tag = "history";  this->Close(); }
        void btnAdd_Click(Object^ sender, EventArgs^ e) { this->Tag = "add";      this->Close(); }
        void btnRestock_Click(Object^ sender, EventArgs^ e) { this->Tag = "restock";  this->Close(); }
        void btnCompare_Click(Object^ sender, EventArgs^ e) { this->Tag = "compare";  this->Close(); }
        void btnLogout_Click(Object^ sender, EventArgs^ e) { this->Tag = "logout";   this->Close(); }
    };
}