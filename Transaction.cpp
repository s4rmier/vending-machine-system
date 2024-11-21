#include "Transaction.h"

Transaction::Transaction(int id, const std::string& name)
    : transactionID(id),
      productID(id),
      productName(name),
      amountPaid(0),
      changeReturned(0),
      transactionStatus("Pending") {}

Transaction::Transaction(const Transaction& other)
    : transactionID(other.transactionID),
      productID(other.productID),
      productName(other.productName),
      amountPaid(other.amountPaid),
      changeReturned(other.changeReturned),
      transactionStatus(other.transactionStatus) {}

bool Transaction::initiateTransaction(int amount) {
    if (amount > 0) {
        amountPaid = amount;
        transactionStatus = "Initiated";
        return true;
    }
    return false;
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
    transactionStatus = "Refunded";
    return true;
}

bool Transaction::cancelTransaction() {
    transactionStatus = "Cancelled";
    return true;
}

int Transaction::getTransactionID() const { return transactionID; }
int Transaction::getAmountPaid() const { return amountPaid; }
int Transaction::getChangeReturned() const { return changeReturned; }
int Transaction::getProductID() const { return productID; }
std::string Transaction::getStatus() const { return transactionStatus; }
std::string Transaction::getProductName() const { return productName; }