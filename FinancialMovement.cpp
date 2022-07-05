#include "FinancialMovement.h"

int FinancialMovement :: getFinancialMovementId() {
    return financialMovementId;
}
int FinancialMovement :: getUserId() {
    return userId;
}
int FinancialMovement :: getDate() {
    return date;
}
string FinancialMovement :: getFinancialMovementDescription() {
    return financialMovementDescription;
}
string FinancialMovement :: getAmount() {
    return amount;
}

void FinancialMovement :: setFinancialMovementId(int newFinancialMovementId) {
    financialMovementId = newFinancialMovementId;
}

void FinancialMovement :: setUserId(int newUserId) {
    userId = newUserId;
}

void FinancialMovement :: setDate(int newDate) {
    date = newDate;
}

void FinancialMovement :: setFinancialMovementDescription(string newFinancialMovementDescription) {
    financialMovementDescription = newFinancialMovementDescription;
}

void FinancialMovement :: setAmount(string newAmount) {
    amount = newAmount;
}

bool FinancialMovement :: operator < (const FinancialMovement &financialMovement) const {
    return (this -> date < financialMovement.date);
}
