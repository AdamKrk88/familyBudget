#include "UserManager.h"


void UserManager :: registerUser() {

    User user = provideDataForNewUser();

    users.push_back(user);
    userFile.addUserToFile(user);

    cout << endl << "Account created" << endl << endl;
    system("pause");
}


User UserManager :: provideDataForNewUser() {

    User user;

    user.setUserId(loadIdForNewUser());

    string name;
    cout << "Enter your name: ";
    cin >> name;
    name = AuxiliaryMethods :: convertFirstLetterOfOneStringToBeInUpperCaseRemainingPartInLowerCase(name);
    user.setName(name);

    string surname;
    cout << "Enter your surname: ";
    cin >> surname;
    cin.sync();
    surname = AuxiliaryMethods :: convertFirstLetterOfOneStringToBeInUpperCaseRemainingPartInLowerCase(surname);
    user.setSurname(surname);

    string login;
    do {
        cout << "Enter your login: ";
        login = AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(AuxiliaryMethods :: loadStringLineFromKeyboard());
        user.setLogin(login);
    } while (checkIfLoginForNewUserExistInSystem(user.getLogin()));

    string password;
    cout << "Enter password for your account to be created: ";
    password = AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(AuxiliaryMethods :: loadStringLineFromKeyboard());
    user.setPassword(password);

    return user;
}


int UserManager :: loadIdForNewUser() {

    if (users.empty())
        return 1;
    else
        return users.back().getUserId() + 1;
}


bool UserManager :: checkIfLoginForNewUserExistInSystem(string login) {

    for (int i = 0; i < users.size(); i++) {
        if (users[i].getLogin() == login) {
            cout << endl << "User with this login exists. Please try once again" << endl << endl;
            return true;
        }
    }
    return false;
}


void UserManager :: printAllUsers() {

for(int i = 0; i < users.size(); i++) {
    cout << users[i].getUserId() << endl;
    cout << users[i].getLogin() << endl;
    cout << users[i].getPassword() << endl;
    cout << users[i].getName() << endl;
    cout << users[i].getSurname() << endl;
}
}


void UserManager :: logInUser() {
    string login = "", password = "";

    cout << "Enter your login: ";
    login = AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(AuxiliaryMethods :: loadStringLineFromKeyboard());

    vector <User>::iterator itr = users.begin();
    while (itr != users.end()) {
        if (itr -> getLogin() == login) {
            for (int numberOfAttempts = 3; numberOfAttempts > 0; numberOfAttempts--) {
                cout << "Enter your password. Number of attempts: " << numberOfAttempts << ": ";
                password = AuxiliaryMethods :: deleteSpaceBeforeAndAfterString(AuxiliaryMethods :: loadStringLineFromKeyboard());

                if (itr -> getPassword() == password) {
                    cout << endl << "You logged in." << endl << endl;
                    system("pause");
                    loggedUserId = itr -> getUserId();
                    return;
                }
            }
            cout << "You provided incorrect password 3 times." << endl;
            system("pause");
            loggedUserId = 0;
            return;
        }
        itr++;
    }
    cout << "This login does not exist in system" << endl << endl;
    system("pause");
    loggedUserId = 0;
    return;
}


bool UserManager :: checkIfUserIsLoggedIn() {
    if (loggedUserId > 0)
        return true;
    else
        return false;
}
