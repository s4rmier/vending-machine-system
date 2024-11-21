#include "Transaction.h"
#include <iostream>

Transaction::Transaction(int id)
    : transactionID(0), productID(id), amountPaid(0), 
      changeReturned(0), transactionStatus("Pending") {}

bool Transaction::initiateTransaction(int amount) {
    if (amount <= 0) {
        return false;
    }
    amountPaid = amount;
    transactionStatus = "Initiated";
    return true;
}

bool Transaction::completeTransaction(int price) {
    if (amountPaid >= price) {
        changeReturned = amountPaid - price;
        transactionStatus = "Completed";
        return true;
    }
    return false;
}

bool Transaction::refundTransaction() {
    if (transactionStatus == "Initiated" || transactionStatus == "Completed") {
        transactionStatus = "Refunded";
        return true;
    }
    return false;
}

bool Transaction::cancelTransaction() {
    if (transactionStatus == "Initiated") {
        transactionStatus = "Cancelled";
        return true;
    }
    return false;
}

int Transaction::getTransactionID() const {
    return transactionID;
}

int Transaction::getAmountPaid() const {
    return amountPaid;
}

int Transaction::getChangeReturned() const {
    return changeReturned;
}

int Transaction::getProductID() const {
    return productID;
}

std::string Transaction::getStatus() const {
    return transactionStatus;
}