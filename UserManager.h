#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <vector>

#include "User.h"
#include "AuxiliaryMethods.h"
#include "UserFile.h"

using namespace std;


class UserManager {

vector<User> users;
UserFile userFile;

User provideDataForNewUser();
int loadIdForNewUser();
bool checkIfLoginForNewUserExistInSystem(string login);


public:
    UserManager(string nameOfUserFile) : userFile(nameOfUserFile) {
    users = userFile.loadAllUsersFromFileToVector();
    };
    void registerUser();
    void printAllUsers();

};

#endif
