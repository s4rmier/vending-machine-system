#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    int transactionID;
    int amountPaid;
    int changeReturned;
    std::string transactionStatus;
    int productID;

public:
    Transaction(int id);
    bool initiateTransaction(int amount);
    bool completeTransaction(int price);
    bool refundTransaction();
    bool cancelTransaction();
    
    int getTransactionID() const;
    int getAmountPaid() const;
    int getChangeReturned() const;
    int getProductID() const;
    std::string getStatus() const;
};

#endif
