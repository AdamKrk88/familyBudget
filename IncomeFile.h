#ifndef INCOMEFILE_H
#define INCOMEFILE_H

#include <iostream>
#include <vector>

#include "AuxiliaryMethods.h"
#include "Income.h"
#include "DateMethods.h"
#include "Markup.h"

using namespace std;


class IncomeFile {

    const string NAME_OF_INCOME_FILE;
    int lastIncomeId;

public:
    IncomeFile(string nameOfIncomeFile) : NAME_OF_INCOME_FILE(nameOfIncomeFile) {
        lastIncomeId = 0;
    };
    void addIncomeToFile(Income income);
    vector<Income> loadAllIncomesForLoggedUser(int loggedUserId);
    int getLastIncomeId();

};


#endif
