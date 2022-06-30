#ifndef AUXILIARYMETHODS_H
#define AUXILIARYMETHODS_H

#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;


class AuxiliaryMethods {

static int checkIfLineContainZeroOneOrMoreSigns(string text, char sign);

public:
static string loadStringLineFromKeyboard();
static string deleteSpaceBeforeAndAfterString(string stringToAdjust);
static string convertFirstLetterOfOneStringToBeInUpperCaseRemainingPartInLowerCase(string text);
static string convertFromIntToString(int number);
static int convertFromStringToInt(string text);
static bool checkIfProvidedStringContainsOnlyDigits(string dataToCheck);
static bool checkIfReturnStatementWasProvided(string providedStatement);
static bool checkIfLineContainZeroOrOnlyOneSign(string text, char sign);
static string replaceCommaByDot(string textToAdjust);
static vector<int> calculateHowManyDotsOrCommasIsInTextLine(string text);

};



#endif
