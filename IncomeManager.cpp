#include "IncomeManager.h"

void IncomeManager :: addIncome() {

    system("cls");
    Income income;
    string dateAsOfTodayOrPast = "";
    string dateProvidedByUserOrTakenFromSystem = "";
    cout << "Provide date for your income - enter \"today\" or \"past\": ";
    cin >> dateAsOfTodayOrPast;
    cin.sync();

    if (dateAsOfTodayOrPast == "today") {
        dateProvidedByUserOrTakenFromSystem = DateMethods :: getCurrentTimeFromSystem();
        income = provideDataForIncome(dateProvidedByUserOrTakenFromSystem);
        incomes.push_back(income);
        incomeFile.addIncomeToFile(income);
    } else if(dateAsOfTodayOrPast == "past") {
        cout << "Enter date in format YYYY-MM-DD: ";
        dateProvidedByUserOrTakenFromSystem = DateMethods :: loadDateFromKeyboard();
        if(dateProvidedByUserOrTakenFromSystem != "") {
            income = provideDataForIncome(dateProvidedByUserOrTakenFromSystem);
            incomes.push_back(income);
            incomeFile.addIncomeToFile(income);
        }
    } else {
        cout << "Not correct. Return to User menu" << endl;
    }

}


Income IncomeManager :: provideDataForIncome(string dateProvidedByUserOrTakenFromSystem) {

    Income income;

    income.setIncomeId(incomeFile.getLastIncomeId() + 1);
    income.setUserId(getLoggedUserId());
    income.setDate(DateMethods :: convertDateFromStringToInt(dateProvidedByUserOrTakenFromSystem));

    string incomeDescription;
    cout << endl << "Enter your income description: ";
    getline(cin, incomeDescription);
    incomeDescription = AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(incomeDescription);
    income.setIncomeDescription(incomeDescription);

    string amount;
    amount = loadIncomeAmountFromKeyboard();
    income.setAmount(amount);

    return income;

}

string IncomeManager :: loadIncomeAmountFromKeyboard() {

    string amount = "";
    vector<int> numberOfCommasOrDotsInAmount;
    cout << "Enter income amount: ";
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
            cout << "Amount provided is not correct. Provide income amount: ";
            getline(cin, amount);
            amount = AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(amount);
        }
    }
    return amount;
}


