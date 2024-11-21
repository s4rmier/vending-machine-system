#include "Product.h"
#include <iostream>

using namespace std;

Product::Product(int id, const string& n, int p, int q)
	:productID(id), name(n), price(p), quantity(q) {}

int Product::getProductID() const { return productID; }
string Product::getName() const { return name; }
int Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }
void Product::setQuantity(int q) { quantity = q; }

void Product::displayProduct() const {
	cout << "Product ID: " << productID
		<< ", Name: " << name
		<< ", Price: $" << price
		<< ", Quantity: " << quantity << "\n";
}
