#pragma once

#include "Inventory.h"
#include "PaymentProcessor.h"
#include "Admin.h"
#include "SalesData.h"
#include "Transaction.h"

class VendingMachine {
private:
    int machineID;
    float currentBalance;
    
    Inventory* inventory;
    PaymentProcessor* paymentProcessor;
    Admin* admin;
    Transaction* currentTransaction;
    SalesData* salesData;

    void recordSale();
    void displayHeader();
    float handleMoneyInsertion();
    void initializeProducts();

public:
    VendingMachine(int id);
    ~VendingMachine();
    
    void displayProducts() const;
    bool selectProduct(int productId);
    bool dispenseProduct(int productId);
    void cancelTransaction();
    bool accessAdminPanel(Admin* adminUser);
    void displayPrice(int productId);
    float getProductPrice(int productId);
    void displayOutOfStock();
    float getCurrentBalance() const;
    bool insertMoney(float amount);
    float returnChange();
};