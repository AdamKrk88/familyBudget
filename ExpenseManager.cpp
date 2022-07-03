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
    expense.setUserId(LOGGED_USER_ID);
    expense.setDate(DateMethods :: convertDateFromStringToInt(dateProvidedByUserOrTakenFromSystem));

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


void ExpenseManager :: printExpensesListedInProvidedDataForLoggedInUser(vector<Expense> &expensesForGivenPeriod) {

    string firstColumnName = "Expense date";
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

    if(expensesForGivenPeriod.empty()) {
        cout << endl << separator << setw(14) << "No expenses" << string(line.size() - 14 - 2*separatorWidth,' ') << separator;
        cout << endl << line;
    }

    else {
        int numberOfExpensesRegistered = expensesForGivenPeriod.size();

        for(int i = 0; i < numberOfExpensesRegistered; i++) {
            cout << endl << separator << " " << left << setw(firstColumnNameWidth + lengthOfFixedSpaceInFirstandThirdColumns*2 - 2) << DateMethods :: convertDateFromIntToStringInCorrectFormat(expensesForGivenPeriod[i].getDate()) << " "
                 << separator << " " << left << setw(secondColumnNameWidth + lengthOfFixedSpaceInSecondColumn*2 -2) << expensesForGivenPeriod[i].getExpenseDescription() << " "
                 << separator << " " << left << setw(thirdColumnNameWidth + lengthOfFixedSpaceInFirstandThirdColumns*2 - 2) << expensesForGivenPeriod[i].getAmount() << " "
                 << separator;
        }
        cout << endl << line;
    }
}


double ExpenseManager :: printExpenseBalanceForProvidedPeriod() {

    string startDate;
    string endDate;
    int startDateConvertedToIntFormat = 0;
    int endDateConvertedToIntFormat = 0;

    cout << "Provide period to display expenses balance" << endl;

    while(true) {
        cout << "Provide start date: ";
        startDate = DateMethods :: loadDateFromKeyboard();

        if(startDate != "") {
            cout << "Provide end date: ";
            endDate = DateMethods :: loadDateFromKeyboard();

            if(endDate != "") {
                startDateConvertedToIntFormat = DateMethods :: convertDateFromStringToInt(startDate);
                endDateConvertedToIntFormat = DateMethods :: convertDateFromStringToInt(endDate);

                if(startDateConvertedToIntFormat <= endDateConvertedToIntFormat) {
                    vector<Expense> expensesForGivenPeriod = createSortedVectorOfExpensesForGivenPeriod(startDateConvertedToIntFormat, endDateConvertedToIntFormat);

                    double expenseSum = 0;

                    for(int i = 0; i < expensesForGivenPeriod.size(); i++) {
                        expenseSum = expenseSum + atof(expensesForGivenPeriod[i].getAmount().c_str());
                    }

                    printExpensesListedInProvidedDataForLoggedInUser(expensesForGivenPeriod);
                    return expenseSum;
                }

                else {
                    cout << "Start date cannot be later than end date. Try once again" << endl;
                }
            }
        }
    }
    return 0;
}


vector<Expense> ExpenseManager :: createSortedVectorOfExpensesForGivenPeriod(int startDateConvertedToIntFormat, int endDateConvertedToIntFormat) {

    vector<Expense> expensesForGivenPeriod = expenses;
    int lengthOfExpensesForGivenPeriodVector = expensesForGivenPeriod.size();
    int indexNumber = 0;

    if(!expensesForGivenPeriod.empty()) {
        sort(expensesForGivenPeriod.begin(), expensesForGivenPeriod.end());

        while(expensesForGivenPeriod[indexNumber].getDate() < startDateConvertedToIntFormat) {
            indexNumber++;

            if(indexNumber == lengthOfExpensesForGivenPeriodVector) {
                break;
            }
        }

        if(indexNumber == 1) {
            expensesForGivenPeriod.erase(expensesForGivenPeriod.begin());
        } else if(indexNumber > 1) {
            expensesForGivenPeriod.erase(expensesForGivenPeriod.begin(),expensesForGivenPeriod.begin() + indexNumber);
        }
        indexNumber = 0;
        lengthOfExpensesForGivenPeriodVector = expensesForGivenPeriod.size();
    }

    if(!expensesForGivenPeriod.empty()) {
        while(expensesForGivenPeriod[indexNumber].getDate() <= endDateConvertedToIntFormat) {
            indexNumber++;

            if(indexNumber == lengthOfExpensesForGivenPeriodVector) {
                break;
            }
        }

        if(lengthOfExpensesForGivenPeriodVector - indexNumber != 0) {
            while(expensesForGivenPeriod[indexNumber].getDate() > endDateConvertedToIntFormat) {
                expensesForGivenPeriod.erase(expensesForGivenPeriod.begin() + indexNumber);
                lengthOfExpensesForGivenPeriodVector = expensesForGivenPeriod.size();
                if(lengthOfExpensesForGivenPeriodVector - indexNumber == 0) {
                    break;
                }
            }
        }
    }

    return expensesForGivenPeriod;
}


double ExpenseManager :: printExpenseBalanceForCurrentMonth() {

    vector<int> currentDate = DateMethods :: convertDateInStringToIntVector(DateMethods :: getCurrentTimeFromSystem());
    int numberOfDaysForCurrentMonth = DateMethods :: calculateNumberOfDaysForProvidedMonth(currentDate[1], currentDate[0]);

    string startDate = AuxiliaryMethods :: convertFromIntToString(currentDate[0]) + DateMethods :: convertMonthOrDayToProperFormat(currentDate[1]) + "01";
    string endDate = AuxiliaryMethods :: convertFromIntToString(currentDate[0]) + DateMethods :: convertMonthOrDayToProperFormat(currentDate[1]) + AuxiliaryMethods :: convertFromIntToString(numberOfDaysForCurrentMonth);

    int startDateConvertedToIntFormat = AuxiliaryMethods :: convertFromStringToInt(startDate);
    int endDateConvertedToIntFormat = AuxiliaryMethods :: convertFromStringToInt(endDate);

    vector<Expense> expensesForGivenPeriod = createSortedVectorOfExpensesForGivenPeriod(startDateConvertedToIntFormat, endDateConvertedToIntFormat);

    double expenseSum = 0;

    for(int i = 0; i < expensesForGivenPeriod.size(); i++) {
        expenseSum = expenseSum + atof(expensesForGivenPeriod[i].getAmount().c_str());
    }

    printExpensesListedInProvidedDataForLoggedInUser(expensesForGivenPeriod);
    return expenseSum;
}


double ExpenseManager :: printExpenseBalanceForPreviousMonth() {

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

    vector<Expense> expensesForGivenPeriod = createSortedVectorOfExpensesForGivenPeriod(startDateConvertedToIntFormat, endDateConvertedToIntFormat);

    double expenseSum = 0;

    for(int i = 0; i < expensesForGivenPeriod.size(); i++) {
        expenseSum = expenseSum + atof(expensesForGivenPeriod[i].getAmount().c_str());
    }

    printExpensesListedInProvidedDataForLoggedInUser(expensesForGivenPeriod);
    return expenseSum;
}






