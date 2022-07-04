#ifndef BALANCEMANAGER_H
#define BALANCEMANAGER_H

#include <iostream>

using namespace std;


class BalanceManager {

    const int LOGGED_USER_ID;


public:
    BalanceManager(int loggedUserId) : LOGGED_USER_ID(loggedUserId) {};

    int getLoggedUserId();



};



#endif
