#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

string addType(string type, string url);
void inCreaseNumQuestion(string url);

class Question;

// Type
//  0: Text Question
//  1: Picture Question
//  2: Road Sign Question
class QuestionFactory {
public:
    QuestionFactory();
    ~QuestionFactory();

public:
    static Question* getRandomQuestion(int QuestionType, string type = "A1");
    static Question* getRandomQuestion(string type = "A1");
    static Question* getQuestion(int QuestionType, int ID, string type = "A1");
    static Question* getCopy(Question*, string type = "A1");

};

class Question {
protected:
    string _question;
    vector<string> _choices;
    vector<int> _permutation;
    int _answer, _userAnswer;
    int _type, _ID;

public:
    Question();
    virtual ~Question();

public:
    string getQuestion();
    string getChoice(int);
    int getType();
    int getID();
    int getNumChoice();
    int getUserAnswer();
    int fakeUserAnswer();
    void setUserAnswer(int userAnswer);
    bool checkAnswer();
    bool checkAnswer(int);
    // typeFunction:
    //      0: questionType idQuestion userAnswer (for practice history)
    //      1: questionType idQuestion (for contest)
    //      2: userAnswer (for contest history)
    void saveQuestion(ostream &out, int contestType);
    bool isChecked();
    void removePermutation();

    void show();

};

class TextQuestion: public Question {
private:
    static string dataURL;
    static string idURL;

public:
    static vector<int> randomID;

public:
    TextQuestion(string type = "A1");
    TextQuestion(int ID, string type = "A1");
    ~TextQuestion();

public:
    static void resetRandomID(string type = "A1");
    static void addQuestion(string type, string question, vector<string> choices, int answer);

};

class PictureQuestion: public Question {
private:
    static string dataURL;
    static string idURL;

public:
    static vector<int> randomID;

public:
    string _picURL;

public:
    PictureQuestion(string type = "A1");
    PictureQuestion(int ID, string type = "A1");
    ~PictureQuestion();

public:
    static void resetRandomID(string type = "A1");
    static void addQuestion(string type, string question, vector<string> choices, int answer, string picURL);

};

class RoadSignQuestion: public Question {
private:
    static string dataURL;
    static string idURL;

public:
    static vector<int> randomID;

public:
    vector<string> _roadSignURL;

public:
    RoadSignQuestion(string type = "A1");
    RoadSignQuestion(int ID, string type = "A1");
    ~RoadSignQuestion();

public:
    static void resetRandomID(string type = "A1");
    static void addQuestion(string type, string question, vector<string> choices, int answer, vector<string> roadSignURL);

};
