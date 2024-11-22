#include "PaymentProcessor.h"

PaymentProcessor::PaymentProcessor() : totalAmount(0) {}

bool PaymentProcessor::validateCurrency(float inputAmount) {
    const int validAmounts[] = {1, 5, 10, 25, 100, 500, 1000, 2000};
    
    for (int amount : validAmounts) {
        if (inputAmount == amount) {
            return true;
        }
    }
    return false;
}

bool PaymentProcessor::processPayment(float amount) {
    if (amount <= 0 || amount > 2000) {
        return false;
    }
    totalAmount += amount;
    return true;
}

float PaymentProcessor::returnChange(float changeAmount) {
    if (changeAmount <= totalAmount) {
        totalAmount -= changeAmount;
        return changeAmount;
    }
    return 0;
}

bool PaymentProcessor::cancelPayment() {
    float refund = totalAmount;
    totalAmount = 0;
    return refund > 0;
}