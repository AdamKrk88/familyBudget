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


int AuxiliaryMethods :: checkIfLineContainZeroOneOrMoreSigns(string text, char sign) {

    size_t position = text.find(sign);

    if(position != string :: npos) {
        position = text.find(sign,position + 1);

        if(position != string :: npos) {
            return 2;
        } else {
            return 1;
        }

    } else {
        return 0;
    }
}

vector<int> AuxiliaryMethods :: calculateHowManyDotsOrCommasIsInTextLine(string text) {

    vector<int> numberOfSigns(2);
    numberOfSigns[0] = checkIfLineContainZeroOneOrMoreSigns(text, '.');
    numberOfSigns[1] = checkIfLineContainZeroOneOrMoreSigns(text, ',');

    return numberOfSigns;

}


string AuxiliaryMethods :: replaceCommaByDot(string textToAdjust) {


    char sign = ',';
    size_t position = textToAdjust.find(sign);
    textToAdjust.replace(position,1,".");

    return textToAdjust;
}


char AuxiliaryMethods :: loadCharFromKeyboard() {
    string inputFromKeyboard = "";
    char charLoadedFromKeyboard  = {0};

    while (true) {
        getline(cin, inputFromKeyboard);

        if (inputFromKeyboard.length() == 1) {
            charLoadedFromKeyboard = inputFromKeyboard[0];
            break;
        }
        cout << "It is not single char. Please try once again" << endl;

    }
    return charLoadedFromKeyboard;
}


bool AuxiliaryMethods :: checkIfDoubleNumberIsInteger(double numberToCheck) {

    double intpart;
    double fractionalPartOfDoubleNumber = 0;
    fractionalPartOfDoubleNumber = modf(numberToCheck, &intpart);

    if(fractionalPartOfDoubleNumber == 0) {
        return true;
    }

    return false;
}
