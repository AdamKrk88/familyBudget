#include <iostream>
#include "UserManager.h"
#include "IncomeManager.h"
#include "ExpenseManager.h"

using namespace std;

int main()
{
 //  IncomeManager incomeManager("Incomes.xml");

    ExpenseManager expenseManager("Expenses.xml");
  //  expenseManager.addExpense();
  //  expenseManager.addExpense();
  //  expenseManager.printAllExpenses();
    expenseManager.printExpenseBalanceForProvidedPeriod();

 //   incomeManager.addIncome();
 //   incomeManager.addIncome();
 //   incomeManager.addIncome();
 //   incomeManager.addIncome();
  //  incomeManager.printAllIncomes();
 // incomeManager.printIncomesForLoggedInUserSortedByDate();
 //   incomeManager.printIncomeBalanceForProvidedPeriod();
  //  UserManager userManager("Users.xml");
    //userManager.registerUser();
   // userManager.registerUser();
   // userManager.registerUser();
 //   userManager.logInUser();
 //   userManager.printAllUsers();



    return 0;
}
