#include "Menu.h"

char Menu :: selectOptionFromMainMenu() {

    system("cls");
    char chosenOption = {0};

    cout << "    >>> MAIN MENU <<<" << endl;
    cout << "---------------------------" << endl;
    cout << "1. Registration" << endl;
    cout << "2. Log In" << endl;
    cout << "3. Close program" << endl;
    cout << "---------------------------" << endl;
    cout << "Your choice: ";
    chosenOption = AuxiliaryMethods :: loadCharFromKeyboard();

    return chosenOption;
}


char Menu :: selectOptionFromUserMenu() {

    system("cls");
    char chosenOption = {0};

    cout << " >>> USER MENU <<<" << endl;
    cout << "---------------------------" << endl;
    cout << "1. Add income" << endl;
    cout << "2. Add expense" << endl;
    cout << "3. Print balance for current month" << endl;
    cout << "4. Print balance for previous month" << endl;
    cout << "5. Print balance for provided period of time" << endl;
    cout << "---------------------------" << endl;
    cout << "6. Change password" << endl;
    cout << "7. Log out" << endl;
    cout << "---------------------------" << endl;
    cout << "Your choice: ";
    chosenOption = AuxiliaryMethods :: loadCharFromKeyboard();

    return chosenOption;

}
