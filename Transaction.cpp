#include "Transaction.h"
#include <iostream>

using namespace std;

Transaction::Transaction(int id)
	:transactionID(id), amountPaid(0.0), changeReturned(0.0),
	transactionStatus("Pending") {}

bool Transaction::initiateTransaction(int amount) {
	if (amount <= 0) {
		cout << "Invalid payment amount. \n";
		return false;
	}
	amountPaid = amount;
	transactionStatus = "Initiated";
	return true;
}

bool Transaction::completeTransaction(int price) {
	if (amountPaid >= price) {
		changeReturned = amountPaid - price;
		transactionStatus = "Completed.";
		cout << "Transaction completed. Change: $" << changeReturned << "\n";
		return true;
	}
	else {
		cout << "Insufficient payment. Please add more.\n";
		return false;
	}
}

bool Transaction::refundTransaction() {
	if (transactionStatus == "Initiated" || transactionStatus == "Completed") {
		cout << "Transaction refunde. Amount: $" << amountPaid << "\n";
		transactionStatus = "Refunded";
		amountPaid = 0.0;
		return true;
	}
	return false;
}

bool Transaction::cancelTransaction() {
	if (transactionStatus == "Initiated") {
		cout << "Transaction canceled.\n";
			transactionStatus = "Cancelled";
		amountPaid = 0.0;
		return true;
	}
	return false;
}
