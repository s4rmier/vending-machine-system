#pragma once
#include "SalesData.h"
#include <string>

class Admin {
private:
    int adminID;
    std::string accessCode;
    bool loginStatus;

public:
    Admin();
    bool login(std::string code);
    void monitorSalesData(SalesData* salesData);
};
