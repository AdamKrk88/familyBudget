#ifndef FINANCIALMOVEMENT_H
#define FINANCIALMOVEMENT_H

#include <iostream>

using namespace std;


class FinancialMovement {

    int financialMovementId;
    int userId;
    int date;
    string financialMovementDescription;
    string amount;

public:
    int getFinancialMovementId();
    int getUserId();
    int getDate();
    string getFinancialMovementDescription();
    string getAmount();

    void setFinancialMovementId(int newFinancialMovementId);
    void setUserId(int newUserId);
    void setDate(int newDate);
    void setFinancialMovementDescription(string newFinancialMovementDescription);
    void setAmount(string newAmount);

    bool operator < (const FinancialMovement &financialMovement) const;
};


#endif
