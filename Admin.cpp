#include "Admin.h"
#include "SalesData.h"
#include <iostream>
#include <iomanip>
#include <limits>

Admin::Admin() : adminID(0), accessCode("admin"), loginStatus(false) {}

bool Admin::login(std::string code) {
    if (code == accessCode) {
        loginStatus = true;
        return true;
    }
    return false;
}

void Admin::monitorSalesData(SalesData* salesData) {
    if (!loginStatus || !salesData) {
        return;
    }
    
    bool monitoring = true;
    while (monitoring) {
        std::cout << "\nAdmin Panel\n";
        std::cout << "1. Daily Sales Report\n";
        std::cout << "2. Product Sales Report\n";
        std::cout << "3. Transaction Report\n";
        std::cout << "4. Exit Admin Panel\n";
        
        std::string input;
        int choice = 0;
        std::cout << "Select option: ";
        std::getline(std::cin, input);
        
        try {
            choice = std::stoi(input);
            
            switch(choice) {
                case 1: {
                    float dailySales = salesData->getDailySales();
                    std::cout << "Total Daily Sales: $" << std::fixed 
                              << std::setprecision(2) << dailySales/100.0f << "\n";
                    break;
                }
                case 2: {
                    std::cout << "Enter Product ID: ";
                    std::getline(std::cin, input);
                    try {
                        int productId = std::stoi(input);
                        float productSales = salesData->getSalesByProduct(productId);
                        std::cout << "Product Sales: $" << std::fixed 
                                  << std::setprecision(2) << productSales/100.0f << "\n";
                    } catch (...) {
                        std::cout << "Invalid product ID\n";
                    }
                    break;
                }
                case 3: {
                    salesData->displayTransactionReport();
                    break;
                }
                case 4:
                    monitoring = false;
                    break;
                default:
                    std::cout << "Invalid option\n";
            }
        } catch (...) {
            std::cout << "Invalid input\n";
        }
        
        if (monitoring && choice != 4) {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
    }
}