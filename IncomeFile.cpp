#include "IncomeFile.h"


void IncomeFile :: addIncomeToFile(Income income) {
    CMarkup xml;
    bool fileExistCorrectlyFormatted = xml.Load(NAME_OF_INCOME_FILE);

    if(!fileExistCorrectlyFormatted) {
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Incomes");
    }

    xml.FindElem();
    xml.IntoElem();
    xml.AddElem("Income");
    xml.IntoElem();
    xml.AddElem("IncomeId",AuxiliaryMethods :: convertFromIntToString(income.getIncomeId()));
    xml.AddElem("UserId",AuxiliaryMethods :: convertFromIntToString(income.getUserId()));
    xml.AddElem("Date",income.getDate());
    xml.AddElem("Item",income.getIncomeDescription());
    xml.AddElem("Amount",income.getAmount());

    xml.Save(NAME_OF_INCOME_FILE);
    lastIncomeId++;
}


vector<Income> IncomeFile :: loadAllIncomesForLoggedUser(int loggedUserId) {

    CMarkup xml;
    Income income;
    vector<Income> incomes;
    int numberOfItemFromFile = 0;
    bool fileExistCorrectlyFormatted = xml.Load(NAME_OF_INCOME_FILE);

    if(fileExistCorrectlyFormatted) {
        xml.FindElem();
        xml.IntoElem();

        while(xml.FindElem()) {
            xml.IntoElem();
            xml.FindElem();
            lastIncomeId = atoi(xml.GetData().c_str());
            xml.FindElem();

            if(loggedUserId == atoi(xml.GetData().c_str())) {
                xml.ResetMainPos();

                while(xml.FindElem()) {

                    switch(numberOfItemFromFile) {
                    case 0:
                        income.setIncomeId(atoi(xml.GetData().c_str()));
                        numberOfItemFromFile++;
                        break;

                    case 1:
                        income.setUserId(loggedUserId);
                        numberOfItemFromFile++;
                        break;

                    case 2:
                        income.setDate(xml.GetData());
                        numberOfItemFromFile++;
                        break;

                    case 3:
                        income.setIncomeDescription(xml.GetData());
                        numberOfItemFromFile++;
                        break;

                    case 4:
                        income.setAmount(xml.GetData());
                        numberOfItemFromFile++;
                        break;
                    }
                }

                incomes.push_back(income);
                numberOfItemFromFile = 0;
                xml.OutOfElem();
            }

            else {
                xml.OutOfElem();
            }
        }
        xml.OutOfElem();
    }
    return incomes;
}


int IncomeFile :: getLastIncomeId() {
    return lastIncomeId;
}
