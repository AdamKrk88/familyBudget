#ifndef EXPENSEFILE_H
#define EXPENSEFILE_H

#include <iostream>
#include <vector>

#include "AuxiliaryMethods.h"
#include "FinancialMovement.h"
#include "DateMethods.h"
#include "Markup.h"
#include "XmlFile.h"

using namespace std;


class ExpenseFile : public XmlFile {

    const string NAME_OF_EXPENSE_FILE;
    int lastExpenseId;

public:
    ExpenseFile(string nameOfExpenseFile) : NAME_OF_EXPENSE_FILE(nameOfExpenseFile) {
        lastExpenseId = 0;
    };

    void addFinancialMovementToFile(FinancialMovement financialMovement);
    vector<FinancialMovement> loadAllFinancialMovementsForLoggedUser(int loggedUserId);
    int getLastItemId();
};


#endif
