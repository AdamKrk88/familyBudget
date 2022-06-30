#ifndef INCOME_H
#define INCOME_H

#include <iostream>

using namespace std;

class Income {

    int incomeId;
    int userId;
    string date;
    string incomeDescription;
    string amount;

public:
    int getIncomeId();
    int getUserId();
    string getDate();
    string getIncomeDescription();
    string getAmount();

    void setIncomeId(int newIncomeId);
    void setUserId(int newUserId);
    void setDate(string newDate);
    void setIncomeDescription(string newIncomeDescription);
    void setAmount(string newAmount);
};


#endif
