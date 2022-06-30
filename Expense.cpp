#include "Expense.h"


int Expense :: getExpenseId() {
    return expenseId;
}
int Expense :: getUserId() {
    return userId;
}
string Expense :: getDate() {
    return date;
}
string Expense :: getExpenseDescription() {
    return expenseDescription;
}
string Expense :: getAmount() {
    return amount;
}

void Expense :: setExpenseId(int newExpenseId) {
    expenseId = newExpenseId;
}

void Expense :: setUserId(int newUserId) {
    userId = newUserId;
}

void Expense :: setDate(string newDate) {
    date = newDate;
}

void Expense :: setExpenseDescription(string newExpenseDescription) {
    expenseDescription = newExpenseDescription;
}

void Expense :: setAmount(string newAmount) {
    amount = newAmount;
}
