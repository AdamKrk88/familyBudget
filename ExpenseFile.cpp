#include "ExpenseFile.h"


void ExpenseFile :: addFinancialMovementToFile(FinancialMovement financialMovement) {

    CMarkup xml;
    bool fileExistCorrectlyFormatted = xml.Load(NAME_OF_EXPENSE_FILE);

    if(!fileExistCorrectlyFormatted) {
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Expenses");
    }

    xml.FindElem();
    xml.IntoElem();
    xml.AddElem("Expense");
    xml.IntoElem();
    xml.AddElem("ExpenseId",AuxiliaryMethods :: convertFromIntToString(financialMovement.getFinancialMovementId()));
    xml.AddElem("UserId",AuxiliaryMethods :: convertFromIntToString(financialMovement.getUserId()));
    xml.AddElem("Date",DateMethods :: convertDateFromIntToStringInCorrectFormat(financialMovement.getDate()));
    xml.AddElem("Item",financialMovement.getFinancialMovementDescription());
    xml.AddElem("Amount",financialMovement.getAmount());

    xml.Save(NAME_OF_EXPENSE_FILE);
    lastExpenseId++;
}


vector<FinancialMovement> ExpenseFile :: loadAllFinancialMovementsForLoggedUser(int loggedUserId) {

    CMarkup xml;
    FinancialMovement financialMovement;
    vector<FinancialMovement> financialMovements;
    int numberOfItemFromFile = 0;
    bool fileExistCorrectlyFormatted = xml.Load(NAME_OF_EXPENSE_FILE);

    if(fileExistCorrectlyFormatted) {
        xml.FindElem();
        xml.IntoElem();

        while(xml.FindElem()) {
            xml.IntoElem();
            xml.FindElem();
            lastExpenseId = atoi(xml.GetData().c_str());
            xml.FindElem();

            if(loggedUserId == atoi(xml.GetData().c_str())) {
                xml.ResetMainPos();

                while(xml.FindElem()) {
                    switch(numberOfItemFromFile) {

                    case 0:
                        financialMovement.setFinancialMovementId(atoi(xml.GetData().c_str()));
                        numberOfItemFromFile++;
                        break;

                    case 1:
                        financialMovement.setUserId(loggedUserId);
                        numberOfItemFromFile++;
                        break;

                    case 2:
                        financialMovement.setDate(DateMethods :: convertDateFromStringToInt(xml.GetData()));
                        numberOfItemFromFile++;
                        break;

                    case 3:
                        financialMovement.setFinancialMovementDescription(xml.GetData());
                        numberOfItemFromFile++;
                        break;

                    case 4:
                        financialMovement.setAmount(xml.GetData());
                        numberOfItemFromFile++;
                        break;
                    }
                }

                financialMovements.push_back(financialMovement);
                numberOfItemFromFile = 0;
                xml.OutOfElem();
            }

            else {
                xml.OutOfElem();
            }
        }
        xml.OutOfElem();
    }
    return financialMovements;
}


int ExpenseFile :: getLastItemId() {
    return lastExpenseId;
}
