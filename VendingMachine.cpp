#pragma once

#include "Inventory.h"
#include "PaymentProcessor.h"
#include "Admin.h"
#include "SalesData.h"
#include "Transaction.h"
#include <string>

class VendingMachine {
private:
    int machineID;
    int currentBalance;
    
    Inventory* inventory;
    PaymentProcessor* paymentProcessor;
    Admin* admin;
    Transaction* currentTransaction;
    SalesData* salesData;

    void recordSale();
    void displayHeader() const;
    int handleMoneyInsertion();
    void initializeProducts();

public:
    VendingMachine(int id);
    ~VendingMachine();
    
    void pushScreen();
    void displayProducts() const;
    bool selectProduct(int productId);
    bool dispenseProduct(int productId);
    void cancelTransaction();
    bool accessAdminPanel(Admin* adminUser);
    void displayPrice(int productId);
    int getProductPrice(int productId);
    void displayOutOfStock();
    int getCurrentBalance() const;
    bool insertMoney(int amount);
    int returnChange();
};

#include <iostream>
#include <iomanip>
#include <limits>

VendingMachine::VendingMachine(int id) 
   : machineID(id), currentBalance(0), currentTransaction(nullptr) {
   inventory = new Inventory(id);
   paymentProcessor = new PaymentProcessor();
   admin = new Admin();
   salesData = new SalesData();
   initializeProducts();
}

VendingMachine::~VendingMachine() {
   delete inventory;
   delete paymentProcessor;
   delete admin;
   delete salesData;
   if (currentTransaction) {
       delete currentTransaction;
   }
}

void VendingMachine::pushScreen() {
   std::cout << std::string(50, '\n');
}

void VendingMachine::recordSale() {
   if (currentTransaction && salesData) {
       salesData->recordTransactionData(currentTransaction);
   }
}

void VendingMachine::displayHeader() const {
   std::cout << "+--------------------------------+" << std::endl;
   std::cout << "|        University Vendo        |" << std::endl;
   std::cout << "+--------------------------------+" << std::endl;
   std::cout << std::endl;
}

int VendingMachine::handleMoneyInsertion() {
   bool inserting = true;
   int totalAmount = 0;
   int requiredAmount = inventory->getProductPrice(currentTransaction->getProductID());
   
   while (inserting && totalAmount < 2000) {
       pushScreen();
       std::cout << "\nTotal Amount: $" << (totalAmount / 100) << "."
                << (totalAmount % 100 < 10 ? "0" : "") << (totalAmount % 100) << "\n\n";
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

       int amounts[] = {1, 5, 10, 25, 100, 500, 1000, 2000};
       
       if (choice >= 1 && choice <= 8) {
           int amount = amounts[choice-1];
           if (totalAmount + amount > 2000) {
               pushScreen();
               std::cout << "\nTotal Amount: $" << (totalAmount / 100) << "."
                        << (totalAmount % 100 < 10 ? "0" : "") << (totalAmount % 100) << "\n\n";
               std::cout << "Cannot accept more than $20.00\n";
               std::cout << "Press Enter to continue...";
               std::cin.get();
               continue;
           }
           totalAmount += amount;
           currentBalance = totalAmount;
           
           if (amount == 2000 || totalAmount >= 2000) {
               if(totalAmount >= requiredAmount) {
                   return totalAmount;
               }
           }
       }
       else if (choice == 9) {
           pushScreen();
           std::cout << "\nProduct price: $" << (requiredAmount / 100) << "."
                    << (requiredAmount % 100 < 10 ? "0" : "") << (requiredAmount % 100) << "\n";
           
           std::cout << "Amount inserted: $" << (totalAmount / 100) << "."
                    << (totalAmount % 100 < 10 ? "0" : "") << (totalAmount % 100) << "\n";
           
           if (totalAmount < requiredAmount) {
               int remaining = requiredAmount - totalAmount;
               std::cout << "\nInsufficient amount.\n";
               std::cout << "Still needed: $" << (remaining / 100) << "."
                        << (remaining % 100 < 10 ? "0" : "") << (remaining % 100) << "\n";
               std::cout << "Please insert more money.\n";
               std::cout << "Press Enter to continue...";
               std::cin.get();
               continue;
           }
           currentBalance = totalAmount;
           return totalAmount;
       }
       else if (choice == 10) {
           return -1;
       }
       else {
           pushScreen();
           std::cout << "Invalid option\n";
           std::cout << "Press Enter to continue...";
           std::cin.get();
       }
   }
   return totalAmount;
}

