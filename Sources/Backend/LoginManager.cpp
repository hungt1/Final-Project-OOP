#include "LoginManager.h"

LoginManager* LoginManager::instancePtr = nullptr;
string LoginManager::dataURL = "data/account/account.csv";
regex LoginManager::usernamePattern("^\\w+$");
regex LoginManager::passwordPattern("^(\\w|[@!?$]){8,}$");
regex LoginManager::phonePattern("^(\\+84|0)\\d{9,10}$");
regex LoginManager::mailPattern("^(\\w|\\.|_)+@(\\w+)(\\.(\\w+))+$");

string removeSpaces(string str) {
    while (str.size() && str.back() == ' ')
        str.pop_back();
    reverse(str.begin(), str.end());
    while (str.size() && str.back() == ' ')
        str.pop_back();
    reverse(str.begin(), str.end());
    return str;
}

bool isValid(string &str, regex pattern) {
    str = removeSpaces(str);
    // cout << str << endl;
    return regex_match(str, pattern);
}

Account* LoginManager::findRole(string username, string password) {
    if (!isValid(username, usernamePattern))
        return nullptr;
    if (!isValid(password, passwordPattern))
        return nullptr;

    int role = -1;
    ifstream inp(dataURL.c_str(), ios::in);

    Account *acc = nullptr;
    string buffer;
    vector<string> line;

    getline(inp, buffer);
    while (getline(inp, buffer, ',')) {
        if (buffer == username) {
            getline(inp, buffer, ',');
            if (buffer == password) {
                getline(inp, buffer);
                stringstream ss(buffer);
                while (getline(ss, buffer, ','))
                    line.push_back(buffer);
            } else
                return nullptr;
            acc = Account::getAccount(line[0][0] == '1', username, line[1], line[2], line[3]);
            break;
        }
        getline(inp, buffer);
    }

    inp.close();
    return acc;
}

int LoginManager::registerUser(string username, string password, string name, string mail, string phone) {
    if (!isValid(username, usernamePattern))
        return 1;
    if (!isValid(password, passwordPattern))
        return 2;
    if (!isValid(mail, mailPattern))
        return 3;
    if (!isValid(phone, phonePattern))
        return 4;

    ifstream inp(dataURL.c_str(), ios::in);
    string buffer;
    while (getline(inp, buffer, ',')) {
        if (buffer == username) {
            inp.close();
            return 5;
        }
        getline(inp, buffer);
    }
    inp.close();

    ofstream out(dataURL.c_str(), ios::app);
    out << username << "," << password << ",0," << name << "," << mail << "," << phone << endl;
    out.close();
    return 0;
}

int LoginManager::editUser(string username, string password, string name, string mail, string phone) {
    if (!isValid(username, usernamePattern))
        return 1;
    if (!isValid(password, passwordPattern))
        return 2;
    if (!isValid(mail, mailPattern))
        return 3;
    if (!isValid(phone, phonePattern))
        return 4;

    ifstream inp(dataURL.c_str(), ios::in);
    ofstream out("temp.txt", ios::out);

    string buffer;
    getline(inp, buffer);
    out << buffer << endl;
    while (getline(inp, buffer, ',')) {
        if (buffer != username) {
            out << buffer << ",";
            getline(inp, buffer);
            out << buffer << endl;
        } else
            getline(inp, buffer);
    }

    out << username << "," << password << ",0," << name << "," << mail << "," << phone << endl;

    inp.close();
    out.close();

    remove(dataURL.c_str());
    rename("temp.txt", dataURL.c_str());

    return 0;
}
