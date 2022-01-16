#pragma once

#include <iostream>
#include <string>

using namespace std;

class Account {
private:
    int _role;
    string _username;
    string _name;
    string _mail;
    string _phone;

private:
    static Account *accountPtr;

private:
    Account();
    Account(int, string, string, string, string);

public:
    static int getRole();
    static string getUsername();
    static string getName();
    static string getMail();
    static string getPhone();

public:
    static Account* getAccount(int, string, string, string, string);

};
