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


