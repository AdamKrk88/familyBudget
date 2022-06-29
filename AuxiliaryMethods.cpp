#include "AuxiliaryMethods.h"


string AuxiliaryMethods :: loadStringLineFromKeyboard() {

    string output = "";
    getline(cin, output);
    return output;
}


string AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(string stringToAdjust) {

    int numberOfSpacesBefore = 0;
    int numberOfSpacesAfter = 0;
    int numberOfLetter = 0;
    int lengthOfString = stringToAdjust.size();

    for(int i = 0; i < lengthOfString; i++) {
        if(stringToAdjust[i] == 32)
            numberOfSpacesBefore++;
        else
            break;
    }

    stringToAdjust = stringToAdjust.erase(0,numberOfSpacesBefore);

    lengthOfString = stringToAdjust.size();
    for(int i = lengthOfString - 1; i >= 0; i--) {
        if(stringToAdjust[i] == 32)
            numberOfSpacesAfter++;
        else
            break;
    }

    stringToAdjust = stringToAdjust.erase(lengthOfString - numberOfSpacesAfter,numberOfSpacesAfter);

    return stringToAdjust;
}


string AuxiliaryMethods :: convertFirstLetterOfOneStringToBeInUpperCaseRemainingPartInLowerCase(string text) {
    if (!text.empty()) {
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        text[0] = toupper(text[0]);
    }
    return text;
}


string AuxiliaryMethods :: convertFromIntToString(int number) {
    ostringstream ss;
    ss << number;
    string str = ss.str();
    return str;
}


int AuxiliaryMethods :: convertFromStringToInt(string text) {
    int number;
    istringstream iss(text);
    iss >> number;

    return number;
}


bool AuxiliaryMethods :: checkIfProvidedStringContainsOnlyDigits(string dataToCheck) {

    for(int i = 0; i < dataToCheck.size(); i++) {
        if(!isdigit(dataToCheck[i]))
            return false;
    }

    return true;

}


bool AuxiliaryMethods :: checkIfReturnStatementWasProvided(string providedStatement) {
    if(providedStatement[0] == 82 || providedStatement[0] == 114) {
        transform(providedStatement.begin(), providedStatement.end(), providedStatement.begin(), :: tolower);
        if(providedStatement == "return") true;
        else return false;
    } else return false;
}
