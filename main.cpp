#include <iostream>
#include "UserManager.h"

using namespace std;

int main()
{

    UserManager userManager("Users.xml");
    //userManager.registerUser();
   // userManager.registerUser();
   // userManager.registerUser();

    userManager.printAllUsers();



    return 0;
}
