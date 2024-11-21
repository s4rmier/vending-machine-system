#pragma once

#include "Inventory.h"
#include "PaymentProcessor.h"
#include "Admin.h"
#include "SalesData.h"
#include "Transaction.h"

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