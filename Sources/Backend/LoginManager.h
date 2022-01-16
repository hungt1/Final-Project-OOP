#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <sstream>

#include "Account.h"

using namespace std;

// utility function remove leading and trailing spaces in string
string removeSpaces(string str);

class LoginManager {
private:
    static string dataURL;
    static LoginManager* instancePtr;
    static regex usernamePattern;
    static regex passwordPattern;
    static regex mailPattern;
    static regex phonePattern;

public:
    static Account* findRole(string username, string password);
    static int registerUser(string username, string password, string name, string mail, string phone);
    static int editUser(string username, string password, string name, string mail, string phone);

};
