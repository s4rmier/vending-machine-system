#pragma once
#include "Transaction.h"
#include <vector>
#include <iostream>
#include <iomanip>

class SalesData {
private:
    float totalSales;
    std::vector<Transaction*> salesRecords;

public:
    SalesData();
    ~SalesData();
    float getDailySales();
    float getSalesByProduct(int productID);
    std::vector<Transaction*> generateSalesReport();
    void recordTransactionData(Transaction* transaction);
    void displayTransactionReport() const;
};