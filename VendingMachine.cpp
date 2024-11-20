#include "Inventory.cpp"
#include "PaymentProcessor.cpp"
#include "Admin.cpp"
#include "SalesData.cpp"
#include <iostream>
#include <iomanip>
#include <limits>

class VendingMachine {
private:
    int machineID;
    std::string location;
    float currentBalance;
    
    Inventory* inventory;
    PaymentProcessor* paymentProcessor;
    Admin* admin;
    Transaction* currentTransaction;
    SalesData* salesData;

    void recordSale() {
        if (currentTransaction && salesData) {
            salesData->recordTransactionData(currentTransaction);
        }
    }

    void displayHeader() {
        std::cout << "## University Vendo ##\n\n";
    }

    float handleMoneyInsertion() {
        bool inserting = true;
        float totalAmount = 0.0f;
        
        while (inserting && totalAmount < 20.0f) {
            std::cout << "\nTotal Amount: $" << std::fixed << std::setprecision(2) << totalAmount << "\n\n";
            std::cout << "1. Insert 1¢\n";
            std::cout << "2. Insert 5¢\n";
            std::cout << "3. Insert 10¢\n";
            std::cout << "4. Insert 25¢\n";
            std::cout << "5. Insert $1\n";
            std::cout << "6. Insert $5\n";
            std::cout << "7. Insert $10\n";
            std::cout << "8. Insert $20\n";
            std::cout << "9. Done Inserting\n";
            std::cout << "10. Cancel Transaction\n";
            
            int choice;
            std::cout << "Choose option: ";
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            float amounts[] = {0.01f, 0.05f, 0.10f, 0.25f, 1.00f, 5.00f, 10.00f, 20.00f};
            
            if (choice >= 1 && choice <= 8) {
                float amount = amounts[choice-1];
                if (totalAmount + amount > 20.0f) {
                    std::cout << "Cannot accept more than $20.00\n";
                    continue;
                }
                totalAmount += amount;
                if (amount == 20.0f || totalAmount >= 20.0f) {
                    break;
                }
            }
            else if (choice == 9) {
                break;
            }
            else if (choice == 10) {
                totalAmount = 0;
                break;
            }
            else {
                std::cout << "Invalid option\n";
            }
        }
        return totalAmount;
    }

    void initializeProducts() {
        inventory->addProduct(Product(1, "Flaming Hot Cheetos", 3.00, 15));
        inventory->addProduct(Product(2, "Doritos Nacho Cheese", 3.00, 15));
        inventory->addProduct(Product(3, "Lays Classic", 2.75, 15));
        inventory->addProduct(Product(4, "Ruffles Cheddar", 2.75, 15));
        inventory->addProduct(Product(5, "Pringles Original", 3.25, 15));
        inventory->addProduct(Product(6, "Snickers", 1.75, 15));
        inventory->addProduct(Product(7, "M&Ms Peanut", 1.75, 15));
        inventory->addProduct(Product(8, "Twix", 1.75, 15));
        inventory->addProduct(Product(9, "Reese's Cups", 1.75, 15));
        inventory->addProduct(Product(10, "Skittles", 1.50, 15));
        inventory->addProduct(Product(11, "Coca Cola", 2.00, 15));
        inventory->addProduct(Product(12, "Pepsi", 2.00, 15));
        inventory->addProduct(Product(13, "Mountain Dew", 2.00, 15));
        inventory->addProduct(Product(14, "Dr Pepper", 2.00, 15));
        inventory->addProduct(Product(15, "Sprite", 2.00, 15));
        inventory->addProduct(Product(16, "Trail Mix", 2.50, 15));
        inventory->addProduct(Product(17, "Granola Bar", 1.50, 15));
        inventory->addProduct(Product(18, "Mixed Nuts", 2.75, 15));
        inventory->addProduct(Product(19, "Dried Fruit", 2.25, 15));
        inventory->addProduct(Product(20, "Water Bottle", 1.50, 15));
    }
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
