#ifndef EXPENSEMANAGER_H
#define EXPENSEMANAGER_H

#include <iostream>
#include <vector>
#include <iomanip>

#include "Expense.h"
#include "DateMethods.h"
#include "AuxiliaryMethods.h"
#include "ExpenseFile.h"
#include "BalanceManager.h"

using namespace std;


class ExpenseManager : private BalanceManager {

    vector<Expense> expenses;
    ExpenseFile expenseFile;
//const int LOGGED_USER_ID;

    Expense provideDataForExpense(string dateProvidedByUserOrTakenFromSystem);
    string loadExpenseAmountFromKeyboard();
    bool checkIfAmountFormatIsCorrect(string amount, vector<int> &numberOfCommasOrDotsInAmount);
    vector<Expense> createSortedVectorOfExpensesForGivenPeriod(int startDateConvertedToIntFormat, int endDateConvertedToIntFormat);
    void printExpensesListedInProvidedDataForLoggedInUser(vector<Expense> &expensesForGivenPeriod);

public:
    ExpenseManager(string nameOfExpenseFile, int loggedUserId) : expenseFile(nameOfExpenseFile), BalanceManager(loggedUserId) {
        expenses = expenseFile.loadAllExpensesForLoggedUser(getLoggedUserId());
    };
    void addExpense();
    void printAllExpenses();
    double printExpenseBalanceForProvidedPeriod(int startDateConvertedToIntFormat, int endDateConvertedToIntFormat);
    double printExpenseBalanceForCurrentMonth();
    double printExpenseBalanceForPreviousMonth();
};


#endif
