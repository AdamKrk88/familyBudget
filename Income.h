#ifndef INCOME_H
#define INCOME_H

#include <iostream>

using namespace std;

class Income {

    int incomeId;
    int userId;
    int date;
    string incomeDescription;
    string amount;

public:
    int getIncomeId();
    int getUserId();
    int getDate();
    string getIncomeDescription();
    string getAmount();

    void setIncomeId(int newIncomeId);
    void setUserId(int newUserId);
    void setDate(int newDate);
    void setIncomeDescription(string newIncomeDescription);
    void setAmount(string newAmount);

    bool operator < (const Income &income) const;
};


#endif
