#ifndef INCOMEFILE_H
#define INCOMEFILE_H

#include <iostream>
#include <vector>

#include "AuxiliaryMethods.h"
#include "FinancialMovement.h"
#include "DateMethods.h"
#include "Markup.h"
#include "XmlFile.h"

using namespace std;


class IncomeFile : public XmlFile {

    const string NAME_OF_INCOME_FILE;
    int lastIncomeId;

public:
    IncomeFile(string nameOfIncomeFile) : NAME_OF_INCOME_FILE(nameOfIncomeFile) {
        lastIncomeId = 0;
    };

    void addFinancialMovementToFile(FinancialMovement financialMovement);
    vector<FinancialMovement> loadAllFinancialMovementsForLoggedUser(int loggedUserId);
    int getLastItemId();
};


#endif
