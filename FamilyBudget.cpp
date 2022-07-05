#include "FamilyBudget.h"


bool FamilyBudget :: checkIfUserIsLoggedIn() {
    return userManager.checkIfUserIsLoggedIn();
}


char FamilyBudget :: selectOptionFromMainMenu() {
    return menu.selectOptionFromMainMenu();
}


void FamilyBudget :: registerUser() {

    AuxiliaryMethods :: initialMessageOnScreen(" >>> USER REGISTRATION <<<");
    userManager.registerUser();
}

void FamilyBudget :: logInUser() {

     AuxiliaryMethods :: initialMessageOnScreen(" >>> USER LOG IN <<<");
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

    AuxiliaryMethods :: initialMessageOnScreen(" >>> ADD INCOME <<<");
    if(userManager.checkIfUserIsLoggedIn()) {
        incomeManager -> addFinancialMovement();
    }

    else {
        cout << "User is not logged in!" << endl;
    }
}


void FamilyBudget :: addExpense() {

    AuxiliaryMethods :: initialMessageOnScreen(" >>> ADD EXPENSE <<<");
    if(userManager.checkIfUserIsLoggedIn()) {
        expenseManager -> addFinancialMovement();
    }

    else {
        cout << "User is not logged in!" << endl;
    }
}


void FamilyBudget :: printBalanceForCurrentMonth() {

    AuxiliaryMethods :: initialMessageOnScreen(" >>> PRINT BALANCE FOR CURRENT MONTH <<<");
    double sumOfIncomes = incomeManager -> printFinancialMovementBalanceForCurrentMonth();
    double sumOfExpenses = expenseManager -> printFinancialMovementBalanceForCurrentMonth();
    printFinalBalanceOnScreen(sumOfIncomes, sumOfExpenses);
}


void FamilyBudget :: printBalanceForPreviousMonth() {

    AuxiliaryMethods :: initialMessageOnScreen(" >>> PRINT BALANCE FOR PREVIOUS MONTH <<<");
    double sumOfIncomes = incomeManager -> printFinancialMovementBalanceForPreviousMonth();
    double sumOfExpenses = expenseManager -> printFinancialMovementBalanceForPreviousMonth();
    printFinalBalanceOnScreen(sumOfIncomes, sumOfExpenses);
}


void FamilyBudget :: printBalanceForProvidedPeriod() {

    AuxiliaryMethods :: initialMessageOnScreen(" >>> PRINT BALANCE FOR PROVIDED PERIOD <<<");
    vector<int> startEndDateProvidedFromKeyboard(2,0);
    cout << "Provide start and end date to display list of incomes and expenses" << endl << endl;
    startEndDateProvidedFromKeyboard = DateMethods :: enterStartEndDate();

    if(startEndDateProvidedFromKeyboard[0] != 0 && startEndDateProvidedFromKeyboard[1] != 0) {
        AuxiliaryMethods :: initialMessageOnScreen(" >>> PRINT BALANCE FOR PROVIDED PERIOD <<<");
        cout << "PERIOD FROM " <<DateMethods :: convertDateFromIntToStringInCorrectFormat(startEndDateProvidedFromKeyboard[0]) << " TO " << DateMethods :: convertDateFromIntToStringInCorrectFormat(startEndDateProvidedFromKeyboard[1]) << endl << endl;
        double sumOfIncomes = incomeManager -> printFinancialMovementBalanceForProvidedPeriod(startEndDateProvidedFromKeyboard[0], startEndDateProvidedFromKeyboard[1]);
        double sumOfExpenses = expenseManager -> printFinancialMovementBalanceForProvidedPeriod(startEndDateProvidedFromKeyboard[0], startEndDateProvidedFromKeyboard[1]);
        printFinalBalanceOnScreen(sumOfIncomes, sumOfExpenses);
    }
}

void FamilyBudget :: changePassword() {
    AuxiliaryMethods :: initialMessageOnScreen(" >>> CHANGE PASSWORD <<<");
    userManager.changePassword();
}


void FamilyBudget :: logOutUser() {
    userManager.logOutUser();
    delete incomeManager;
    incomeManager = NULL;
    delete expenseManager;
    expenseManager = NULL;
}

void FamilyBudget :: printFinalBalanceOnScreen(double sumOfIncomes, double sumOfExpenses) {

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
    cin.sync();
}
