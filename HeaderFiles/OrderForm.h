#pragma once
#include "Resource.h"
#include "Book Store.h"
#include "food.h"
#include "Lab Hardware.h"
#include "Order.h"
#include "Payment.h"
#include "InventoryFile.h"
#include "user.h"
#include <vector>
#using <System.Windows.Forms.dll>
#using <System.dll>
#using <System.Drawing.dll>

namespace Project1 {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace std;

    public ref class OrderForm : public Form {
    public:
        vector<Resource*>* inventory;
        User* loggedUser;
        int role;

        OrderForm(User* u, int r, vector<Resource*>* inv) {
            loggedUser = u;
            role = r;
            inventory = inv;
            InitializeComponent();
            LoadInventory();
        }

    private:
        // Top
        Label^ lblTitle;
        Label^ lblDelivery;
        RadioButton^ rbPickup;
        RadioButton^ rbDelivery;

        // Inventory list
        ListView^ listInventory;

        // Order list
        ListView^ listOrder;

        // Quantity + Add
        Label^ lblQty;
        TextBox^ txtQty;
        Button^ btnAddItem;

        // Total + Payment
        Label^ lblTotal;
        Label^ lblDiscount;
        Label^ lblPayMethod;
        RadioButton^ rbCash;
        RadioButton^ rbCard;
        TextBox^ txtCard;
        Label^ lblCard;
        Button^ btnPlaceOrder;
        Label^ lblStatus;

        void InitializeComponent() {
            this->Text = L"Smart Campus - Create Order";
            this->Size = Drawing::Size(780, 620);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::FromArgb(245, 247, 250);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;

            // Title
            lblTitle = gcnew Label();
            lblTitle->Text = L"Create Order";
            lblTitle->Font = gcnew Drawing::Font("Segoe UI", 13, FontStyle::Bold);
            lblTitle->ForeColor = Color::FromArgb(30, 80, 160);
            lblTitle->Size = Drawing::Size(740, 35);
            lblTitle->Location = Drawing::Point(20, 10);
            lblTitle->TextAlign = ContentAlignment::MiddleCenter;

            // Delivery GroupBox
            rbPickup = gcnew RadioButton();
            rbPickup->Text = L"Pickup";
            rbPickup->Font = gcnew Drawing::Font("Segoe UI", 9);
            rbPickup->Location = Drawing::Point(15, 18);
            rbPickup->Size = Drawing::Size(80, 22);
            rbPickup->Checked = true;

            rbDelivery = gcnew RadioButton();
            rbDelivery->Text = L"Delivery (+50 EGP)";
            rbDelivery->Font = gcnew Drawing::Font("Segoe UI", 9);
            rbDelivery->Location = Drawing::Point(100, 18);
            rbDelivery->Size = Drawing::Size(150, 22);
            rbDelivery->CheckedChanged += gcnew EventHandler(this, &OrderForm::rbDelivery_Changed);

            GroupBox^ grpDelivery = gcnew GroupBox();
            grpDelivery->Text = L"Delivery Type";
            grpDelivery->Font = gcnew Drawing::Font("Segoe UI", 9);
            grpDelivery->Location = Drawing::Point(20, 50);
            grpDelivery->Size = Drawing::Size(280, 48);
            grpDelivery->Controls->Add(rbPickup);
            grpDelivery->Controls->Add(rbDelivery);

            // Inventory ListView
            Label^ lblInv = gcnew Label();
            lblInv->Text = L"Available Resources:";
            lblInv->Font = gcnew Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            lblInv->Location = Drawing::Point(20, 108);
            lblInv->Size = Drawing::Size(160, 22);

            listInventory = gcnew ListView();
            listInventory->Location = Drawing::Point(20, 130);
            listInventory->Size = Drawing::Size(370, 200);
            listInventory->View = View::Details;
            listInventory->FullRowSelect = true;
            listInventory->GridLines = true;
            listInventory->Font = gcnew Drawing::Font("Segoe UI", 9);
            listInventory->Columns->Add(L"ID", 50);
            listInventory->Columns->Add(L"Name", 130);
            listInventory->Columns->Add(L"Price", 80);
            listInventory->Columns->Add(L"Stock", 60);

            // Order ListView
            Label^ lblOrd = gcnew Label();
            lblOrd->Text = L"Order Items:";
            lblOrd->Font = gcnew Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            lblOrd->Location = Drawing::Point(410, 108);
            lblOrd->Size = Drawing::Size(120, 22);

            listOrder = gcnew ListView();
            listOrder->Location = Drawing::Point(410, 130);
            listOrder->Size = Drawing::Size(340, 200);
            listOrder->View = View::Details;
            listOrder->FullRowSelect = true;
            listOrder->GridLines = true;
            listOrder->Font = gcnew Drawing::Font("Segoe UI", 9);
            listOrder->Columns->Add(L"Name", 130);
            listOrder->Columns->Add(L"Qty", 50);
            listOrder->Columns->Add(L"Total", 80);

            // Qty + Add button
            lblQty = gcnew Label();
            lblQty->Text = L"Quantity:";
            lblQty->Font = gcnew Drawing::Font("Segoe UI", 9);
            lblQty->Location = Drawing::Point(20, 345);
            lblQty->Size = Drawing::Size(70, 22);

            txtQty = gcnew TextBox();
            txtQty->Font = gcnew Drawing::Font("Segoe UI", 9);
            txtQty->Location = Drawing::Point(95, 343);
            txtQty->Size = Drawing::Size(60, 22);
            txtQty->Text = L"1";

            btnAddItem = gcnew Button();
            btnAddItem->Text = L"Add to Order";
            btnAddItem->Font = gcnew Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            btnAddItem->Size = Drawing::Size(120, 30);
            btnAddItem->Location = Drawing::Point(170, 340);
            btnAddItem->BackColor = Color::FromArgb(30, 80, 160);
            btnAddItem->ForeColor = Color::White;
            btnAddItem->FlatStyle = FlatStyle::Flat;
            btnAddItem->FlatAppearance->BorderSize = 0;
            btnAddItem->Cursor = Cursors::Hand;
            btnAddItem->Click += gcnew EventHandler(this, &OrderForm::btnAddItem_Click);

            // Total
            lblTotal = gcnew Label();
            lblTotal->Text = L"Total: 0.00 EGP";
            lblTotal->Font = gcnew Drawing::Font("Segoe UI", 11, FontStyle::Bold);
            lblTotal->ForeColor = Color::FromArgb(30, 80, 160);
            lblTotal->Location = Drawing::Point(410, 345);
            lblTotal->Size = Drawing::Size(200, 25);
            lblTotal->TextAlign = ContentAlignment::MiddleLeft;

            // Discount label (only visible for staff - role == 2)
            lblDiscount = gcnew Label();
            lblDiscount->Text = L"";
            lblDiscount->Font = gcnew Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            lblDiscount->ForeColor = Color::FromArgb(0, 140, 80);
            lblDiscount->Location = Drawing::Point(615, 348);
            lblDiscount->Size = Drawing::Size(135, 20);
            lblDiscount->TextAlign = ContentAlignment::MiddleRight;
            lblDiscount->Visible = false;

            // Payment GroupBox
            rbCash = gcnew RadioButton();
            rbCash->Text = L"Cash";
            rbCash->Font = gcnew Drawing::Font("Segoe UI", 9);
            rbCash->Location = Drawing::Point(15, 18);
            rbCash->Size = Drawing::Size(60, 22);
            rbCash->Checked = true;
            rbCash->CheckedChanged += gcnew EventHandler(this, &OrderForm::rbCash_Changed);

            rbCard = gcnew RadioButton();
            rbCard->Text = L"Card";
            rbCard->Font = gcnew Drawing::Font("Segoe UI", 9);
            rbCard->Location = Drawing::Point(90, 18);
            rbCard->Size = Drawing::Size(60, 22);

            GroupBox^ grpPayment = gcnew GroupBox();
            grpPayment->Text = L"Payment Method";
            grpPayment->Font = gcnew Drawing::Font("Segoe UI", 9);
            grpPayment->Location = Drawing::Point(20, 390);
            grpPayment->Size = Drawing::Size(200, 48);
            grpPayment->Controls->Add(rbCash);
            grpPayment->Controls->Add(rbCard);

            // Card fields
            lblCard = gcnew Label();
            lblCard->Text = L"Card Number:";
            lblCard->Font = gcnew Drawing::Font("Segoe UI", 9);
            lblCard->Location = Drawing::Point(20, 450);
            lblCard->Size = Drawing::Size(90, 22);
            lblCard->Visible = false;

            txtCard = gcnew TextBox();
            txtCard->Font = gcnew Drawing::Font("Segoe UI", 9);
            txtCard->Location = Drawing::Point(115, 448);
            txtCard->Size = Drawing::Size(160, 22);
            txtCard->MaxLength = 16;
            txtCard->Visible = false;

            // Place Order button
            btnPlaceOrder = gcnew Button();
            btnPlaceOrder->Text = L"Place Order";
            btnPlaceOrder->Font = gcnew Drawing::Font("Segoe UI", 11, FontStyle::Bold);
            btnPlaceOrder->Size = Drawing::Size(200, 42);
            btnPlaceOrder->Location = Drawing::Point(280, 490);
            btnPlaceOrder->BackColor = Color::FromArgb(0, 140, 80);
            btnPlaceOrder->ForeColor = Color::White;
            btnPlaceOrder->FlatStyle = FlatStyle::Flat;
            btnPlaceOrder->FlatAppearance->BorderSize = 0;
            btnPlaceOrder->Cursor = Cursors::Hand;
            btnPlaceOrder->Click += gcnew EventHandler(this, &OrderForm::btnPlaceOrder_Click);

            // Status
            lblStatus = gcnew Label();
            lblStatus->Font = gcnew Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            lblStatus->Location = Drawing::Point(20, 545);
            lblStatus->Size = Drawing::Size(740, 25);
            lblStatus->TextAlign = ContentAlignment::MiddleCenter;

            this->Controls->Add(lblTitle);
            this->Controls->Add(grpDelivery);
            this->Controls->Add(lblInv);
            this->Controls->Add(listInventory);
            this->Controls->Add(lblOrd);
            this->Controls->Add(listOrder);
            this->Controls->Add(lblQty);
            this->Controls->Add(txtQty);
            this->Controls->Add(btnAddItem);
            this->Controls->Add(lblTotal);
            this->Controls->Add(lblDiscount);
            this->Controls->Add(grpPayment);
            this->Controls->Add(lblCard);
            this->Controls->Add(txtCard);
            this->Controls->Add(btnPlaceOrder);
            this->Controls->Add(lblStatus);
        }

        void LoadInventory() {
            listInventory->Items->Clear();
            for (auto item : *inventory) {
                ListViewItem^ row = gcnew ListViewItem(gcnew String(to_string(item->getId()).c_str()));
                row->SubItems->Add(gcnew String(item->getName().c_str()));
                row->SubItems->Add(gcnew String(to_string(item->getPrice()).c_str()));
                row->SubItems->Add(gcnew String(to_string(item->getQuantity()).c_str()));
                listInventory->Items->Add(row);
            }
        }

        void UpdateTotal() {
            double total = 0;
            for each (ListViewItem ^ row in listOrder->Items)
                total += Double::Parse(row->SubItems[2]->Text);
            if (rbDelivery->Checked) total += 50;
            // apply discount for staff
            if (role == 2) {
                double discount = total * 0.10;
                total -= discount;
                lblDiscount->Text = L"Discount 10%: -" + discount.ToString("F2") + L" EGP";
                lblDiscount->Visible = true;
            }
            else {
                lblDiscount->Visible = false;
            }
            lblTotal->Text = L"Total: " + total.ToString("F2") + L" EGP";
        }

        void rbCash_Changed(Object^ sender, EventArgs^ e) {
            lblCard->Visible = rbCard->Checked;
            txtCard->Visible = rbCard->Checked;
        }
        void rbDelivery_Changed(Object^ sender, EventArgs^ e) {
            UpdateTotal();
        }


        void btnAddItem_Click(Object^ sender, EventArgs^ e) {
            if (listInventory->SelectedItems->Count == 0) {
                MessageBox::Show(L"Please select a resource first!", L"Order", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            int qty = 0;
            try { qty = Int32::Parse(txtQty->Text); }
            catch (...) {
                MessageBox::Show(L"Invalid quantity!", L"Order", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            ListViewItem^ selected = listInventory->SelectedItems[0];
            int id = Int32::Parse(selected->Text);

            for (auto item : *inventory) {
                if (item->getId() == id) {
                    try {
                        item->purchase(qty);
                        double itemTotal = item->getPrice() * qty;
                        ListViewItem^ row = gcnew ListViewItem(gcnew String(item->getName().c_str()));
                        row->SubItems->Add(qty.ToString());
                        row->SubItems->Add(itemTotal.ToString("F2"));
                        row->Tag = gcnew String(to_string(id).c_str());
                        listOrder->Items->Add(row);
                        LoadInventory();
                        UpdateTotal();
                    }
                    catch (exception& ex) {
                        MessageBox::Show(gcnew String(ex.what()), L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    }
                    return;
                }
            }
        }

        void btnPlaceOrder_Click(Object^ sender, EventArgs^ e) {
            if (listOrder->Items->Count == 0) {
                MessageBox::Show(L"No items in order!", L"Order", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            // Card validation
            if (rbCard->Checked) {
                String^ cardNum = txtCard->Text;
                if (cardNum->Length != 16) {
                    MessageBox::Show(L"Card number must be 16 digits!", L"Payment", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
                for (int i = 0; i < cardNum->Length; i++) {
                    if (!Char::IsDigit(cardNum[i])) {
                        MessageBox::Show(L"Card must contain digits only!", L"Payment", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                        return;
                    }
                }
            }

            string delivery = rbDelivery->Checked ? "delivery" : "pickup";
            Order order(loggedUser, delivery);

            for each (ListViewItem ^ row in listOrder->Items) {
                int id = Int32::Parse((String^)row->Tag);
                int qty = Int32::Parse(row->SubItems[1]->Text);
                for (auto item : *inventory)
                    if (item->getId() == id) { order.addItem(item, qty); break; }
            }

            saveInventory(*inventory);
            saveOrder(order);

            double total = order.calculateTotal();
            String^ payMsg = rbCash->Checked ?
                L"Cash Payment Successful!\nAmount Paid: " + total.ToString("F2") + L" EGP" :
                L"Card Payment Successful!\nAmount Paid: " + total.ToString("F2") + L" EGP";

            MessageBox::Show(payMsg, L"Payment", MessageBoxButtons::OK, MessageBoxIcon::Information);

            lblStatus->ForeColor = Color::FromArgb(0, 140, 80);
            lblStatus->Text = L"Order placed successfully!";
            listOrder->Items->Clear();
            LoadInventory();
            UpdateTotal();
        }
    };
}