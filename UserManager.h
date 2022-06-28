#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <vector>

#include "User.h"
#include "AuxiliaryMethods.h"

using namespace std;


class UserManager {

vector<User> users;

User provideDataForNewUser();
int loadIdForNewUser();
bool checkIfLoginForNewUserExistInSystem(string login);


public:
    void registerUser();
    void printAllUsers();

};

#endif
