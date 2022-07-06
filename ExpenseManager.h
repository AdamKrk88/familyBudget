#ifndef EXPENSEMANAGER_H
#define EXPENSEMANAGER_H

#include <iostream>
#include <vector>
#include <iomanip>

#include "DateMethods.h"
#include "AuxiliaryMethods.h"
#include "ExpenseFile.h"
#include "FinancialMovementManager.h"

using namespace std;


class ExpenseManager : public FinancialMovementManager {

    ExpenseFile expenseFile;

public:
    ExpenseManager(string nameOfExpenseFile, int loggedUserId) : expenseFile(nameOfExpenseFile), FinancialMovementManager(loggedUserId, "expense") {
        financialMovements = expenseFile.loadAllFinancialMovementsForLoggedUser(getLoggedUserId());
        xmlFile = &expenseFile;
    };
};


#endif
