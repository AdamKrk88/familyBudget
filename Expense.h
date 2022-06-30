#ifndef EXPENSE_H
#define EXPENSE_H

#include <iostream>

using namespace std;


class Expense {

  int expenseId;
    int userId;
    string date;
    string expenseDescription;
    string amount;

public:
    int getExpenseId();
    int getUserId();
    string getDate();
    string getExpenseDescription();
    string getAmount();

    void setExpenseId(int newExpenseId);
    void setUserId(int newUserId);
    void setDate(string newDate);
    void setExpenseDescription(string newExpenseDescription);
    void setAmount(string newAmount);

};


#endif
