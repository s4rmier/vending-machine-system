#include "Admin.h"
#include <iostream>

using namespace std;

Admin::Admin(int id, const string& code)
    : adminID(id), accessCode(code), loginStatus(false) {
}

bool Admin::login(const string& accessCode) {
    if (this->accessCode == accessCode) {
        loginStatus = true;
        cout << "Login successful.\n";
        return true;
    }
    cout << "Login failed.\n";
    return false;
}

SalesData Admin::monitorSalesData() {
    if (loginStatus) {
        cout << "Accessing sales data...\n";
        SalesData salesData;  // Assuming default initialization
        return salesData;
    }
    cout << "Login required to access sales data.\n";
    return SalesData();  // Return an empty object if not logged in
}
