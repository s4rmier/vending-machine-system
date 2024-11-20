#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Product.h"

using namespace std;

class Inventory
{
private:
	int inventoryID;
	vector<Product> products;

public:
	Inventory(int id);

	void addProduct(const Product product);

	//void addProduct(const Product& product);
	bool chackAvailability(int productID) const;
	void updateInventory(int productID, int quantity);
	void displayInventory() const;
};

#endif

