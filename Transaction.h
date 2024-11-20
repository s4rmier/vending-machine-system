#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

using namespace std;

class Transaction
{
private:
	int transactionID;
	float amountPaid;
	float changeReturned;
	string transactionStatus;

public:
	Transaction(int id);

	bool initiateTransaction(float amount);
	bool completeTransaction(float price);
	bool refundTransaction();
	bool cancelTransaction();
};

#endif
