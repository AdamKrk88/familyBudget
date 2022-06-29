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
string Income :: getItemDescription() {
    return itemDescription;
}
double Income :: getAmount() {
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

void Income :: setItemDescription(string newItemDescription) {
    itemDescription = newItemDescription;
}

void Income :: setAmount(double newAmount) {
    amount = newAmount;
}
