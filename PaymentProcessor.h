#pragma once

class PaymentProcessor {
private:
    float totalAmount;

public:
    PaymentProcessor();
    bool validateCurrency(float inputAmount);
    bool processPayment(float amount);
    float returnChange(float changeAmount);
    bool cancelPayment();
};