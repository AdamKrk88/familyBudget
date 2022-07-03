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
char FamilyBudget :: selectOptionFromUserMenu() {}
void FamilyBudget :: addIncome() {}
void FamilyBudget :: addExpense() {}
void FamilyBudget :: printBalanceForCurrentMonth() {}
void FamilyBudget :: printBalanceForPreviousMonth() {}
void FamilyBudget :: printBalanceForProvidedPeriod() {}
void FamilyBudget :: changePassword() {}
void FamilyBudget :: logOutUser() {}
