#ifndef AUXILIARYMETHODS_H
#define AUXILIARYMETHODS_H

#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;


class AuxiliaryMethods {

public:
static string loadStringLineFromKeyboard();
static string deleteSpaceBeforeAndAfterString(string stringToAdjust);
static string convertFirstLetterOfOneStringToBeInUpperCaseRemainingPartInLowerCase(string text);
static string convertFromIntToString(int number);

};



#endif
