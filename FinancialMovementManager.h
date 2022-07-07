#ifndef FINANCIALMOVEMENTMANAGER_H
#define FINANCIALMOVEMENTMANAGER_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <stdio.h>

#include "XmlFile.h"
#include "DateMethods.h"
#include "FinancialMovement.h"

using namespace std;


class FinancialMovementManager {

    const int LOGGED_USER_ID;
    const string TYPE_OF_FINANCIAL_MOVEMENT;

    FinancialMovement provideDataForFinancialMovement(string dateProvidedByUserOrTakenFromSystem);
    string loadFinancialMovementAmountFromKeyboard();
    bool checkIfAmountFormatIsCorrect(string amount, vector<int> &numberOfCommasOrDotsInAmount);
    vector<FinancialMovement> createSortedVectorOfFinancialMovementsForGivenPeriod(int startDateConvertedToIntFormat, int endDateConvertedToIntFormat);
    void printFinancialMovementsListedInProvidedDataForLoggedInUser(vector<FinancialMovement> &financialMovementsForGivenPeriod);
    string createNameForFirstColumn();
    void printFinancialMovementsSumOnScreen(double financialMovementSum);
    double calculateSumOfAmountsForFinancialMovements(vector<FinancialMovement> &financialMovementsForGivenPeriod);
    int calculateProperWidthForNameInFirstColumn(string firstColumnName);

protected:
    XmlFile *xmlFile;
    vector<FinancialMovement> financialMovements;

public:
    FinancialMovementManager(int loggedUserId, string typeOfFinancialMovement) : LOGGED_USER_ID(loggedUserId), TYPE_OF_FINANCIAL_MOVEMENT(typeOfFinancialMovement) {
        xmlFile = NULL;
    };

    int getLoggedUserId();
    void addFinancialMovement();
    double printFinancialMovementBalanceForProvidedPeriod(int startDateConvertedToIntFormat, int endDateConvertedToIntFormat);
    double printFinancialMovementBalanceForCurrentMonth();
    double printFinancialMovementBalanceForPreviousMonth();
};


#endif
