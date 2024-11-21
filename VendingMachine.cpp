#include "VendingMachine.h"
#include <iostream>
#include <iomanip>
#include <limits>

class VendingMachine {
private:
    int machineID;
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

    void displayHeader() const{
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

public:
    VendingMachine(int id) 
        : machineID(id), currentBalance(0.0), currentTransaction(nullptr) {
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
        std::cout << std::setfill('0') << std::fixed << std::setprecision(2);
        inventory->displayInventory();
    }

    bool selectProduct(int productId) {
        if (!inventory->checkAvailability(productId)) {
            displayOutOfStock();
            return false;
        }
        
        displayPrice(productId);
        currentTransaction = new Transaction(productId);
        
        float insertedAmount = handleMoneyInsertion();
        if (insertedAmount > 0) {
            return insertMoney(insertedAmount);
        }
        return false;
    }

    bool dispenseProduct(int productId) {
        if (!currentTransaction) {
            return false;
        }

        float price = inventory->getProductPrice(productId);
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
        float price = inventory->getProductPrice(productId);
        std::cout << "Price: $" << std::fixed << std::setprecision(2) 
                 << price << std::endl;
    }

    void displayOutOfStock() {
        std::cout << "Product is out of stock.\n";
    }

    float getCurrentBalance() const {
        return currentBalance;
    }

    bool insertMoney(float amount) {
        if (amount > 20.0f) {
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

    float returnChange() {
        float change = currentBalance;
        if (change > 0) {
            std::cout << "Returning change: $" << std::fixed << std::setprecision(2) 
                     << change << std::endl;
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