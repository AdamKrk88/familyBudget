#include "Income.h"

int Income :: getIncomeId() {
    return incomeId;
}
int Income :: getUserId() {
    return userId;
}
string Income :: getDate() {
    return date;
}
string Income :: getIncomeDescription() {
    return incomeDescription;
}
string Income :: getAmount() {
    return amount;
}

void Income :: setIncomeId(int newIncomeId) {
    incomeId = newIncomeId;
}

void Income :: setUserId(int newUserId) {
    userId = newUserId;
}

void Income :: setDate(string newDate) {
    date = newDate;
}

void Income :: setIncomeDescription(string newIncomeDescription) {
    incomeDescription = newIncomeDescription;
}

void Income :: setAmount(string newAmount) {
    amount = newAmount;
}