#ifndef EXPENSEFILE_H
#define EXPENSEFILE_H

#include <iostream>
#include <vector>

#include "AuxiliaryMethods.h"
#include "Expense.h"
#include "DateMethods.h"
#include "Markup.h"

using namespace std;


class ExpenseFile {

    const string NAME_OF_EXPENSE_FILE;
    int lastExpenseId;

public:
    ExpenseFile(string nameOfExpenseFile) : NAME_OF_EXPENSE_FILE(nameOfExpenseFile) {
    lastExpenseId = 0;
    };
    void addExpenseToFile(Expense income);
    vector<Expense> loadAllExpensesForLoggedUser(int loggedUserId);
    int getLastExpenseId();
};


#endif
