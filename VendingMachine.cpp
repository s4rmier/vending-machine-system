#include "Inventory.cpp"
#include "PaymentProcessor.cpp"
#include "Admin.cpp"

class VendingMachine {
public:
    VendingMachine();
};


/* sample main to call my classes - HK
#include "Product.h"
#include "Inventory.h"
#include "Transaction.h"
#include <iostream>

using namespace std;

int main() {
	//create the products here
	Product p1(1, "Flaming hot Cheetos", 3.00, 10);


	//create the inventory and add products
	Inventory inventory(101);
	inventory.addProduct(p1);

	//display inventory
	inventory.displayInventory();

	//check availability and update inventory
	if (inventory.checkAvailability(1)) {
		cout << "Product is available.\n";
		inventory.updateInventory(1, -1);
	}

	//display updated inventory
	inventory.displayInventory();

	//create a transaction
	Transaction transaction(1001);
	if (transaction.initiateTransaction(3.00)) {
		if (transaction.completeTransaction(1.50)) {
			inventory.updateInventory(1, -1);//reduces the inventory
		}
	}

	//refund example
	transaction.refundTransaction();
	return 0;
}
*/
