#include "UserManager.h"


void UserManager :: registerUser() {

    User user = provideDataForNewUser();

    users.push_back(user);

    cout << endl << "Account created" << endl << endl;
    system("pause");
}


User UserManager :: provideDataForNewUser() {

    User user;

    user.setUserId(loadIdForNewUser());

    string name;
    cout << "Enter your name: ";
    cin >> name;
    user.setName(name);

    string surname;
    cout << "Enter your surname: ";
    cin >> surname;
    user.setSurname(surname);

    string login;
    do {
        cout << "Enter your login: ";
        cin >> login;
        user.setLogin(login);
    } while (checkIfLoginForNewUserExistInSystem(user.getLogin()));

    string password;
    cout << "Enter password for your account to be created: ";
    cin >> password;
    cin.sync();
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