void VendingMachine::initializeProducts() {
    inventory->addProduct(Product(1, "Flaming Hot Cheetos", 300, 2));
    inventory->addProduct(Product(2, "Doritos Nacho Cheese", 300, 0));
    inventory->addProduct(Product(3, "Lays Classic", 275, 3));
    inventory->addProduct(Product(4, "Ruffles Cheddar", 275, 5));
    inventory->addProduct(Product(5, "Pringles Original", 325, 15));
    inventory->addProduct(Product(6, "Snickers", 175, 5));
    inventory->addProduct(Product(7, "M&Ms Peanut", 175, 0));
    inventory->addProduct(Product(8, "Twix", 175, 12));
    inventory->addProduct(Product(9, "Reese's Cups", 175, 3));
    inventory->addProduct(Product(10, "Skittles", 150, 11));
    inventory->addProduct(Product(11, "Coca Cola", 200, 7));
    inventory->addProduct(Product(12, "Pepsi", 200, 3));
    inventory->addProduct(Product(13, "Mountain Dew", 200, 5));
    inventory->addProduct(Product(14, "Dr Pepper", 200, 5));
    inventory->addProduct(Product(15, "Sprite", 200, 12));
    inventory->addProduct(Product(16, "Trail Mix", 250, 14));
    inventory->addProduct(Product(17, "Granola Bar", 150, 0));
    inventory->addProduct(Product(18, "Mixed Nuts", 275, 5));
    inventory->addProduct(Product(19, "Dried Fruit", 225, 5));
    inventory->addProduct(Product(20, "Water Bottle", 150, 4));
}

void VendingMachine::displayProducts() const {
   displayHeader();
   std::cout << "Available Products:\n";
   inventory->displayInventory();
}

bool VendingMachine::selectProduct(int productId) {
   pushScreen();
   if (productId < 1 || productId > 20) {
       std::cout << "Invalid product selection.\n";
       std::cout << "Press Enter to continue...";
       std::cin.get();
       return false;
   }
   
   if (!inventory->checkAvailability(productId)) {
       displayOutOfStock();
       std::cout << "Press Enter to continue...";
       std::cin.get();
       return false;
   }
   
   displayPrice(productId);
   std::string productName;
   for(const auto& product : inventory->getProducts()) {
       if(product.getProductID() == productId) {
           productName = product.getName();
           break;
       }
   }
   currentTransaction = new Transaction(productId, productName);
   
   int insertedAmount = handleMoneyInsertion();
   if (insertedAmount > 0) {
       if(currentTransaction) {
           currentTransaction->initiateTransaction(insertedAmount);
           dispenseProduct(productId);
           return true;
       }
   } else if (insertedAmount == -1) {
       cancelTransaction();
   }
   return false;
}

bool VendingMachine::dispenseProduct(int productId) {
    if (!currentTransaction) {
        return false;
    }

    int price = inventory->getProductPrice(productId);
    if (currentBalance >= price) {
        currentTransaction->initiateTransaction(currentBalance);
        if (currentTransaction->completeTransaction(price)) {
            pushScreen();
            std::cout << "\nDispensing... press Enter to continue";
            std::cin.get();
            
            inventory->updateInventory(productId, -1);
            recordSale();
            
            int change = currentBalance - price;
            if (change > 0) {
                std::cout << "\nReturning change: $" << (change / 100) << "."
                         << (change % 100 < 10 ? "0" : "") << (change % 100) << "\n";
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
            }
            
            currentBalance = 0;
            delete currentTransaction;
            currentTransaction = nullptr;
            return true;
        }
    }
    return false;
}

void VendingMachine::cancelTransaction() {
   pushScreen();
   if (currentTransaction) {
       currentTransaction->cancelTransaction();
       if (currentBalance > 0) {
           returnChange();
       }
       delete currentTransaction;
       currentTransaction = nullptr;
   }
}

bool VendingMachine::accessAdminPanel(Admin* adminUser) {
   pushScreen();
   if (adminUser && adminUser->login("admin")) {
       adminUser->monitorSalesData(salesData);
       return true;
   }
   return false;
}

void VendingMachine::displayPrice(int productId) {
   int price = inventory->getProductPrice(productId);
   std::cout << "Price: $" << (price / 100) << "."
            << (price % 100 < 10 ? "0" : "") << (price % 100) << std::endl;
}

void VendingMachine::displayOutOfStock() {
   std::cout << "Product is out of stock.\n";
}

int VendingMachine::getCurrentBalance() const {
   return currentBalance;
}

bool VendingMachine::insertMoney(int amount) {
   if (amount > 2000) {
       std::cout << "Cannot accept more than $20.00\n";
       return false;
   }
   
   if (paymentProcessor->validateCurrency(amount)) {
       currentBalance = amount;
       return true;
   }
   return false;
}

int VendingMachine::returnChange() {
   int change = currentBalance;
   if (change > 0) {
       std::cout << "Returning change: $" << (change / 100) << "."
                << (change % 100 < 10 ? "0" : "") << (change % 100) << std::endl;
       currentBalance = 0;
   }
   return change;
}

int main() {
    VendingMachine machine(1);
    bool running = true;
    std::string input;
    
    while(running) {
        machine.pushScreen();
        machine.displayProducts();
        std::cout << "\nEnter product number or 99 for Admin Panel: ";
        
        std::getline(std::cin, input);
        
        try {
            int choice = std::stoi(input);
            
            if (choice == 99) {
                Admin admin;
                machine.accessAdminPanel(&admin);
                continue;
            }
            
            machine.selectProduct(choice);
        }
        catch (const std::invalid_argument&) {
            machine.pushScreen();
            std::cout << "Invalid input. Please try again.\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
    }
    
    return 0;
}