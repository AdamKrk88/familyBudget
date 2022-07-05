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


int DateMethods :: calculateNumberOfDaysForProvidedMonth(int month, int year) {

    switch(month) {
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;

    case 2:
        if(checkIfYearIsLeap(year))
            return 29;
        else
            return 28;

    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    }
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
    const int MAX_VALID_YEAR = currentDate[0];
    const int MIN_VALID_YEAR = 2000;
    const int MAX_VALID_MONTH = currentDate[1];

    if(year > MAX_VALID_YEAR || year < MIN_VALID_YEAR)
        return false;

    if(month < 1 || month > 12)
        return false;

    if(day < 1 || day > 31)
        return false;

    if(month == 2) {

        if(checkIfYearIsLeap(year))
            return (day <= 29);
        else
            return (day <= 28);
    }

    if(month == 4 || month == 6 || month == 9 || month == 11)
        return (day <= 30);

    if(month > MAX_VALID_MONTH && year == MAX_VALID_YEAR)
        return false;

    return true;
}


string DateMethods :: loadDateFromKeyboard() {

    string providedDateOrReturnStatement = "";
    getline(cin, providedDateOrReturnStatement);
    providedDateOrReturnStatement = AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(providedDateOrReturnStatement);

    while(true) {
        if(checkIfFormatOfDateIsCorrect(providedDateOrReturnStatement)) {
            if(checkIfDateIsValid(providedDateOrReturnStatement)) {
                break;
            } else {
                cout << endl << "Date is not valid" << endl << "Provide date between 2000-01-01 and last day of current month"
                     << endl << "Or enter \"return\" to go back to User Menu: ";
                getline(cin, providedDateOrReturnStatement);
                providedDateOrReturnStatement = AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(providedDateOrReturnStatement);
                if(AuxiliaryMethods :: checkIfReturnStatementWasProvided(providedDateOrReturnStatement)) {
                    providedDateOrReturnStatement = "";
                    break;
                }
            }
        } else {
            cout << endl << "Format of date is not correct."
                 << endl << "Please provide YYYY-MM-DD or enter \"return\" to go back to User Menu: ";
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


int DateMethods :: convertDateFromStringToInt(string date) {

    date = date.substr(0,4) + date.substr(5,2) + date.substr(8,2);
    int dateConvertedToInt = AuxiliaryMethods :: convertFromStringToInt(date);
    return dateConvertedToInt;
}


string DateMethods :: convertDateFromIntToStringInCorrectFormat(int dateAsNumber) {

    string dateConvertedFromInt = AuxiliaryMethods :: convertFromIntToString(dateAsNumber);
    dateConvertedFromInt = dateConvertedFromInt.substr(0,4) + '-' + dateConvertedFromInt.substr(4,2) + '-' + dateConvertedFromInt.substr(6,2);
    return dateConvertedFromInt;
}


vector<int> DateMethods :: enterStartEndDate() {

    string startDate;
    string endDate;
    int startDateConvertedToIntFormat = 0;
    int endDateConvertedToIntFormat = 0;
    vector<int> startEndDateProvidedFromKeyboard(2,0);

    while(true) {
        cout << "Provide start date: ";
        startDate = loadDateFromKeyboard();

        if(startDate == "")
            break;

        cout << "Provide end date: ";
        endDate = loadDateFromKeyboard();

        if(endDate == "")
            break;

        startDateConvertedToIntFormat = convertDateFromStringToInt(startDate);
        endDateConvertedToIntFormat = convertDateFromStringToInt(endDate);

        if(startDateConvertedToIntFormat <= endDateConvertedToIntFormat) {
            startEndDateProvidedFromKeyboard[0] = startDateConvertedToIntFormat;
            startEndDateProvidedFromKeyboard[1] = endDateConvertedToIntFormat;
            return startEndDateProvidedFromKeyboard;
        } else {
            cout << "Start date cannot be later than end date. Try once again" << endl;
        }
    }
    return startEndDateProvidedFromKeyboard;
}
