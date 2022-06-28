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
