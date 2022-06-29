#ifndef INCOMEMANAGER_H
#define INCOMEMANAGER_H

#include <iostream>
#include <vector>

#include "Income.h"
#include "DateMethods.h"
#include "AuxiliaryMethods.h"

using namespace std;

class IncomeManager {

vector<Income> incomes;

int loadIdForNewIncome();
Income provideDataForIncome(string dateProvidedByUserOrTakenFromSystem);
string loadIncomeAmountFromKeyboard();
bool checkIfAmountFormatIsCorrect(string amount, vector<int> &numberOfCommasOrDotsInAmount);

public:
    void addIncome();
    void printAllIncomes();

};


#endif
