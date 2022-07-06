#ifndef INCOMEMANAGER_H
#define INCOMEMANAGER_H

#include <iostream>
#include <vector>
#include <iomanip>

#include "DateMethods.h"
#include "AuxiliaryMethods.h"
#include "IncomeFile.h"
#include "FinancialMovementManager.h"

using namespace std;


class IncomeManager : public FinancialMovementManager {

    IncomeFile incomeFile;

public:
    IncomeManager(string nameOfIncomeFile, int loggedUserId) : incomeFile(nameOfIncomeFile), FinancialMovementManager(loggedUserId, "income") {
        financialMovements = incomeFile.loadAllFinancialMovementsForLoggedUser(getLoggedUserId());
        xmlFile = &incomeFile;
    };
};


#endif
