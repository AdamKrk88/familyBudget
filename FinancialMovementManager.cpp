#include "FinancialMovementManager.h"

int FinancialMovementManager :: getLoggedUserId() {
    return LOGGED_USER_ID;
}


void FinancialMovementManager :: addFinancialMovement() {

    system("cls");
    FinancialMovement financialMovement;
    string dateAsOfTodayOrPast = "";
    string dateProvidedByUserOrTakenFromSystem = "";
    cout << "Provide date for your " << TYPE_OF_FINANCIAL_MOVEMENT << " - enter \"today\" or \"past\": ";
    cin >> dateAsOfTodayOrPast;
    cin.sync();

    if (dateAsOfTodayOrPast == "today") {
        dateProvidedByUserOrTakenFromSystem = DateMethods :: getCurrentTimeFromSystem();
        financialMovement = provideDataForFinancialMovement(dateProvidedByUserOrTakenFromSystem);
        financialMovements.push_back(financialMovement);
        xmlFile -> addFinancialMovementToFile(financialMovement);
    } else if(dateAsOfTodayOrPast == "past") {
        cout << "Enter date in format YYYY-MM-DD: ";
        dateProvidedByUserOrTakenFromSystem = DateMethods :: loadDateFromKeyboard();
        if(dateProvidedByUserOrTakenFromSystem != "") {
            financialMovement = provideDataForFinancialMovement(dateProvidedByUserOrTakenFromSystem);
            financialMovements.push_back(financialMovement);
            xmlFile -> addFinancialMovementToFile(financialMovement);
        }
    } else {
        cout << "Not correct. Return to User menu" << endl;
    }

}


FinancialMovement FinancialMovementManager :: provideDataForFinancialMovement(string dateProvidedByUserOrTakenFromSystem) {

    FinancialMovement financialMovement;

    financialMovement.setFinancialMovementId(xmlFile -> getLastItemId() + 1);
    financialMovement.setUserId(getLoggedUserId());
    financialMovement.setDate(DateMethods :: convertDateFromStringToInt(dateProvidedByUserOrTakenFromSystem));

    string financialMovementDescription;
    cout << endl << "Enter your " << TYPE_OF_FINANCIAL_MOVEMENT << " description: ";
    getline(cin, financialMovementDescription);
    financialMovementDescription = AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(financialMovementDescription);
    financialMovement.setFinancialMovementDescription(financialMovementDescription);

    string amount;
    amount = loadFinancialMovementAmountFromKeyboard();
    financialMovement.setAmount(amount);

    return financialMovement;

}

string FinancialMovementManager :: loadFinancialMovementAmountFromKeyboard() {

    string amount = "";
    vector<int> numberOfCommasOrDotsInAmount;
    cout << "Enter " << TYPE_OF_FINANCIAL_MOVEMENT << " amount: ";
    getline(cin, amount);
    amount = AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(amount);

    while(true) {
        numberOfCommasOrDotsInAmount = AuxiliaryMethods :: calculateHowManyDotsOrCommasIsInTextLine(amount);
        if(checkIfAmountFormatIsCorrect(amount,numberOfCommasOrDotsInAmount)) {
            if(numberOfCommasOrDotsInAmount[1] == 1) {
                amount = AuxiliaryMethods :: replaceCommaByDot(amount);
            }

            break;
        } else {
            cout << "Amount provided is not correct. Provide " << TYPE_OF_FINANCIAL_MOVEMENT << " amount: ";
            getline(cin, amount);
            amount = AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(amount);
        }
    }
    return amount;
}


