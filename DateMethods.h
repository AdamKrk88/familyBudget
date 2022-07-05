#ifndef DATEMETHODS_H
#define DATEMETHODS_H

#include <iostream>
#include <ctime>
#include <vector>

#include "AuxiliaryMethods.h"

using namespace std;


class DateMethods {

    static bool checkIfFormatOfDateIsCorrect(string providedDate);
    static bool checkIfDateIsValid(string dateToCheckInOneString);
    static bool checkIfYearIsLeap (int year);

public:
    static string getCurrentTimeFromSystem();
    static string loadDateFromKeyboard();
    static int convertDateFromStringToInt(string date);
    static string convertDateFromIntToStringInCorrectFormat(int dateAsNumber);
    static int calculateNumberOfDaysForProvidedMonth(int month, int year);
    static vector<int> convertDateInStringToIntVector(string dateFormat);
    static string convertMonthOrDayToProperFormat(int monthOrDay);
    static vector<int> enterStartEndDate();
};


#endif
