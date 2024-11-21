#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

using namespace std;

class Transaction
{
private:
	int transactionID;
	int amountPaid;
	int changeReturned;
	string transactionStatus;

public:
	Transaction(int id);

	bool initiateTransaction(int amount);
	bool completeTransaction(int price);
	bool refundTransaction();
	bool cancelTransaction();
};

#endif
