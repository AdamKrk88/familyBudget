#include "IncomeManager.h"

void IncomeManager :: addIncome() {

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
    income.setUserId(2);
    income.setDate(DateMethods :: convertDateFromStringToInt(dateProvidedByUserOrTakenFromSystem));

    string incomeDescription;
    cout << "Enter your income description: ";
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


void IncomeManager :: printIncomesForLoggedInUserSortedByDate() {

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

    if(incomes.empty()) {
        cout << endl << separator << setw(14) << "No incomes" << string(line.size() - 14 - 2*separatorWidth,' ') << separator;
        cout << endl << line;
    }

    else {
        sort(incomes.begin(),incomes.end());
        int numberOfIncomesRegistered = incomes.size();

        for(int i = 0; i < numberOfIncomesRegistered; i++) {
            cout << endl << separator << " " << left << setw(firstColumnNameWidth + lengthOfFixedSpaceInFirstandThirdColumns*2 - 2) << DateMethods :: convertDateFromIntToStringInCorrectFormat(incomes[i].getDate()) << " "
                 << separator << " " << left << setw(secondColumnNameWidth + lengthOfFixedSpaceInSecondColumn*2 -2) << incomes[i].getIncomeDescription() << " "
                 << separator << " " << left << setw(thirdColumnNameWidth + lengthOfFixedSpaceInFirstandThirdColumns*2 - 2) << incomes[i].getAmount() << " "
                 << separator;
        }
        cout << endl << line;
    }
}

/*
void IncomeManager :: extractIncomesAsOfProvidedPeriod() {

     cout << "Provide period to display incomes and expenses balance" << endl;
     cout << "Provide start date: ";
     string startDate = DateMethods :: loadDateFromKeyboard();

}
*/
