#include "ExpenseManager.h"

void ExpenseManager :: addExpense() {

    Expense expense;
    string dateAsOfTodayOrPast = "";
    string dateProvidedByUserOrTakenFromSystem = "";
    cout << "Provide date for your expense - enter \"today\" or \"past\": ";
    cin >> dateAsOfTodayOrPast;
    cin.sync();

    if (dateAsOfTodayOrPast == "today") {
        dateProvidedByUserOrTakenFromSystem = DateMethods :: getCurrentTimeFromSystem();
        expense = provideDataForExpense(dateProvidedByUserOrTakenFromSystem);
        expenses.push_back(expense);
        expenseFile.addExpenseToFile(expense);
    } else if(dateAsOfTodayOrPast == "past") {
        dateProvidedByUserOrTakenFromSystem = DateMethods :: loadDateFromKeyboard();
        if(dateProvidedByUserOrTakenFromSystem != "") {
            expense = provideDataForExpense(dateProvidedByUserOrTakenFromSystem);
            expenses.push_back(expense);
            expenseFile.addExpenseToFile(expense);
        }
    } else {
        cout << "Not correct. Return to User menu" << endl;
    }

}


Expense ExpenseManager :: provideDataForExpense(string dateProvidedByUserOrTakenFromSystem) {

    Expense expense;

    expense.setExpenseId(expenseFile.getLastExpenseId() + 1);
    expense.setUserId(2);
    expense.setDate(dateProvidedByUserOrTakenFromSystem);

    string expenseDescription;
    cout << "Enter your expense description: ";
    getline(cin, expenseDescription);
    expenseDescription = AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(expenseDescription);
    expense.setExpenseDescription(expenseDescription);

    string amount;
    amount = loadExpenseAmountFromKeyboard();
    expense.setAmount(amount);

    return expense;

}

string ExpenseManager :: loadExpenseAmountFromKeyboard() {

    string amount = "";
    vector<int> numberOfCommasOrDotsInAmount;
    cout << "Enter expense amount: ";
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
            cout << "Amount provided is not correct. Provide expense amount: ";
            getline(cin, amount);
            amount = AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(amount);
        }
    }
    return amount;
}


bool ExpenseManager :: checkIfAmountFormatIsCorrect(string amount, vector<int> &numberOfCommasOrDotsInAmount) {

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


void ExpenseManager :: printAllExpenses() {

for(int i = 0; i < expenses.size(); i++) {
    cout << expenses[i].getExpenseId() << endl;
    cout << expenses[i].getUserId() << endl;
    cout << expenses[i].getDate() << endl;
    cout << expenses[i].getExpenseDescription() << endl;
    cout << expenses[i].getAmount() << endl;
}
}


