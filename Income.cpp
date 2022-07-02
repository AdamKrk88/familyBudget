#include "Income.h"

int Income :: getIncomeId() {
    return incomeId;
}
int Income :: getUserId() {
    return userId;
}
int Income :: getDate() {
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

void Income :: setDate(int newDate) {
    date = newDate;
}

void Income :: setIncomeDescription(string newIncomeDescription) {
    incomeDescription = newIncomeDescription;
}

void Income :: setAmount(string newAmount) {
    amount = newAmount;
}

 bool Income :: operator < (const Income &income) const {
    return (this -> date < income.date);
 }
