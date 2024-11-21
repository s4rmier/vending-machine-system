#include "Inventory.h"
#include<iostream>
#include <iomanip>

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
	for (const auto& product : products) {
		cout << setw(2) << setfill('0') << product.getProductID() << ". "
			<< product.getName()
			<< " - $" << fixed << setprecision(2) << product.getPrice()
			<< " (Qty: " << product.getQuantity() << ")\n";
	}
	cout << "99. Admin Panel\n";
}

float Inventory::getProductPrice(int productID) const {
	for (const auto& product : products) {
		if (product.getProductID() == productID) {
			return product.getPrice();
		}
	}
	return 0.0f;
}