#ifndef INCOMEMANAGER_H
#define INCOMEMANAGER_H

#include <iostream>
#include <vector>
#include <iomanip>

#include "Income.h"
#include "DateMethods.h"
#include "AuxiliaryMethods.h"
#include "IncomeFile.h"

using namespace std;

class IncomeManager {

vector<Income> incomes;
IncomeFile incomeFile;

Income provideDataForIncome(string dateProvidedByUserOrTakenFromSystem);
string loadIncomeAmountFromKeyboard();
bool checkIfAmountFormatIsCorrect(string amount, vector<int> &numberOfCommasOrDotsInAmount);

public:
    IncomeManager(string nameOfIncomeFile) : incomeFile(nameOfIncomeFile) {
    incomes = incomeFile.loadAllIncomesForLoggedUser(2);
    };
    void addIncome();
    void printAllIncomes();
    void printIncomesForLoggedInUserSortedByDate();
 //   void extractIncomesAsOfProvidedPeriod();

};


#endif
