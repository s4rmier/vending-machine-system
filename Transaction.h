#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    static int nextTransactionID;
    int transactionID;
    std::string productName;
    int productID;
    int amountPaid;
    int changeReturned;
    std::string transactionStatus;

public:
    Transaction(int id, const std::string& name);
    Transaction(const Transaction& other);
    bool initiateTransaction(int amount);
    bool completeTransaction(int price);
    bool refundTransaction();
    bool cancelTransaction();
    
    int getTransactionID() const;
    int getAmountPaid() const;
    int getChangeReturned() const;
    int getProductID() const;
    std::string getStatus() const;
    std::string getProductName() const;
};

#endif