#pragma once
#include <vector>
#include <sstream>
#include "Resource.h"
#include "Order.h"

using namespace std;

void saveInventory(vector<Resource*> items);
void loadInventory(vector<Resource*>& items);
void saveOrder(Order& order);
void loadOrders();

