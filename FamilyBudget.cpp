#include "FamilyBudget.h"


bool FamilyBudget :: checkIfUserIsLoggedIn() {
    return userManager.checkIfUserIsLoggedIn();
}


char FamilyBudget :: selectOptionFromMainMenu() {
    return menu.selectOptionFromMainMenu();
}


void FamilyBudget :: registerUser() {}
void FamilyBudget :: logInUser() {}
char FamilyBudget :: selectOptionFromUserMenu() {}
void FamilyBudget :: addIncome() {}
void FamilyBudget :: addExpense() {}
void FamilyBudget :: printBalanceForCurrentMonth() {}
void FamilyBudget :: printBalanceForPreviousMonth() {}
void FamilyBudget :: printBalanceForProvidedPeriod() {}
void FamilyBudget :: changePassword() {}
void FamilyBudget :: logOutUser() {}
