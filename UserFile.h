#ifndef USERFILE_H
#define USERFILE_H

#include <iostream>

#include "Markup.h"
#include "User.h"
#include "AuxiliaryMethods.h"

using namespace std;


class UserFile {

    const string NAME_OF_USER_FILE;

public:
    UserFile(string nameOfUserFile) : NAME_OF_USER_FILE(nameOfUserFile) {};
    void addUserToFile(User user);


};





#endif
