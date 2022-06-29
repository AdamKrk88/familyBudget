#include "DateMethods.h"


string DateMethods :: getCurrentTimeFromSystem() {

    string currentDate="";
    int year, month, day;
    time_t t = time(0);
    tm* now = localtime(&t);
    year = now->tm_year + 1900;
    month = now->tm_mon + 1;
    day = now->tm_mday;

    currentDate = AuxiliaryMethods :: convertFromIntToString(year) + "-" + convertMonthOrDayToProperFormat(month) + "-" + convertMonthOrDayToProperFormat(day);

    return currentDate;
}


string DateMethods :: convertMonthOrDayToProperFormat(int monthOrDay) {

    string monthAsString = AuxiliaryMethods :: convertFromIntToString(monthOrDay);
    if (monthAsString.size() == 1)
        monthAsString = "0" + monthAsString;

    return monthAsString;

}


vector<int> DateMethods :: convertDateInStringToIntVector(string dateFormat) {

    vector<int> dateIntFormat(3);
    string year = dateFormat.substr(0,4);
    string month = dateFormat.substr(5,2);
    string day = dateFormat.substr(8,2);

    dateIntFormat[0] = AuxiliaryMethods :: convertFromStringToInt(year);
    dateIntFormat[1] = AuxiliaryMethods :: convertFromStringToInt(month);
    dateIntFormat[2] = AuxiliaryMethods :: convertFromStringToInt(day);

    return dateIntFormat;
}


bool DateMethods :: checkIfYearIsLeap (int year) {
     if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return true;
     else
        return false;
}


bool DateMethods :: checkIfFormatOfDateIsCorrect(string providedDate) {

    if(providedDate.size() != 10)
        return false;

    if(providedDate[4] != '-' || providedDate[7] != '-')
        return false;

    if(!AuxiliaryMethods :: checkIfProvidedStringContainsOnlyDigits(providedDate.substr(0,4)))
        return false;

    if(!AuxiliaryMethods :: checkIfProvidedStringContainsOnlyDigits(providedDate.substr(5,2)))
        return false;

    if(!AuxiliaryMethods :: checkIfProvidedStringContainsOnlyDigits(providedDate.substr(8,2)))
        return false;

    return true;

}


bool DateMethods :: checkIfDateIsValid(string dateToCheckInOneString) {

    int day = 0, month = 0, year = 0;
    vector<int> dateToCheck = convertDateInStringToIntVector(dateToCheckInOneString);
    day = dateToCheck[2];
    month = dateToCheck[1];
    year = dateToCheck[0];

    string currentDateInOneString = getCurrentTimeFromSystem();
    vector<int> currentDate = convertDateInStringToIntVector(currentDateInOneString);
    const int MAX_VALID_YR = currentDate[0];
    const int MIN_VALID_YR = 2000;

    if (year > MAX_VALID_YR || year < MIN_VALID_YR)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;


    if (month == 2) {
        if (checkIfYearIsLeap(year))
            return (day <= 29);
        else
            return (day <= 28);
    }

    if (month == 4 || month == 6 || month == 9 || month == 11)
        return (day <= 30);

    return true;
}


string DateMethods :: loadDateFromKeyboard() {

    string providedDateOrReturnStatement = "";

    cout << "Enter date in format YYYY-MM-DD: ";
    getline(cin, providedDateOrReturnStatement);
    providedDateOrReturnStatement = AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(providedDateOrReturnStatement);

    while(true) {
        if(checkIfFormatOfDateIsCorrect(providedDateOrReturnStatement)) {
            cout << "Format of date correct" << endl;

            if(checkIfDateIsValid(providedDateOrReturnStatement)) {
                cout << "Date is valid" << endl;
                break;
            } else {
                cout << "Date is not valid. Provide date or enter \"return\" to go back to User Menu: ";
                getline(cin, providedDateOrReturnStatement);
                providedDateOrReturnStatement = AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(providedDateOrReturnStatement);
                if(AuxiliaryMethods :: checkIfReturnStatementWasProvided(providedDateOrReturnStatement)) {
                        providedDateOrReturnStatement = "";
                        break;
                }
            }
        } else {
            cout << "Format of date is not correct. Please provide YYYY-MM-DD or enter \"return\" to go back to User Menu: ";
            getline(cin, providedDateOrReturnStatement);
            providedDateOrReturnStatement = AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(providedDateOrReturnStatement);
            if(AuxiliaryMethods :: checkIfReturnStatementWasProvided(providedDateOrReturnStatement)) {
                    providedDateOrReturnStatement = "";
                    break;
            }
        }
    }

    return providedDateOrReturnStatement;
}

