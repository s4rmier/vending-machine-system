#include "SalesData.h"
#include "Transaction.h"
#include <numeric>
#include <algorithm>
#include <iomanip>

SalesData::SalesData() : totalSales(0) {}

SalesData::~SalesData() {
    for(auto transaction : salesRecords) {
        delete transaction;
    }
    salesRecords.clear();
}

float SalesData::getDailySales() {
    float total = 0;
    for(const auto& transaction : salesRecords) {
        if(transaction && transaction->getStatus() == "Completed") {
            total += transaction->getAmountPaid() - transaction->getChangeReturned();
        }
    }
    return total;
}

float SalesData::getSalesByProduct(int productID) {
    float productTotal = 0;
    for(const auto& transaction : salesRecords) {
        if(transaction && 
           transaction->getStatus() == "Completed" && 
           transaction->getProductID() == productID) {
            productTotal += transaction->getAmountPaid() - transaction->getChangeReturned();
        }
    }
    return productTotal;
}

std::vector<Transaction*> SalesData::generateSalesReport() {
    return salesRecords;
}

void SalesData::recordTransactionData(Transaction* transaction) {
    if(transaction) {
        Transaction* newTransaction = new Transaction(*transaction);
        salesRecords.push_back(newTransaction);
        if(transaction->getStatus() == "Completed") {
            totalSales += transaction->getAmountPaid() - transaction->getChangeReturned();
        }
    }
}

void SalesData::displayTransactionReport() const {
    if (salesRecords.empty()) {
        std::cout << "No transactions recorded.\n";
        return;
    }

    std::cout << "\nTransaction Report\n";
    std::cout << std::string(40, '-') << "\n\n";

    for (const auto& transaction : salesRecords) {
        if (transaction && transaction->getStatus() == "Completed") {
            std::cout << "Product: " << transaction->getProductName() << "\n"
                      << "ID: " << transaction->getProductID() << "\n"
                      << "Paid: $" << std::fixed << std::setprecision(2) 
                      << transaction->getAmountPaid()/100.0 << "\n"
                      << "Change: $" << transaction->getChangeReturned()/100.0 << "\n"
                      << "Status: " << transaction->getStatus() << "\n\n";
        }
    }
    std::cout << std::string(40, '-') << "\n";
}