bool IncomeManager :: checkIfAmountFormatIsCorrect(string amount, vector<int> &numberOfCommasOrDotsInAmount) {

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


void IncomeManager :: printAllIncomes() {

    for(int i = 0; i < incomes.size(); i++) {
        cout << incomes[i].getIncomeId() << endl;
        cout << incomes[i].getUserId() << endl;
        cout << incomes[i].getDate() << endl;
        cout << incomes[i].getIncomeDescription() << endl;
        cout << incomes[i].getAmount() << endl;
    }
}


void IncomeManager :: printIncomesListedInProvidedDataForLoggedInUser(vector<Income> &incomesForGivenPeriod) {

    system("cls");
    string firstColumnName = "Income date";
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

    if(incomesForGivenPeriod.empty()) {
        cout << endl << separator << setw(14) << "No incomes" << string(line.size() - 14 - 2*separatorWidth,' ') << separator;
        cout << endl << line;
    }

    else {
        int numberOfIncomesRegistered = incomesForGivenPeriod.size();

        for(int i = 0; i < numberOfIncomesRegistered; i++) {
            cout << endl << separator << " " << left << setw(firstColumnNameWidth + lengthOfFixedSpaceInFirstandThirdColumns*2 - 2) << DateMethods :: convertDateFromIntToStringInCorrectFormat(incomesForGivenPeriod[i].getDate()) << " "
                 << separator << " " << left << setw(secondColumnNameWidth + lengthOfFixedSpaceInSecondColumn*2 -2) << incomesForGivenPeriod[i].getIncomeDescription() << " "
                 << separator << " " << left << setw(thirdColumnNameWidth + lengthOfFixedSpaceInFirstandThirdColumns*2 - 2) << incomesForGivenPeriod[i].getAmount() << " "
                 << separator;
        }
        cout << endl << line;
    }
}


double IncomeManager :: printIncomeBalanceForProvidedPeriod(int startDateConvertedToIntFormat, int endDateConvertedToIntFormat) {

    vector<Income> incomesForGivenPeriod = createSortedVectorOfIncomesForGivenPeriod(startDateConvertedToIntFormat, endDateConvertedToIntFormat);
    double incomeSum = 0;

    for(int i = 0; i < incomesForGivenPeriod.size(); i++) {
        incomeSum = incomeSum + atof(incomesForGivenPeriod[i].getAmount().c_str());
    }

    printIncomesListedInProvidedDataForLoggedInUser(incomesForGivenPeriod);
    return incomeSum;
}


vector<Income> IncomeManager :: createSortedVectorOfIncomesForGivenPeriod(int startDateConvertedToIntFormat, int endDateConvertedToIntFormat) {

    vector<Income> incomesForGivenPeriod = incomes;
    int lengthOfIncomesForGivenPeriodVector = incomesForGivenPeriod.size();
    int indexNumber = 0;

    if(!incomesForGivenPeriod.empty()) {
        sort(incomesForGivenPeriod.begin(), incomesForGivenPeriod.end());

        while(incomesForGivenPeriod[indexNumber].getDate() < startDateConvertedToIntFormat) {
            indexNumber++;

            if(indexNumber == lengthOfIncomesForGivenPeriodVector) {
                break;
            }
        }

        if(indexNumber == 1) {
            incomesForGivenPeriod.erase(incomesForGivenPeriod.begin());
        } else if(indexNumber > 1) {
            incomesForGivenPeriod.erase(incomesForGivenPeriod.begin(),incomesForGivenPeriod.begin() + indexNumber);
        }
        indexNumber = 0;
        lengthOfIncomesForGivenPeriodVector = incomesForGivenPeriod.size();
    }

    if(!incomesForGivenPeriod.empty()) {
        while(incomesForGivenPeriod[indexNumber].getDate() <= endDateConvertedToIntFormat) {
            indexNumber++;

            if(indexNumber == lengthOfIncomesForGivenPeriodVector) {
                break;
            }
        }

        if(lengthOfIncomesForGivenPeriodVector - indexNumber != 0) {
            while(incomesForGivenPeriod[indexNumber].getDate() > endDateConvertedToIntFormat) {
                incomesForGivenPeriod.erase(incomesForGivenPeriod.begin() + indexNumber);
                lengthOfIncomesForGivenPeriodVector = incomesForGivenPeriod.size();
                if(lengthOfIncomesForGivenPeriodVector - indexNumber == 0) {
                    break;
                }
            }
        }
    }

    return incomesForGivenPeriod;
}


double IncomeManager :: printIncomeBalanceForCurrentMonth() {

    vector<int> currentDate = DateMethods :: convertDateInStringToIntVector(DateMethods :: getCurrentTimeFromSystem());
    int numberOfDaysForCurrentMonth = DateMethods :: calculateNumberOfDaysForProvidedMonth(currentDate[1], currentDate[0]);

    string startDate = AuxiliaryMethods :: convertFromIntToString(currentDate[0]) + DateMethods :: convertMonthOrDayToProperFormat(currentDate[1]) + "01";
    string endDate = AuxiliaryMethods :: convertFromIntToString(currentDate[0]) + DateMethods :: convertMonthOrDayToProperFormat(currentDate[1]) + AuxiliaryMethods :: convertFromIntToString(numberOfDaysForCurrentMonth);

    int startDateConvertedToIntFormat = AuxiliaryMethods :: convertFromStringToInt(startDate);
    int endDateConvertedToIntFormat = AuxiliaryMethods :: convertFromStringToInt(endDate);

    vector<Income> incomesForGivenPeriod = createSortedVectorOfIncomesForGivenPeriod(startDateConvertedToIntFormat, endDateConvertedToIntFormat);

    double incomeSum = 0;

    for(int i = 0; i < incomesForGivenPeriod.size(); i++) {
        incomeSum = incomeSum + atof(incomesForGivenPeriod[i].getAmount().c_str());
    }

    printIncomesListedInProvidedDataForLoggedInUser(incomesForGivenPeriod);

    if(AuxiliaryMethods ::checkIfDoubleNumberIsInteger(incomeSum)) {
        cout << endl << "Sum of incomes is " << incomeSum << " zl" << endl << endl << endl;
    }

    else {
        cout << endl << "Sum of incomes is " << setprecision(2) << fixed << incomeSum << " zl" << endl << endl << endl;
    }
    return incomeSum;
}


double IncomeManager :: printIncomeBalanceForPreviousMonth() {

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

    vector<Income> incomesForGivenPeriod = createSortedVectorOfIncomesForGivenPeriod(startDateConvertedToIntFormat, endDateConvertedToIntFormat);

    double incomeSum = 0;

    for(int i = 0; i < incomesForGivenPeriod.size(); i++) {
        incomeSum = incomeSum + atof(incomesForGivenPeriod[i].getAmount().c_str());
    }

    printIncomesListedInProvidedDataForLoggedInUser(incomesForGivenPeriod);

    return incomeSum;
}

