#include <iostream>
#include "UserManager.h"
#include "IncomeManager.h"

using namespace std;

int main()
{
    IncomeManager incomeManager;
    incomeManager.addIncome();
    incomeManager.addIncome();
    incomeManager.addIncome();
    incomeManager.printAllIncomes();

  //  UserManager userManager("Users.xml");
    //userManager.registerUser();
   // userManager.registerUser();
   // userManager.registerUser();
 //   userManager.logInUser();
 //   userManager.printAllUsers();



    return 0;
}