bool FinancialMovementManager :: checkIfAmountFormatIsCorrect(string amount, vector<int> &numberOfCommasOrDotsInAmount) {

    int amountSize = amount.size();
    int numberOfDots = numberOfCommasOrDotsInAmount[0];
    int numberOfCommas = numberOfCommasOrDotsInAmount[1];

    if(!isdigit(amount[0]) || !isdigit(amount[amountSize - 1])) {
        return false;
    }

    if(numberOfCommas > 1 || numberOfDots > 1 || (numberOfCommas == 1 && numberOfDots == 1))
        return false;

    if(numberOfCommas == 1 || numberOfDots == 1) {
        size_t positionOfComma = amount.find(',');
        size_t positionOfDot = amount.find('.');
        size_t positiionOfSign;

        if(positionOfComma != string :: npos) {
            positiionOfSign = positionOfComma;
        } else {
            positiionOfSign = positionOfDot;
        }

        for(int i = 1; i < positiionOfSign; i++) {
            if(!isdigit(amount[i])) {
                return false;
            }
        }

        for(int i = positiionOfSign + 1; i < amountSize - 1; i++) {
            if(!isdigit(amount[i])) {
                return false;
            }
        }
    }

    else if(numberOfCommas == 0 && numberOfDots == 0) {
        for(int i = 1; i < amountSize - 1; i++) {
            if(!isdigit(amount[i])) {
                return false;
            }
        }
    }

    else {
        return false;
    }

    return true;
}


void FinancialMovementManager :: printAllFinancialMovements() {

    for(int i = 0; i < financialMovements.size(); i++) {
        cout << financialMovements[i].getFinancialMovementId() << endl;
        cout << financialMovements[i].getUserId() << endl;
        cout << financialMovements[i].getDate() << endl;
        cout << financialMovements[i].getFinancialMovementDescription() << endl;
        cout << financialMovements[i].getAmount() << endl;
    }
}


void FinancialMovementManager :: printFinancialMovementsListedInProvidedDataForLoggedInUser(vector<FinancialMovement> &financialMovementsForGivenPeriod) {

    string firstColumnName = createNameForFirstColumn();
    string secondColumnName = "Description";
    string thirdColumnName = "Amount";

    int firstColumnNameWidth = firstColumnName.size();
    int secondColumnNameWidth = secondColumnName.size();
    int thirdColumnNameWidth = thirdColumnName.size();
    int separatorWidth = 1;

    string separator = "|";
    string fixedSpaceInFirstandThirdColumns = string(4,' ');
    string fixedSpaceInSecondColumn = string(15,' ');
    int lengthOfFixedSpaceInFirstandThirdColumns = fixedSpaceInFirstandThirdColumns.size();
    int lengthOfFixedSpaceInSecondColumn = fixedSpaceInSecondColumn.size();

    int totalWidth = firstColumnNameWidth + lengthOfFixedSpaceInFirstandThirdColumns * 2 + secondColumnNameWidth + lengthOfFixedSpaceInSecondColumn * 2 + thirdColumnNameWidth + lengthOfFixedSpaceInFirstandThirdColumns * 2 + 2*separatorWidth;
    string line = separator + string(totalWidth,'-') + separator;

    cout << line;
    cout << '\n';
    cout << separator << fixedSpaceInFirstandThirdColumns  << firstColumnName << fixedSpaceInFirstandThirdColumns
         << separator << fixedSpaceInSecondColumn  << secondColumnName << fixedSpaceInSecondColumn
         << separator << fixedSpaceInFirstandThirdColumns  << thirdColumnName << fixedSpaceInFirstandThirdColumns
         << separator;
    cout << '\n' << line;

    if(financialMovementsForGivenPeriod.empty()) {
        cout << endl << separator << right << setw(4) << "No " << TYPE_OF_FINANCIAL_MOVEMENT << "s" << string(line.size() - 4 - TYPE_OF_FINANCIAL_MOVEMENT.size() - 1 - 2*separatorWidth,' ') << separator;
        cout << endl << line;
    }

    else {
        int numberOfFinancialMovementsRegistered = financialMovementsForGivenPeriod.size();

        for(int i = 0; i < numberOfFinancialMovementsRegistered; i++) {
            cout << endl << separator << " " << left << setw(firstColumnNameWidth + lengthOfFixedSpaceInFirstandThirdColumns*2 - 2) << DateMethods :: convertDateFromIntToStringInCorrectFormat(financialMovementsForGivenPeriod[i].getDate()) << " "
                 << separator << " " << left << setw(secondColumnNameWidth + lengthOfFixedSpaceInSecondColumn*2 -2) << financialMovementsForGivenPeriod[i].getFinancialMovementDescription() << " "
                 << separator << " " << left << setw(thirdColumnNameWidth + lengthOfFixedSpaceInFirstandThirdColumns*2 - 2) << financialMovementsForGivenPeriod[i].getAmount() << " "
                 << separator;
        }
        cout << endl << line;
    }
}


