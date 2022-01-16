#pragma once

#include "Question.h"
#include <sstream>
#include <vector>

// ultility function convert integer to string
string toString(int);

// ultility function check if file exists
bool checkExist(string);

class QuestionSet {
protected:
    vector<Question*> _questions;
    string _code, _password;

public:
    QuestionSet(int sz = 0, string type = "A1");
    QuestionSet(string code);
    virtual ~QuestionSet();

public:
    QuestionSet(const QuestionSet &other);
    QuestionSet& operator = (const QuestionSet &other);

public:
    Question* getQuestion(int);
    void getAllQuestion(string type);
    int getNumQuestion() const;
    void setUserAnswer(int idQuestion, int userAnswer);
    int getPoint() const;
    string getTime();
    string getType();
    int getStatus(int idQuestion);
    int getChecked();
    // contestType
    //      0: practice history (user)
    //      1: contest (admin)
    //      2: contest history (user)
    void saveHistory(string username, string name = "");
    void saveContest(string startTime, string password, int duration);
    bool loadHistory(istream &inp);
    void show();
    int getDuration();
    string getPassword();

public:
    static vector<QuestionSet> loadUserHistory(string username);
    static string getContestTime(string code);
    static vector<string> getUpcomingContest();
    static bool checkPassword(string code, string pass);
};
