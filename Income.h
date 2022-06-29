#ifndef INCOME_H
#define INCOME_H

#include <iostream>

using namespace std;

class Income {

    int incomeId;
    int userId;
    string date;
    string itemDescription;
    double amount;

public:
    int getIncomeId();
    int getUserId();
    string getDate();
    string getItemDescription();
    double getAmount();

    void setIncomeId(int newIncomeId);
    void setUserId(int newUserId);
    void setDate(string newDate);
    void setItemDescription(string newItemDescription);
    void setAmount(double newAmount);
};


#endif
