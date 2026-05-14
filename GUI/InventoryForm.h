#pragma once
#include "Resource.h"
#include "Book Store.h"
#include "food.h"
#include "Lab Hardware.h"
#include "InventoryFile.h"
#include "search.h"
#include <vector>
#using <System.Windows.Forms.dll>
#using <System.dll>
#using <System.Drawing.dll>

namespace Project1 {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace std;

    public ref class InventoryForm : public Form {
    public:
        vector<Resource*>* inventory;
        int role;
        String^ mode; // "display", "search", "add", "restock", "compare"

        InventoryForm(vector<Resource*>* inv, int r, String^ m) {
            inventory = inv;
            role = r;
            mode = m;
            InitializeComponent();
            LoadData();
        }

    private:
        ListView^ listView;
        Label^ lblTitle;
        Panel^ pnlBottom;

        // Search
        TextBox^ txtSearchID;
        Button^ btnSearch;

        // Add
        ComboBox^ cmbType;
        TextBox^ txtID;
        TextBox^ txtName;
        TextBox^ txtPrice;
        TextBox^ txtQty;
        TextBox^ txtExtra1;
        TextBox^ txtExtra2;
        Button^ btnAdd;
        Label^ lblExtra1;
        Label^ lblExtra2;
        // Restock
        TextBox^ txtRestockID;
        TextBox^ txtRestockAmt;
        Button^ btnRestock;

        // Compare
        TextBox^ txtCmpID1;
        TextBox^ txtCmpID2;
        Button^ btnCompare;
        Label^ lblResult;

        void InitializeComponent() {
            this->Size = Drawing::Size(750, 550);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::FromArgb(245, 247, 250);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;

            lblTitle = gcnew Label();
            lblTitle->Font = gcnew Drawing::Font("Segoe UI", 13, FontStyle::Bold);
            lblTitle->ForeColor = Color::FromArgb(30, 80, 160);
            lblTitle->Size = Drawing::Size(710, 35);
            lblTitle->Location = Drawing::Point(20, 10);
            lblTitle->TextAlign = ContentAlignment::MiddleCenter;

            listView = gcnew ListView();
            listView->Location = Drawing::Point(20, 55);
            listView->Size = Drawing::Size(710, 320);
            listView->View = View::Details;
            listView->FullRowSelect = true;
            listView->GridLines = true;
            listView->Font = gcnew Drawing::Font("Segoe UI", 9);
            listView->Columns->Add(L"ID", 60);
            listView->Columns->Add(L"Name", 140);
            listView->Columns->Add(L"Category", 110);
            listView->Columns->Add(L"Price", 80);
            listView->Columns->Add(L"Stock", 60);
            listView->Columns->Add(L"Extra 1", 130);
            listView->Columns->Add(L"Extra 2", 100);

            pnlBottom = gcnew Panel();
            pnlBottom->Location = Drawing::Point(20, 385);
            pnlBottom->Size = Drawing::Size(710, 120);
            pnlBottom->BackColor = Color::White;

            this->Controls->Add(lblTitle);
            this->Controls->Add(listView);
            this->Controls->Add(pnlBottom);

            if (mode->Equals("display")) {
                this->Text = L"Inventory - Display";
                lblTitle->Text = L"All Resources";
            }
            else if (mode->Equals("search")) {
                this->Text = L"Inventory - Search";
                lblTitle->Text = L"Search Resource by ID";
                BuildSearchPanel();
            }
            else if (mode->Equals("add")) {
                this->Text = L"Inventory - Add Resource";
                lblTitle->Text = L"Add New Resource";
                BuildAddPanel();
            }
            else if (mode->Equals("restock")) {
                this->Text = L"Inventory - Restock";
                lblTitle->Text = L"Restock Resource";
                BuildRestockPanel();
            }
            else if (mode->Equals("compare")) {
                this->Text = L"Inventory - Compare";
                lblTitle->Text = L"Compare Resources";
                BuildComparePanel();
            }
        }

        // ---- helpers ----
        Label^ MakeLabel(String^ text, int x, int y) {
            Label^ l = gcnew Label();
            l->Text = text;
            l->Font = gcnew Drawing::Font("Segoe UI", 9);
            l->Location = Drawing::Point(x, y);
            l->Size = Drawing::Size(80, 22);
            return l;
        }

        TextBox^ MakeTextBox(int x, int y, int w) {
            TextBox^ t = gcnew TextBox();
            t->Font = gcnew Drawing::Font("Segoe UI", 9);
            t->Location = Drawing::Point(x, y);
            t->Size = Drawing::Size(w, 22);
            return t;
        }

        Button^ MakeButton(String^ text, Color color, int x, int y) {
            Button^ b = gcnew Button();
            b->Text = text;
            b->Font = gcnew Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            b->Size = Drawing::Size(110, 30);
            b->Location = Drawing::Point(x, y);
            b->BackColor = color;
            b->ForeColor = Color::White;
            b->FlatStyle = FlatStyle::Flat;
            b->FlatAppearance->BorderSize = 0;
            b->Cursor = Cursors::Hand;
            return b;
        }

        // ---- panels ----
        void BuildSearchPanel() {
            pnlBottom->Controls->Add(MakeLabel(L"Resource ID:", 10, 15));
            txtSearchID = MakeTextBox(100, 13, 120);
            pnlBottom->Controls->Add(txtSearchID);
            btnSearch = MakeButton(L"Search", Color::FromArgb(30, 80, 160), 235, 10);
            btnSearch->Click += gcnew EventHandler(this, &InventoryForm::btnSearch_Click);
            pnlBottom->Controls->Add(btnSearch);
        }

        void BuildAddPanel() {
            pnlBottom->Controls->Add(MakeLabel(L"Type:", 10, 10));
            cmbType = gcnew ComboBox();
            cmbType->Font = gcnew Drawing::Font("Segoe UI", 9);
            cmbType->Location = Drawing::Point(90, 8);
            cmbType->Size = Drawing::Size(110, 22);
            cmbType->Items->Add(L"Book");
            cmbType->Items->Add(L"Food");
            cmbType->Items->Add(L"Lab Hardware");
            cmbType->SelectedIndex = 0;
            cmbType->SelectedIndexChanged += gcnew EventHandler(this, &InventoryForm::cmbType_Changed);
            pnlBottom->Controls->Add(cmbType);

            pnlBottom->Controls->Add(MakeLabel(L"ID:", 10, 40));
            txtID = MakeTextBox(90, 38, 80);
            pnlBottom->Controls->Add(txtID);

            pnlBottom->Controls->Add(MakeLabel(L"Name:", 10, 70));
            txtName = MakeTextBox(90, 68, 120);
            pnlBottom->Controls->Add(txtName);

            pnlBottom->Controls->Add(MakeLabel(L"Price:", 230, 40));
            txtPrice = MakeTextBox(310, 38, 80);
            pnlBottom->Controls->Add(txtPrice);

            pnlBottom->Controls->Add(MakeLabel(L"Qauntity:", 230, 70));
            txtQty = MakeTextBox(310, 68, 80);
            pnlBottom->Controls->Add(txtQty);

            // Extra labels 
            lblExtra1 = gcnew Label();
            lblExtra1->Text = L"Author:";
            lblExtra1->Font = gcnew Drawing::Font("Segoe UI", 9);
            lblExtra1->Location = Drawing::Point(390, 40);
            lblExtra1->Size = Drawing::Size(65, 22);
            pnlBottom->Controls->Add(lblExtra1);
            txtExtra1 = MakeTextBox(460, 38, 110);
            pnlBottom->Controls->Add(txtExtra1);

            lblExtra2 = gcnew Label();
            lblExtra2->Text = L"Pages:";
            lblExtra2->Font = gcnew Drawing::Font("Segoe UI", 9);
            lblExtra2->Location = Drawing::Point(390, 70);
            lblExtra2->Size = Drawing::Size(65, 22);
            pnlBottom->Controls->Add(lblExtra2);
            txtExtra2 = MakeTextBox(460, 68, 110);
            pnlBottom->Controls->Add(txtExtra2);

            btnAdd = MakeButton(L"Add", Color::FromArgb(0, 140, 80), 590, 50);
            btnAdd->Click += gcnew EventHandler(this, &InventoryForm::btnAdd_Click);
            pnlBottom->Controls->Add(btnAdd);
        }

        void BuildRestockPanel() {
            pnlBottom->Controls->Add(MakeLabel(L"Resource ID:", 10, 15));
            txtRestockID = MakeTextBox(100, 13, 100);
            pnlBottom->Controls->Add(txtRestockID);
            pnlBottom->Controls->Add(MakeLabel(L"Amount:", 220, 15));
            txtRestockAmt = MakeTextBox(300, 13, 100);
            pnlBottom->Controls->Add(txtRestockAmt);
            btnRestock = MakeButton(L"Restock", Color::FromArgb(0, 140, 80), 420, 10);
            btnRestock->Click += gcnew EventHandler(this, &InventoryForm::btnRestock_Click);
            pnlBottom->Controls->Add(btnRestock);
        }

        void BuildComparePanel() {
            pnlBottom->Controls->Add(MakeLabel(L"First ID:", 10, 15));
            txtCmpID1 = MakeTextBox(90, 13, 100);
            pnlBottom->Controls->Add(txtCmpID1);
            pnlBottom->Controls->Add(MakeLabel(L"Second ID:", 210, 15));
            txtCmpID2 = MakeTextBox(300, 13, 100);
            pnlBottom->Controls->Add(txtCmpID2);
            btnCompare = MakeButton(L"Compare", Color::FromArgb(30, 80, 160), 420, 10);
            btnCompare->Click += gcnew EventHandler(this, &InventoryForm::btnCompare_Click);
            pnlBottom->Controls->Add(btnCompare);

            lblResult = gcnew Label();
            lblResult->Font = gcnew Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            lblResult->ForeColor = Color::FromArgb(30, 80, 160);
            lblResult->Location = Drawing::Point(10, 55);
            lblResult->Size = Drawing::Size(680, 50);
            lblResult->TextAlign = ContentAlignment::MiddleCenter;
            pnlBottom->Controls->Add(lblResult);
        }

        // ---- load data ----
        void LoadData() {
            listView->Items->Clear();
            for (auto item : *inventory) {
                ListViewItem^ row = gcnew ListViewItem(gcnew String(to_string(item->getId()).c_str()));
                row->SubItems->Add(gcnew String(item->getName().c_str()));
                row->SubItems->Add(gcnew String(item->GetCategory().c_str()));
                row->SubItems->Add(gcnew String(to_string(item->getPrice()).c_str()));
                row->SubItems->Add(gcnew String(to_string(item->getQuantity()).c_str()));

                BookStore* b = dynamic_cast<BookStore*>(item);
                food* f = dynamic_cast<food*>(item);
                LabHardware* l = dynamic_cast<LabHardware*>(item);

                if (b) {
                    row->SubItems->Add(gcnew String(b->GetAuthor().c_str()));
                    row->SubItems->Add(gcnew String(to_string(b->GetPages()).c_str()));
                }
                else if (f) {
                    row->SubItems->Add(gcnew String(f->getexpire().c_str()));
                    row->SubItems->Add(gcnew String(f->getcategoryFood().c_str()));
                }
                else if (l) {
                    row->SubItems->Add(gcnew String(l->getBrand().c_str()));
                    row->SubItems->Add(gcnew String(to_string(l->getWarranty()).c_str()));
                }
                listView->Items->Add(row);
            }
        }

        String^ ToStr(String^ s) { return s; }

        // ---- events ----
        void btnSearch_Click(Object^ sender, EventArgs^ e) {
            int id = Int32::Parse(txtSearchID->Text);
            listView->Items->Clear();
            for (auto item : *inventory) {
                if (item->getId() == id) {
                    ListViewItem^ row = gcnew ListViewItem(gcnew String(to_string(item->getId()).c_str()));
                    row->SubItems->Add(gcnew String(item->getName().c_str()));
                    row->SubItems->Add(gcnew String(item->GetCategory().c_str()));
                    row->SubItems->Add(gcnew String(to_string(item->getPrice()).c_str()));
                    row->SubItems->Add(gcnew String(to_string(item->getQuantity()).c_str()));
                    listView->Items->Add(row);
                    return;
                }
            }
            MessageBox::Show(L"Resource not found!", L"Search", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }

        void btnAdd_Click(Object^ sender, EventArgs^ e) {
            MessageBox::Show(L"Button clicked! Index: " + cmbType->SelectedIndex.ToString());
            try {
                int id = Int32::Parse(txtID->Text);
                double price = Double::Parse(txtPrice->Text);
                int qty = Int32::Parse(txtQty->Text);

                string name = "", extra1 = "", extra2 = "";
                for (int i = 0; i < txtName->Text->Length; i++)   name += (char)txtName->Text[i];
                for (int i = 0; i < txtExtra1->Text->Length; i++) extra1 += (char)txtExtra1->Text[i];
                for (int i = 0; i < txtExtra2->Text->Length; i++) extra2 += (char)txtExtra2->Text[i];

                if (cmbType->SelectedIndex == 0) {
                    if (extra2.empty()) {
                        MessageBox::Show(L"Please enter number of pages!", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                        return;
                    }
                    inventory->push_back(new BookStore(id, name, price, qty, extra1, stoi(extra2)));
                }
                else if (cmbType->SelectedIndex == 1) {
                    inventory->push_back(new food(id, name, price, qty, extra1, extra2));
                }
                else {
                    if (extra2.empty()) {
                        MessageBox::Show(L"Please enter warranty months!", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                        return;
                    }
                    inventory->push_back(new LabHardware(id, name, price, qty, extra1, stoi(extra2)));
                }

                saveInventory(*inventory);
                LoadData();
                MessageBox::Show(L"Resource added successfully!", L"Add", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            catch (Exception^ ex) {
                MessageBox::Show(L"Please fill all fields correctly!\n" + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
        void cmbType_Changed(Object^ sender, EventArgs^ e) {
            if (cmbType->SelectedIndex == 0) {
                lblExtra1->Text = L"Author:";
                lblExtra2->Text = L"Pages:";
            }
            else if (cmbType->SelectedIndex == 1) {
                lblExtra1->Text = L"Expire Date:";
                lblExtra2->Text = L"Category:";
            }
            else {
                lblExtra1->Text = L"Brand:";
                lblExtra2->Text = L"Warranty(months):";
            }
        }

        void btnRestock_Click(Object^ sender, EventArgs^ e) {
            int id = Int32::Parse(txtRestockID->Text);
            int amt = Int32::Parse(txtRestockAmt->Text);
            for (auto item : *inventory) {
                if (item->getId() == id) {
                    try {
                        item->restock(amt);
                        saveInventory(*inventory);
                        LoadData();
                        MessageBox::Show(L"Restocked successfully!", L"Restock", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    }
                    catch (exception& ex) {
                        MessageBox::Show(gcnew String(ex.what()), L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    }
                    return;
                }
            }
            MessageBox::Show(L"Resource not found!", L"Restock", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }

        void btnCompare_Click(Object^ sender, EventArgs^ e) {
            int id1 = Int32::Parse(txtCmpID1->Text);
            int id2 = Int32::Parse(txtCmpID2->Text);
            Resource* r1 = nullptr; Resource* r2 = nullptr;
            for (auto item : *inventory) {
                if (item->getId() == id1) r1 = item;
                if (item->getId() == id2) r2 = item;
            }
            if (r1 && r2) {
                double c1 = r1->getPrice() * r1->getQuantity();
                double c2 = r2->getPrice() * r2->getQuantity();
                String^ n1 = gcnew String(r1->getName().c_str());
                String^ n2 = gcnew String(r2->getName().c_str());
                String^ msg = n1 + L": " + c1.ToString("F2") + L" EGP  |  " + n2 + L": " + c2.ToString("F2") + L" EGP\n";
                if (c1 > c2) msg += n1 + L" has higher cost burden.";
                else if (c2 > c1) msg += n2 + L" has higher cost burden.";
                else msg += L"Both have the same cost burden.";
                lblResult->Text = msg;
            }
            else {
                MessageBox::Show(L"One or both resources not found!", L"Compare", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }
    };
}