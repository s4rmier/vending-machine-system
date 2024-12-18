#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H

#include<string>
using namespace std;

class Product
{
private:
	int productID;
	string name;
	int price;
	int quantity;

public: Product(int id, const string& n, int p, int q);

	  int getProductID()const;
	  string getName() const;
	  int getPrice() const;
	  int getQuantity() const;
	  void setQuantity(int q);
	  void displayProduct() const;

};

#endif
