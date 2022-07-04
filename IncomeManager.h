#ifndef INCOMEMANAGER_H
#define INCOMEMANAGER_H

#include <iostream>
#include <vector>
#include <iomanip>

#include "Income.h"
#include "DateMethods.h"
#include "AuxiliaryMethods.h"
#include "IncomeFile.h"
#include "BalanceManager.h"

using namespace std;

class IncomeManager : private BalanceManager {

    vector<Income> incomes;
    IncomeFile incomeFile;
//const int LOGGED_USER_ID;

    Income provideDataForIncome(string dateProvidedByUserOrTakenFromSystem);
    string loadIncomeAmountFromKeyboard();
    bool checkIfAmountFormatIsCorrect(string amount, vector<int> &numberOfCommasOrDotsInAmount);
    void printIncomesListedInProvidedDataForLoggedInUser(vector<Income> &incomesForGivenPeriod);
    vector<Income> createSortedVectorOfIncomesForGivenPeriod(int startDateConvertedToIntFormat, int endDateConvertedToIntFormat);

public:
    IncomeManager(string nameOfIncomeFile, int loggedUserId) : incomeFile(nameOfIncomeFile), BalanceManager(loggedUserId) {
        incomes = incomeFile.loadAllIncomesForLoggedUser(getLoggedUserId());
    };
    void addIncome();
    void printAllIncomes();
    double printIncomeBalanceForProvidedPeriod(int startDateConvertedToIntFormat, int endDateConvertedToIntFormat);
    double printIncomeBalanceForCurrentMonth();
    double printIncomeBalanceForPreviousMonth();

};


#endif
