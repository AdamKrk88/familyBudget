#include "ExpenseFile.h"


void ExpenseFile :: addExpenseToFile(Expense expense) {
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
    xml.AddElem("ExpenseId",AuxiliaryMethods :: convertFromIntToString(expense.getExpenseId()));
    xml.AddElem("UserId",AuxiliaryMethods :: convertFromIntToString(expense.getUserId()));
    xml.AddElem("Date",DateMethods :: convertDateFromIntToStringInCorrectFormat(expense.getDate()));
    xml.AddElem("Item",expense.getExpenseDescription());
    xml.AddElem("Amount",expense.getAmount());

    xml.Save(NAME_OF_EXPENSE_FILE);
    lastExpenseId++;
}


vector<Expense> ExpenseFile :: loadAllExpensesForLoggedUser(int loggedUserId) {

    CMarkup xml;
    Expense expense;
    vector<Expense> expenses;
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
                        expense.setExpenseId(atoi(xml.GetData().c_str()));
                        numberOfItemFromFile++;
                        break;

                    case 1:
                        expense.setUserId(loggedUserId);
                        numberOfItemFromFile++;
                        break;

                    case 2:
                        expense.setDate(DateMethods :: convertDateFromStringToInt(xml.GetData()));
                        numberOfItemFromFile++;
                        break;

                    case 3:
                        expense.setExpenseDescription(xml.GetData());
                        numberOfItemFromFile++;
                        break;

                    case 4:
                        expense.setAmount(xml.GetData());
                        numberOfItemFromFile++;
                        break;
                    }
                }

                expenses.push_back(expense);
                numberOfItemFromFile = 0;
                xml.OutOfElem();
            }

            else {
                xml.OutOfElem();
            }
        }
        xml.OutOfElem();
    }
    return expenses;
}


int ExpenseFile :: getLastExpenseId() {
    return lastExpenseId;
}