double FinancialMovementManager :: printFinancialMovementBalanceForProvidedPeriod(int startDateConvertedToIntFormat, int endDateConvertedToIntFormat) {

    vector<FinancialMovement> financialMovementsForGivenPeriod = createSortedVectorOfFinancialMovementsForGivenPeriod(startDateConvertedToIntFormat, endDateConvertedToIntFormat);
    double financialMovementSum = 0;

    for(int i = 0; i < financialMovementsForGivenPeriod.size(); i++) {
        financialMovementSum = financialMovementSum + atof(financialMovementsForGivenPeriod[i].getAmount().c_str());
    }

    printFinancialMovementsListedInProvidedDataForLoggedInUser(financialMovementsForGivenPeriod);

    if(AuxiliaryMethods ::checkIfDoubleNumberIsInteger(financialMovementSum)) {
        cout << endl << "Sum of " << TYPE_OF_FINANCIAL_MOVEMENT << "s is " << setprecision(0) << fixed << financialMovementSum << " zl" << endl << endl << endl;
    }

    else {
        cout << endl << "Sum of " << TYPE_OF_FINANCIAL_MOVEMENT << "s is " << setprecision(2) << fixed << financialMovementSum << " zl" << endl << endl << endl;
    }

    return financialMovementSum;
}


vector<FinancialMovement> FinancialMovementManager :: createSortedVectorOfFinancialMovementsForGivenPeriod(int startDateConvertedToIntFormat, int endDateConvertedToIntFormat) {

    vector<FinancialMovement> financialMovementsForGivenPeriod = financialMovements;
    int lengthOfFinancialMovementsForGivenPeriodVector = financialMovementsForGivenPeriod.size();
    int indexNumber = 0;

    if(!financialMovementsForGivenPeriod.empty()) {
        sort(financialMovementsForGivenPeriod.begin(), financialMovementsForGivenPeriod.end());

        while(financialMovementsForGivenPeriod[indexNumber].getDate() < startDateConvertedToIntFormat) {
            indexNumber++;

            if(indexNumber == lengthOfFinancialMovementsForGivenPeriodVector) {
                break;
            }
        }

        if(indexNumber == 1) {
            financialMovementsForGivenPeriod.erase(financialMovementsForGivenPeriod.begin());
        } else if(indexNumber > 1) {
            financialMovementsForGivenPeriod.erase(financialMovementsForGivenPeriod.begin(),financialMovementsForGivenPeriod.begin() + indexNumber);
        }
        indexNumber = 0;
        lengthOfFinancialMovementsForGivenPeriodVector = financialMovementsForGivenPeriod.size();
    }

    if(!financialMovementsForGivenPeriod.empty()) {
        while(financialMovementsForGivenPeriod[indexNumber].getDate() <= endDateConvertedToIntFormat) {
            indexNumber++;

            if(indexNumber == lengthOfFinancialMovementsForGivenPeriodVector) {
                break;
            }
        }

        if(lengthOfFinancialMovementsForGivenPeriodVector - indexNumber != 0) {
            while(financialMovementsForGivenPeriod[indexNumber].getDate() > endDateConvertedToIntFormat) {
                financialMovementsForGivenPeriod.erase(financialMovementsForGivenPeriod.begin() + indexNumber);
                lengthOfFinancialMovementsForGivenPeriodVector = financialMovementsForGivenPeriod.size();
                if(lengthOfFinancialMovementsForGivenPeriodVector - indexNumber == 0) {
                    break;
                }
            }
        }
    }

    return financialMovementsForGivenPeriod;
}


