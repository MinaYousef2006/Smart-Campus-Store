#pragma once
#include "user.h"
#include "student.h"
#include "staff.h"
#include <vector>
#using <System.Windows.Forms.dll>
#using <System.dll>
#using <System.Drawing.dll>

namespace Project1 {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace std;

    public ref class LoginForm : public Form {
    public:
        vector<User*>* users;
        User* loggedUser;
        int role;

        LoginForm(vector<User*>* u) {
            users = u;
            loggedUser = nullptr;
            role = 0;
            InitializeComponent();
        }

    private:
        Label^ lblTitle;
        Label^ lblRole;
        RadioButton^ rbStudent;
        RadioButton^ rbStaff;
        Label^ lblName;
        TextBox^ txtName;
        Label^ lblID;
        TextBox^ txtID;
        Button^ btnLogin;
        Label^ lblError;
        Panel^ pnlMain;

        void InitializeComponent() {
            this->Text = L"Smart Campus  - Login";
            this->Size = Drawing::Size(420, 380);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::FromArgb(245, 247, 250);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;

            // Title
            lblTitle = gcnew Label();
            lblTitle->Text = L"SMART CAMPUS STORE";
            lblTitle->Font = gcnew Drawing::Font("Segoe UI", 18, FontStyle::Bold);
            lblTitle->ForeColor = Color::FromArgb(30, 80, 160);
            lblTitle->Size = Drawing::Size(380, 40);
            lblTitle->Location = Drawing::Point(20, 20);
            lblTitle->TextAlign = ContentAlignment::MiddleCenter;

            // Role label
            lblRole = gcnew Label();
            lblRole->Text = L"Login as:";
            lblRole->Font = gcnew Drawing::Font("Segoe UI", 10);
            lblRole->Location = Drawing::Point(40, 80);
            lblRole->Size = Drawing::Size(80, 25);

            // Radio buttons
            rbStudent = gcnew RadioButton();
            rbStudent->Text = L"Student";
            rbStudent->Font = gcnew Drawing::Font("Segoe UI", 10);
            rbStudent->Location = Drawing::Point(130, 78);
            rbStudent->Size = Drawing::Size(90, 25);
            rbStudent->Checked = true;

            rbStaff = gcnew RadioButton();
            rbStaff->Text = L"Staff";
            rbStaff->Font = gcnew Drawing::Font("Segoe UI", 10);
            rbStaff->Location = Drawing::Point(230, 78);
            rbStaff->Size = Drawing::Size(80, 25);

            // Name
            lblName = gcnew Label();
            lblName->Text = L"Name:";
            lblName->Font = gcnew Drawing::Font("Segoe UI", 10);
            lblName->Location = Drawing::Point(40, 130);
            lblName->Size = Drawing::Size(80, 25);

            txtName = gcnew TextBox();
            txtName->Font = gcnew Drawing::Font("Segoe UI", 10);
            txtName->Location = Drawing::Point(130, 128);
            txtName->Size = Drawing::Size(220, 25);

            // ID
            lblID = gcnew Label();
            lblID->Text = L"Campus ID:";
            lblID->Font = gcnew Drawing::Font("Segoe UI", 10);
            lblID->Location = Drawing::Point(40, 180);
            lblID->Size = Drawing::Size(80, 25);

            txtID = gcnew TextBox();
            txtID->Font = gcnew Drawing::Font("Segoe UI", 10);
            txtID->Location = Drawing::Point(130, 178);
            txtID->Size = Drawing::Size(220, 25);

            // Login button
            btnLogin = gcnew Button();
            btnLogin->Text = L"Login";
            btnLogin->Font = gcnew Drawing::Font("Segoe UI", 11, FontStyle::Bold);
            btnLogin->Size = Drawing::Size(220, 40);
            btnLogin->Location = Drawing::Point(100, 230);
            btnLogin->BackColor = Color::FromArgb(30, 80, 160);
            btnLogin->ForeColor = Color::White;
            btnLogin->FlatStyle = FlatStyle::Flat;
            btnLogin->FlatAppearance->BorderSize = 0;
            btnLogin->Cursor = Cursors::Hand;
            btnLogin->Click += gcnew EventHandler(this, &LoginForm::btnLogin_Click);

            // Error label
            lblError = gcnew Label();
            lblError->Text = L"";
            lblError->ForeColor = Color::Red;
            lblError->Font = gcnew Drawing::Font("Segoe UI", 9);
            lblError->Location = Drawing::Point(40, 285);
            lblError->Size = Drawing::Size(320, 25);
            lblError->TextAlign = ContentAlignment::MiddleCenter;

            this->Controls->Add(lblTitle);
            this->Controls->Add(lblRole);
            this->Controls->Add(rbStudent);
            this->Controls->Add(rbStaff);
            this->Controls->Add(lblName);
            this->Controls->Add(txtName);
            this->Controls->Add(lblID);
            this->Controls->Add(txtID);
            this->Controls->Add(btnLogin);
            this->Controls->Add(lblError);
        }

        void btnLogin_Click(Object^ sender, EventArgs^ e) {
            role = rbStudent->Checked ? 1 : 2;
            String^ sName = txtName->Text;
            String^ sID = txtID->Text;
            string name = "";
            string id = "";
            for (int i = 0; i < sName->Length; i++)
                name += (char)sName[i];
            for (int i = 0; i < sID->Length; i++)
                id += (char)sID[i];

            for (auto u : *users) {
                bool isStudent = dynamic_cast<Student*>(u);
                if (u->getName() == name && u->getCampusID() == id) {
                    if ((role == 1 && isStudent) || (role == 2 && !isStudent)) {
                        loggedUser = u;
                        this->DialogResult = System::Windows::Forms::DialogResult::OK;
                        this->Close();
                        return;
                    }
                }
            }
            lblError->Text = L"Invalid Name or ID! Try again.";
        }
    };
}