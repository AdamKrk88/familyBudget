#include "FamilyBudget.h"


bool FamilyBudget :: checkIfUserIsLoggedIn() {
    return userManager.checkIfUserIsLoggedIn();
}


char FamilyBudget :: selectOptionFromMainMenu() {
    return menu.selectOptionFromMainMenu();
}


void FamilyBudget :: registerUser() {
    userManager.registerUser();
}

void FamilyBudget :: logInUser() {
    userManager.logInUser();
    if (userManager.checkIfUserIsLoggedIn()) {
        incomeManager = new IncomeManager(NAME_OF_INCOME_FILE, userManager.getLoggedUserId());
        expenseManager = new ExpenseManager(NAME_OF_EXPENSE_FILE, userManager.getLoggedUserId());
    }

}
char FamilyBudget :: selectOptionFromUserMenu() {
    return menu.selectOptionFromUserMenu();
}


void FamilyBudget :: addIncome() {

    if(userManager.checkIfUserIsLoggedIn()) {
        incomeManager -> addIncome();
    }

    else {
        cout << "User is not logged in!" << endl;
    }
}


void FamilyBudget :: addExpense() {

    if(userManager.checkIfUserIsLoggedIn()) {
        expenseManager -> addExpense();
    }

    else {
        cout << "User is not logged in!" << endl;
    }
}


void FamilyBudget :: printBalanceForCurrentMonth() {

    double sumOfIncomes = incomeManager -> printIncomeBalanceForCurrentMonth();
    double sumOfExpenses = expenseManager -> printExpenseBalanceForCurrentMonth();

    double finalBalance = sumOfIncomes - sumOfExpenses;

    if(AuxiliaryMethods :: checkIfDoubleNumberIsInteger(finalBalance)) {
        cout << "Balance is: " << setprecision(0) << fixed << finalBalance << " zl" << endl;
    }

    else {
        cout << "Balance is: " <<  setprecision(2) << fixed << finalBalance << " zl" << endl;
    }

    cout << "(+ means gain, - means loss)" << endl << endl;
    cout << "Click enter to continue";
    getchar();
}


void FamilyBudget :: printBalanceForPreviousMonth() {

    double intpart;
    double fractionalPartOfDoubleNumber = 0;
    double sumOfIncomes = incomeManager -> printIncomeBalanceForPreviousMonth();
    fractionalPartOfDoubleNumber = modf(sumOfIncomes, &intpart);

    if(fractionalPartOfDoubleNumber == 0) {
        cout << endl << "Sum of incomes is " << sumOfIncomes << " zl" << endl << endl << endl;
    }

    else {
        cout << endl << "Sum of incomes is " << setprecision(2) << fixed << sumOfIncomes << " zl" << endl << endl << endl;
    }

    double sumOfExpenses = expenseManager -> printExpenseBalanceForPreviousMonth();
    fractionalPartOfDoubleNumber = modf(sumOfExpenses, &intpart);

    if(fractionalPartOfDoubleNumber == 0) {
        cout << endl << "Sum of expenses is " << setprecision(0) << fixed << sumOfExpenses << " zl" << endl << endl;
    }

    else {

        cout << endl << "Sum of expenses is " << setprecision(2) << fixed << sumOfExpenses << " zl" << endl << endl;
    }

    double finalBalance = sumOfIncomes - sumOfExpenses;
    fractionalPartOfDoubleNumber = modf(finalBalance, &intpart);

    if(fractionalPartOfDoubleNumber == 0) {
        cout << "Balance is: " << setprecision(0) << fixed << finalBalance << " zl" << endl;
    }

    else {
        cout << "Balance is: " <<  setprecision(2) << fixed << finalBalance << " zl" << endl;
    }

    cout << "(+ means gain, - means loss)" << endl << endl;
    cout << "Click enter to continue";
    getchar();
}


void FamilyBudget :: printBalanceForProvidedPeriod() {

    system("cls");
    double sumOfIncomes = 0;
    double sumOfExpenses = 0;
    double intpart;
    double fractionalPartOfDoubleNumber = 0;
    vector<int> startEndDateProvidedFromKeyboard(2,0);
    cout << "Provide start and end date to display list of incomes and expenses" << endl << endl;
    startEndDateProvidedFromKeyboard = DateMethods :: enterStartEndDate();

    if(startEndDateProvidedFromKeyboard[0] != 0 && startEndDateProvidedFromKeyboard[1] != 0) {
        sumOfIncomes = incomeManager -> printIncomeBalanceForProvidedPeriod(startEndDateProvidedFromKeyboard[0], startEndDateProvidedFromKeyboard[1]);
        fractionalPartOfDoubleNumber = modf(sumOfIncomes, &intpart);

        if(fractionalPartOfDoubleNumber == 0) {
            cout << endl << "Sum of incomes is " << sumOfIncomes << " zl" << endl << endl << endl;
        }

        else {
            cout << endl << "Sum of incomes is " << setprecision(2) << fixed << sumOfIncomes << " zl" << endl << endl << endl;
        }

        sumOfExpenses = expenseManager -> printExpenseBalanceForProvidedPeriod(startEndDateProvidedFromKeyboard[0], startEndDateProvidedFromKeyboard[1]);
        fractionalPartOfDoubleNumber = modf(sumOfExpenses, &intpart);

        if(fractionalPartOfDoubleNumber == 0) {
            cout << endl << "Sum of expenses is " << setprecision(0) << fixed << sumOfExpenses << " zl" << endl << endl;
        }

        else {
            cout << endl << "Sum of expenses is " << setprecision(2) << fixed << sumOfExpenses << " zl" << endl << endl;
        }

        double finalBalance = sumOfIncomes - sumOfExpenses;
        fractionalPartOfDoubleNumber = modf(finalBalance, &intpart);

        if(fractionalPartOfDoubleNumber == 0) {
            cout << "Balance is: " << setprecision(0) << fixed << finalBalance << " zl" << endl;
        }

        else {
            cout << "Balance is: " <<  setprecision(2) << fixed << finalBalance << " zl" << endl;
        }

        cout << "(+ means gain, - means loss)" << endl << endl;
        cout << "Click enter to continue";
        getchar();
    }
}


void FamilyBudget :: changePassword() {
    userManager.changePassword();
}


void FamilyBudget :: logOutUser() {
    userManager.logOutUser();
    delete incomeManager;
    incomeManager = NULL;
    delete expenseManager;
    expenseManager = NULL;
}