double FinancialMovementManager :: printFinancialMovementBalanceForCurrentMonth() {

    vector<int> currentDate = DateMethods :: convertDateInStringToIntVector(DateMethods :: getCurrentTimeFromSystem());
    int numberOfDaysForCurrentMonth = DateMethods :: calculateNumberOfDaysForProvidedMonth(currentDate[1], currentDate[0]);

    string startDate = AuxiliaryMethods :: convertFromIntToString(currentDate[0]) + DateMethods :: convertMonthOrDayToProperFormat(currentDate[1]) + "01";
    string endDate = AuxiliaryMethods :: convertFromIntToString(currentDate[0]) + DateMethods :: convertMonthOrDayToProperFormat(currentDate[1]) + AuxiliaryMethods :: convertFromIntToString(numberOfDaysForCurrentMonth);

    int startDateConvertedToIntFormat = AuxiliaryMethods :: convertFromStringToInt(startDate);
    int endDateConvertedToIntFormat = AuxiliaryMethods :: convertFromStringToInt(endDate);

    vector<FinancialMovement> financialMovementsForGivenPeriod = createSortedVectorOfFinancialMovementsForGivenPeriod(startDateConvertedToIntFormat, endDateConvertedToIntFormat);

    double financialMovementSum = 0;

    for(int i = 0; i < financialMovementsForGivenPeriod.size(); i++) {
        financialMovementSum = financialMovementSum + atof(financialMovementsForGivenPeriod[i].getAmount().c_str());
    }

    printFinancialMovementsListedInProvidedDataForLoggedInUser(financialMovementsForGivenPeriod);

     if(AuxiliaryMethods ::checkIfDoubleNumberIsInteger(financialMovementSum)) {
        cout << endl << "Sum of " << TYPE_OF_FINANCIAL_MOVEMENT << "s is " << setprecision(0) << fixed << financialMovementSum << " zl" << endl << endl;
    }

    else {
        cout << endl << "Sum of " << TYPE_OF_FINANCIAL_MOVEMENT << "s is " << setprecision(2) << fixed << financialMovementSum << " zl" << endl << endl;
    }

    return financialMovementSum;
}


double FinancialMovementManager :: printFinancialMovementBalanceForPreviousMonth() {

    vector<int> currentDate = DateMethods :: convertDateInStringToIntVector(DateMethods :: getCurrentTimeFromSystem());

    int previousMonth = 0;
    int year = 0;

    if(currentDate[1] != 1) {
        previousMonth = currentDate[1] - 1;
        year = currentDate[0];
    }

    else {
        previousMonth = 12;
        year = currentDate[0] - 1;
    }

    int numberOfDaysForPreviousMonth = DateMethods :: calculateNumberOfDaysForProvidedMonth(previousMonth, year);

    string startDate = AuxiliaryMethods :: convertFromIntToString(year) + DateMethods :: convertMonthOrDayToProperFormat(previousMonth) + "01";
    string endDate = AuxiliaryMethods :: convertFromIntToString(year) + DateMethods :: convertMonthOrDayToProperFormat(previousMonth) + AuxiliaryMethods :: convertFromIntToString(numberOfDaysForPreviousMonth);

    int startDateConvertedToIntFormat = AuxiliaryMethods :: convertFromStringToInt(startDate);
    int endDateConvertedToIntFormat = AuxiliaryMethods :: convertFromStringToInt(endDate);

    vector<FinancialMovement> financialMovementsForGivenPeriod = createSortedVectorOfFinancialMovementsForGivenPeriod(startDateConvertedToIntFormat, endDateConvertedToIntFormat);

    double financialMovementSum = 0;

    for(int i = 0; i < financialMovementsForGivenPeriod.size(); i++) {
        financialMovementSum = financialMovementSum + atof(financialMovementsForGivenPeriod[i].getAmount().c_str());
    }

    printFinancialMovementsListedInProvidedDataForLoggedInUser(financialMovementsForGivenPeriod);

    if(AuxiliaryMethods ::checkIfDoubleNumberIsInteger(financialMovementSum)) {
        cout << endl << "Sum of " << TYPE_OF_FINANCIAL_MOVEMENT << "s is " << setprecision(0) << fixed << financialMovementSum << " zl" << endl << endl << endl;
    }

    else {
        cout << endl << "Sum of " << TYPE_OF_FINANCIAL_MOVEMENT << "s is " << setprecision(2) << fixed << financialMovementSum << " zl" << endl << endl << endl;
    }

    return financialMovementSum;
}


string FinancialMovementManager :: createNameForFirstColumn() {

    if(TYPE_OF_FINANCIAL_MOVEMENT == "expense") {
        return "Expense date";
    }

    else {
        return "Income date";
    }
}
