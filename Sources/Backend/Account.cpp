#include "Account.h"

Account* Account::accountPtr = nullptr;

Account::Account():
    _name(""), _mail(""), _phone("") {}

Account::Account(int role, string username, string name, string mail, string phone):
    _role(role), _username(username), _name(name), _mail(mail), _phone(phone) {}

Account* Account::getAccount(int role, string username, string name, string mail, string phone) {
    if (accountPtr != nullptr)
        delete accountPtr;
    accountPtr = new Account(role, username, name, mail, phone);
    return accountPtr;
}

int Account::getRole() {
    return accountPtr->_role;
}

string Account::getUsername() {
    return accountPtr->_username;
}

string Account::getName() {
    return accountPtr->_name;
}

string Account::getMail() {
    return accountPtr->_mail;
}

string Account::getPhone() {
    return accountPtr->_phone;
}

