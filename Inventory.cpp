#include "Inventory.h"
#include<iostream>

using namespace std;

Inventory::Inventory(int id) : inventoryID(id) {}

void Inventory::addProduct(const Product product) {
	products.push_back(product);
}

bool Inventory::checkAvailability(int productID) const {
	for (const auto& product : products) {
		if (product.getProductID() == productID && product.getQuantity() > 0) {
			return true;
		}
	}
	return false;
}

void Inventory::updateInventory(int productID, int quantity) {
	for(auto & product: products) {
		if (product.getProductID() == productID) {
			product.setQuantity(product.getQuantity() + quantity);
			return;
		}
	}
}
void Inventory::displayInventory() const {
	cout << "Inventory ID; " << inventoryID << "\n";
	for (const auto& product : products) {
		product.displayProduct();
	}
}
