#pragma once
#include "Transaction.h"
#include <vector>

class SalesData {
private:
    float totalSales;
    std::vector<Transaction*> salesRecords;

public:
    SalesData();
    float getDailySales();
    float getSalesByProduct(int productID);
    std::vector<Transaction*> generateSalesReport();
    void recordTransactionData(Transaction* transaction);
};