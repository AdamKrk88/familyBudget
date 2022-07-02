#ifndef EXPENSEMANAGER_H
#define EXPENSEMANAGER_H

#include <iostream>
#include <vector>
#include <iomanip>

#include "Expense.h"
#include "DateMethods.h"
#include "AuxiliaryMethods.h"
#include "ExpenseFile.h"

using namespace std;


class ExpenseManager {

vector<Expense> expenses;
ExpenseFile expenseFile;

Expense provideDataForExpense(string dateProvidedByUserOrTakenFromSystem);
string loadExpenseAmountFromKeyboard();
bool checkIfAmountFormatIsCorrect(string amount, vector<int> &numberOfCommasOrDotsInAmount);
vector<Expense> createSortedVectorOfExpensesForGivenPeriod(int startDateConvertedToIntFormat, int endDateConvertedToIntFormat);
void printExpensesListedInProvidedDataForLoggedInUser(vector<Expense> &expensesForGivenPeriod);

public:
    ExpenseManager(string nameOfExpenseFile) : expenseFile(nameOfExpenseFile) {
    expenses = expenseFile.loadAllExpensesForLoggedUser(2);
    };
    void addExpense();
    void printAllExpenses();
    void printExpenseBalanceForProvidedPeriod();
};


#endif
