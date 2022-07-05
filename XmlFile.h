#ifndef XMLFILE_H
#define XMLFILE_H

#include <iostream>
#include <vector>

#include "FinancialMovement.h"

using namespace std;


class XmlFile {

public:

    virtual void addFinancialMovementToFile(FinancialMovement financialMovement) = 0;
    virtual vector<FinancialMovement> loadAllFinancialMovementsForLoggedUser(int loggedUserId) = 0;
    virtual int getLastItemId() = 0;
};


#endif
