#ifndef FAMILYBUDGET_H
#define FAMILYBUDGET_H

#include <iostream>


#include "UserManager.h"
#include "IncomeManager.h"
#include "ExpenseManager.h"
#include "Menu.h"

using namespace std;


class FamilyBudget {

    UserManager userManager;
    IncomeManager *incomeManager;
    ExpenseManager *expenseManager;
    Menu menu;
    const string NAME_OF_INCOME_FILE;
    const string NAME_OF_EXPENSE_FILE;

public:
    FamilyBudget(string nameOfUserFile, string nameOfIncomeFile, string nameOfExpenseFile) : userManager(nameOfUserFile), NAME_OF_INCOME_FILE(nameOfIncomeFile), NAME_OF_EXPENSE_FILE(nameOfExpenseFile)  {
        incomeManager = NULL;
        expenseManager = NULL;
    };

    ~FamilyBudget() {
        delete incomeManager;
        incomeManager = NULL;

        delete expenseManager;
        expenseManager = NULL;
    };

    bool checkIfUserIsLoggedIn();
    char selectOptionFromMainMenu();
    void registerUser();
    void logInUser();
    char selectOptionFromUserMenu();
    void addIncome();
    void addExpense();
    void printBalanceForCurrentMonth();
    void printBalanceForPreviousMonth();
    void printBalanceForProvidedPeriod();
    void changePassword();
    void logOutUser();


};


#endif
