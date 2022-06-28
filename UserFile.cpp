#include "UserFile.h"


void UserFile :: addUserToFile(User user) {

    CMarkup xml;
    bool fileExistCorrectlyFormatted = xml.Load(NAME_OF_USER_FILE);

    if(!fileExistCorrectlyFormatted) {
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Users");
    }

    xml.FindElem();
    xml.IntoElem();
    xml.AddElem("User");
    xml.IntoElem();
    xml.AddElem("UserId",AuxiliaryMethods :: convertFromIntToString(user.getUserId()));
    xml.AddElem("Login",user.getLogin());
    xml.AddElem("Password",user.getPassword());
    xml.AddElem("Name",user.getName());
    xml.AddElem("Surname",user.getSurname());

    xml.Save(NAME_OF_USER_FILE);
}


vector<User> UserFile :: loadAllUsersFromFileToVector() {

    CMarkup xml;
    User user;
    vector<User> users;
    int numberOfItemFromFile = 0;
    bool fileExistCorrectlyFormatted = xml.Load(NAME_OF_USER_FILE);

    if(fileExistCorrectlyFormatted) {
        xml.FindElem();
        xml.IntoElem();

        while(xml.FindElem()) {
            xml.IntoElem();

            while(xml.FindElem()) {

                switch(numberOfItemFromFile) {
                case 0:
                    user.setUserId(atoi(xml.GetData().c_str()));
                    numberOfItemFromFile++;
                    break;

                case 1:
                    user.setLogin(xml.GetData());
                    numberOfItemFromFile++;
                    break;

                case 2:
                    user.setPassword(xml.GetData());
                    numberOfItemFromFile++;
                    break;

                case 3:
                    user.setName(xml.GetData());
                    numberOfItemFromFile++;
                    break;

                case 4:
                    user.setSurname(xml.GetData());
                    numberOfItemFromFile++;
                    break;
                }
            }
            users.push_back(user);
            numberOfItemFromFile = 0;
            xml.OutOfElem();
        }
        xml.OutOfElem();
    }
    return users;
}
