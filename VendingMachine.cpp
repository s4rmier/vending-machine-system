#include "VendingMachine.h"
#include <iostream>
#include <iomanip>
#include <limits>

class VendingMachine {
private:
    int machineID;
    int currentBalance;
    
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

    void displayHeader() const{
        std::cout << "## University Vendo ##\n\n";
    }

    int handleMoneyInsertion() {
        bool inserting = true;
        int totalAmount = 0;
        
        while (inserting && totalAmount < 2000) {
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
                    std::cout << "Cannot accept more than $20.00\n";
                    continue;
                }
                totalAmount += amount;
                if (amount == 2000 || totalAmount >= 2000) {
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
        inventory->addProduct(Product(1, "Flaming Hot Cheetos", 300, 15));
        inventory->addProduct(Product(2, "Doritos Nacho Cheese", 300, 15));
        inventory->addProduct(Product(3, "Lays Classic", 275, 15));
        inventory->addProduct(Product(4, "Ruffles Cheddar", 275, 15));
        inventory->addProduct(Product(5, "Pringles Original", 325, 15));
        inventory->addProduct(Product(6, "Snickers", 175, 15));
        inventory->addProduct(Product(7, "M&Ms Peanut", 175, 15));
        inventory->addProduct(Product(8, "Twix", 175, 15));
        inventory->addProduct(Product(9, "Reese's Cups", 175, 15));
        inventory->addProduct(Product(10, "Skittles", 150, 15));
        inventory->addProduct(Product(11, "Coca Cola", 200, 15));
        inventory->addProduct(Product(12, "Pepsi", 200, 15));
        inventory->addProduct(Product(13, "Mountain Dew", 200, 15));
        inventory->addProduct(Product(14, "Dr Pepper", 200, 15));
        inventory->addProduct(Product(15, "Sprite", 200, 15));
        inventory->addProduct(Product(16, "Trail Mix", 250, 15));
        inventory->addProduct(Product(17, "Granola Bar", 150, 15));
        inventory->addProduct(Product(18, "Mixed Nuts", 275, 15));
        inventory->addProduct(Product(19, "Dried Fruit", 225, 15));
        inventory->addProduct(Product(20, "Water Bottle", 150, 15));
    }

public:
    VendingMachine(int id) 
        : machineID(id), currentBalance(0), currentTransaction(nullptr) {
        inventory = new Inventory(id);
        paymentProcessor = new PaymentProcessor();
        admin = new Admin();
        salesData = new SalesData();
        initializeProducts();
    }

    ~VendingMachine() {
        delete inventory;
        delete paymentProcessor;
        delete admin;
        delete salesData;
        if (currentTransaction) {
            delete currentTransaction;
        }
    }

    void displayProducts() const {
        displayHeader();
        std::cout << "Available Products:\n";
        inventory->displayInventory();
    }

    bool selectProduct(int productId) {
        if (!inventory->checkAvailability(productId)) {
            displayOutOfStock();
            return false;
        }
        
        displayPrice(productId);
        currentTransaction = new Transaction(productId);
        
        int insertedAmount = handleMoneyInsertion();
        if (insertedAmount > 0) {
            return insertMoney(insertedAmount);
        }
        return false;
    }

    bool dispenseProduct(int productId) {
        if (!currentTransaction) {
            return false;
        }

        int price = inventory->getProductPrice(productId);
        if (currentBalance >= price) {
            if (currentTransaction->completeTransaction(price)) {
                inventory->updateInventory(productId, -1);
                recordSale();
                std::cout << "\nDispensing... press Enter to continue";
                std::cin.get();
                std::cout << "\n";
                returnChange();
                delete currentTransaction;
                currentTransaction = nullptr;
                return true;
            }
        }
        return false;
    }

    void cancelTransaction() {
        if (currentTransaction) {
            currentTransaction->cancelTransaction();
            if (currentBalance > 0) {
                returnChange();
            }
            delete currentTransaction;
            currentTransaction = nullptr;
        }
    }

    bool accessAdminPanel(Admin* adminUser) {
        if (adminUser && adminUser->login("admin")) {
            adminUser->monitorSalesData();
            return true;
        }
        return false;
    }

    void displayPrice(int productId) {
        int price = inventory->getProductPrice(productId);
        std::cout << "Price: $" << (price / 100) << "."
                 << (price % 100 < 10 ? "0" : "") << (price % 100) << std::endl;
    }

    void displayOutOfStock() {
        std::cout << "Product is out of stock.\n";
    }

    int getCurrentBalance() const {
        return currentBalance;
    }

    bool insertMoney(int amount) {
        if (amount > 2000) {
            std::cout << "Cannot accept more than $20.00\n";
            return false;
        }
        
        if (paymentProcessor->validateCurrency(amount)) {
            currentBalance += amount;
            if (currentTransaction) {
                currentTransaction->initiateTransaction(currentBalance);
            }
            return true;
        }
        return false;
    }

    int returnChange() {
        int change = currentBalance;
        if (change > 0) {
            std::cout << "Returning change: $" << (change / 100) << "."
                     << (change % 100 < 10 ? "0" : "") << (change % 100) << std::endl;
            currentBalance = 0;
        }
        return change;
    }
};

int main() {
    VendingMachine machine(1);
    bool running = true;
    std::string input;
    
    while(running) {
        machine.displayProducts();
        std::cout << "\n0. Exit\n";
        std::cout << "\nPlease select a product number: ";
        
        std::getline(std::cin, input);
        
        try {
            int choice = std::stoi(input);
            
            if (choice == 0) {
                running = false;
                continue;
            }
            
            if (choice == 99) {
                Admin admin;
                machine.accessAdminPanel(&admin);
                continue;
            }
            
            if (machine.selectProduct(choice)) {
                if (!machine.dispenseProduct(choice)) {
                    machine.cancelTransaction();
                }
            }
        }
        catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please try again.\n";
        }
    }
    
    return 0;
}