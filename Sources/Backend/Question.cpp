#include "Question.h"

string addType(string type, string url) {
    string newURL = url;
    type += '/';
    newURL.insert(14, type);
    return newURL;
}

void inCreaseNumQuestion(string url) {
    ifstream inp(url.c_str(), ios::in | ios::binary);
    ofstream temp("temp.txt", ios::out | ios::binary);

    int numQuestion;
    inp >> numQuestion;
    temp << numQuestion + 1;
    temp << inp.rdbuf();

    inp.close();
    temp.close();

    remove(url.c_str());
    rename("temp.txt", url.c_str());
}

/*-----------------Question-----------------*/

Question::Question() {
    _userAnswer = -1;
}

Question::~Question() {

}

string Question::getQuestion(){
    return _question;
}

string Question::getChoice(int i){
    return _choices[_permutation[i]];
}

int Question::getNumChoice() {
    return _choices.size();
}

int Question::getType() {
    return _type;
}

int Question::getID() {
    return _ID;
}

void Question::setUserAnswer(int userAnswer) {
    _userAnswer = userAnswer;
}

bool Question::checkAnswer() {
    return _userAnswer != -1 ? _answer - 1 == _permutation[_userAnswer] : 0;
}

bool Question::checkAnswer(int i){
    return _answer - 1 == _permutation[i];
}

void Question::saveQuestion(ostream &out, int contestType) {
    if (contestType == 0)
        out << _type << " " << _ID << " " << (_userAnswer != -1 ? _permutation[_userAnswer] : -1) << endl;
    if (contestType == 1)
        out << _type << " " << _ID << endl;
    if (contestType == 2)
        out << (_userAnswer != -1 ? _permutation[_userAnswer] : -1) << endl;
}

void Question::show() {
    cout << _question;
    for (int i = 0; i < _choices.size(); ++i) {
        cout << _choices[_permutation[i]];
    }
    cout << endl;
}

bool Question::isChecked() {
    return _userAnswer != -1;
}

void Question::removePermutation() {
    sort(_permutation.begin(), _permutation.end());
}

int Question::getUserAnswer() {
    return _userAnswer != -1 ? _permutation[_userAnswer] : -1;
}

int Question::fakeUserAnswer(){
    return _userAnswer;
}
/*-----------------Text Question-----------------*/

string TextQuestion::dataURL = "data/question/TQuestion.txt";
string TextQuestion::idURL = "data/question/OffSetTQuestion.bin";
vector<int> TextQuestion::randomID(0);

// Default constructor: Get random question
TextQuestion::TextQuestion(string type) {
    _type = 0;
    if (randomID.empty())
        _ID = 1;
    else {
        _ID = randomID.back();
        randomID.pop_back();
    }

    ifstream in(addType(type, dataURL).c_str(), ios::in | ios::binary);
    ifstream inBin(addType(type, idURL).c_str(), ios::in | ios::binary);

    inBin.seekg((_ID- 1) * sizeof(int), inBin.beg);
    int offSet;
    inBin.read(reinterpret_cast<char*>(&offSet), sizeof(offSet));
    in.seekg(offSet, ios::beg);

    int numAnswer;

    in >> numAnswer >> _answer;
    _choices.resize(numAnswer);
    in.ignore(2);
    getline(in, _question);
    for (int i = 0; i < _choices.size(); ++i)
        getline(in, _choices[i]);

    _permutation.resize(numAnswer);
    for (int i = 0; i < numAnswer; ++i)
        _permutation[i] = i;
    random_shuffle(_permutation.begin(), _permutation.end());

    in.close();
    inBin.close();
}

TextQuestion::TextQuestion(int ID, string type) {
    _type = 0;
    _ID = ID;

    ifstream in(addType(type, dataURL).c_str(), ios::in | ios::binary);
    ifstream inBin(addType(type, idURL).c_str(), ios::in | ios::binary);

    inBin.seekg((_ID- 1) * sizeof(int), inBin.beg);
    int offSet;
    inBin.read(reinterpret_cast<char*>(&offSet), sizeof(offSet));
    in.seekg(offSet, ios::beg);

    int numAnswer;

    in >> numAnswer >> _answer;
    _choices.resize(numAnswer);
    in.ignore(2);
    getline(in, _question);
    for (int i = 0; i < _choices.size(); ++i)
        getline(in, _choices[i]);

    _permutation.resize(numAnswer);
    for (int i = 0; i < numAnswer; ++i)
        _permutation[i] = i;
    random_shuffle(_permutation.begin(), _permutation.end());

    in.close();
    inBin.close();
}

TextQuestion::~TextQuestion() {
    // do something
}

void TextQuestion::resetRandomID(string type) {
    ifstream in(addType(type, dataURL).c_str(), ios::in | ios::binary);
    int n;
    in >> n;
    randomID.resize(n);
    for (int i = 1; i <= n; ++i)
        randomID[i - 1] = i;
    random_shuffle(randomID.begin(), randomID.end());
    in.close();
}

/*-----------------Picture Question-----------------*/

string PictureQuestion::dataURL = "data/question/PQuestion.txt";
string PictureQuestion::idURL = "data/question/OffSetPQuestion.bin";
vector<int> PictureQuestion::randomID(0);

// Default constructor: Get random question
PictureQuestion::PictureQuestion(string type) {
    _type = 1;
    if (randomID.empty())
        _ID = 1;
    else {
        _ID = randomID.back();
        randomID.pop_back();
    }

    ifstream in(addType(type, dataURL).c_str(), ios::in | ios::binary);
    ifstream inBin(addType(type, idURL).c_str(), ios::in | ios::binary);

    inBin.seekg((_ID - 1) * sizeof(int), inBin.beg);
    int offSet;
    inBin.read(reinterpret_cast<char*>(&offSet), sizeof(offSet));
    in.seekg(offSet, ios::beg);

    int numAnswer;

    in >> numAnswer >> _answer;
    _choices.resize(numAnswer);
    in.ignore(2);
    getline(in, _question);
    for (int i = 0; i < _choices.size(); ++i)
        getline(in, _choices[i]);
    getline(in, _picURL);
    if (_picURL.back() == '\r') _picURL.pop_back();
    _permutation.resize(numAnswer);
    for (int i = 0; i < numAnswer; ++i)
        _permutation[i] = i;
    random_shuffle(_permutation.begin(), _permutation.end());

    in.close();
    inBin.close();
}

PictureQuestion::PictureQuestion(int ID, string type) {
    _type = 1;
    _ID = ID;

    ifstream in(addType(type, dataURL).c_str(), ios::in | ios::binary);
    ifstream inBin(addType(type, idURL).c_str(), ios::in | ios::binary);

    inBin.seekg((ID - 1) * sizeof(int), inBin.beg);
    int offSet;
    inBin.read(reinterpret_cast<char*>(&offSet), sizeof(offSet));
    in.seekg(offSet, ios::beg);
    int numAnswer;

    in >> numAnswer >> _answer;
    _choices.resize(numAnswer);
    in.ignore(2);
    getline(in, _question);
    for (int i = 0; i < _choices.size(); ++i)
        getline(in, _choices[i]);
    getline(in, _picURL);
    if (_picURL.back() == '\r') _picURL.pop_back();
    _permutation.resize(numAnswer);
    for (int i = 0; i < numAnswer; ++i)
        _permutation[i] = i;
    random_shuffle(_permutation.begin(), _permutation.end());

    in.close();
    inBin.close();
}

PictureQuestion::~PictureQuestion() {

}

void PictureQuestion::resetRandomID(string type) {
    ifstream in(addType(type, dataURL).c_str(), ios::in | ios::binary);
    int n;
    in >> n;
    randomID.resize(n);
    for (int i = 1; i <= n; ++i)
        randomID[i - 1] = i;
    random_shuffle(randomID.begin(), randomID.end());
    in.close();
}

/*-----------------Road Sign Question-----------------*/

string RoadSignQuestion::dataURL = "data/question/RSQuestion.txt";
string RoadSignQuestion::idURL = "data/question/OffSetRSQuestion.bin";
vector<int> RoadSignQuestion::randomID(0);

// Default constructor: Get random question
RoadSignQuestion::RoadSignQuestion(string type) {
    _type = 2;
    if (randomID.empty())
        _ID = 1;
    else {
        _ID = randomID.back();
        randomID.pop_back();
    }

    ifstream in(addType(type, dataURL).c_str(), ios::in | ios::binary);
    ifstream inBin(addType(type, idURL).c_str(), ios::in | ios::binary);

    inBin.seekg((_ID - 1) * sizeof(int), inBin.beg);
    int offSet;
    inBin.read(reinterpret_cast<char*>(&offSet), sizeof(offSet));
    in.seekg(offSet, ios::beg);

    int numAnswer, numPic;

    in >> numAnswer >> _answer >> numPic;
    _choices.resize(numAnswer);
    _roadSignURL.resize(numPic);
    in.ignore(2);
    getline(in, _question);
    for (int i = 0; i < _choices.size(); ++i)
        getline(in, _choices[i]);
    for (int i = 0; i < _roadSignURL.size(); ++i){
        getline(in, _roadSignURL[i]);
        if (_roadSignURL[i].back() == '\r') _roadSignURL[i].pop_back();
    }
    _permutation.resize(numAnswer);
    for (int i = 0; i < numAnswer; ++i)
        _permutation[i] = i;
    random_shuffle(_permutation.begin(), _permutation.end());

    in.close();
    inBin.close();
}

RoadSignQuestion::RoadSignQuestion(int ID, string type) {
    _type = 2;
    _ID = ID;

    ifstream in(addType(type, dataURL).c_str(), ios::in | ios::binary);
    ifstream inBin(addType(type, idURL).c_str(), ios::in | ios::binary);

    inBin.seekg((_ID - 1) * sizeof(int), inBin.beg);
    int offSet;
    inBin.read(reinterpret_cast<char*>(&offSet), sizeof(offSet));
    in.seekg(offSet, ios::beg);

    int numAnswer, numPic;

    in >> numAnswer >> _answer >> numPic;
    _choices.resize(numAnswer);
    _roadSignURL.resize(numPic);
    in.ignore(2);
    getline(in, _question);
    for (int i = 0; i < _choices.size(); ++i)
        getline(in, _choices[i]);
    for (int i = 0; i < _roadSignURL.size(); ++i){
        getline(in, _roadSignURL[i]);
        if (_roadSignURL[i].back() == '\r') _roadSignURL[i].pop_back();
    }

    _permutation.resize(numAnswer);
    for (int i = 0; i < numAnswer; ++i)
        _permutation[i] = i;
    random_shuffle(_permutation.begin(), _permutation.end());

    in.close();
    inBin.close();
}

RoadSignQuestion::~RoadSignQuestion() {

}

void RoadSignQuestion::resetRandomID(string type) {
    ifstream in(addType(type, dataURL).c_str(), ios::in | ios::binary);
    int n;
    in >> n;
    randomID.resize(n);
    for (int i = 1; i <= n; ++i)
        randomID[i - 1] = i;
    random_shuffle(randomID.begin(), randomID.end());
    in.close();
}

/*-----------------Question Factory-----------------*/

QuestionFactory::QuestionFactory() {
    // do something
}

QuestionFactory::~QuestionFactory() {
    // do something
}

Question* QuestionFactory::getRandomQuestion(int QuestionType, string type) {
    if (QuestionType == 0)
        return new TextQuestion(type);
    if (QuestionType == 1)
        return new PictureQuestion(type);
    return new RoadSignQuestion(type);
}

Question* QuestionFactory::getRandomQuestion(string type) {
    int QuestionType = rand() % 3;
    return QuestionFactory::getRandomQuestion(QuestionType, type);
}

Question* QuestionFactory::getQuestion(int QuestionType, int ID, string type) {
    if (QuestionType == 0)
        return new TextQuestion(ID, type);
    if (QuestionType == 1)
        return new PictureQuestion(ID, type);
    return new RoadSignQuestion(ID, type);
}

Question* QuestionFactory::getCopy(Question *other, string type) {
    // cout << other->getType() << " " <<  other->getID() << " " << type << endl;
    Question* q = QuestionFactory::getQuestion(other->getType(), other->getID(), type);
    q->removePermutation();
    q->setUserAnswer(other->getUserAnswer());
    return q;
}

void TextQuestion::addQuestion(string type, string question, vector<string> choices, int answer) {
    // increase numquestion
    inCreaseNumQuestion(addType(type, dataURL).c_str());
    // add question
    ifstream inp(addType(type, dataURL).c_str(), ios::in | ios::binary);
    inp.seekg(0, ios::end);
    int offSet = inp.tellg();
    inp.close();

    ofstream out(addType(type, dataURL).c_str(), ios::app | ios::binary);
    ofstream outBin(addType(type, idURL).c_str(), ios::app | ios::binary);

    cout << offSet << endl;
    outBin.write(reinterpret_cast<char*>(&offSet), sizeof(offSet));
    out << (int)(choices.size()) << " " << answer + 1 << "\r\n";
    out << question << "\r\n";
    for (int i = 0; i < choices.size(); ++i)
        out << choices[i] << "\r\n";

    out.close();
    outBin.close();
}

void PictureQuestion::addQuestion(string type, string question, vector<string> choices, int answer, string picURL) {
    // increase numquestion
    inCreaseNumQuestion(addType(type, dataURL).c_str());
    // add question
    ifstream inp(addType(type, dataURL).c_str(), ios::in | ios::binary);
    inp.seekg(0, ios::end);
    int offSet = inp.tellg();
    inp.close();

    ofstream out(addType(type, dataURL).c_str(), ios::app | ios::binary);
    ofstream outBin(addType(type, idURL).c_str(), ios::app | ios::binary);

    outBin.write(reinterpret_cast<char*>(&offSet), sizeof(offSet));
    out << (int)(choices.size()) << " " << answer + 1 << "\r\n";
    out << question << "\r\n";
    for (int i = 0; i < choices.size(); ++i)
        out << choices[i] << "\r\n";
    out << picURL << "\r\n";

    out.close();
    outBin.close();
}

void RoadSignQuestion::addQuestion(string type, string question, vector<string> choices, int answer, vector<string> roadSignURL) {
    // increase numquestion
    inCreaseNumQuestion(addType(type, dataURL).c_str());
    // add question
    ifstream inp(addType(type, dataURL).c_str(), ios::in | ios::binary);
    inp.seekg(0, ios::end);
    int offSet = inp.tellg();
    inp.close();

    ofstream out(addType(type, dataURL).c_str(), ios::app | ios::binary);
    ofstream outBin(addType(type, idURL).c_str(), ios::app | ios::binary);

    outBin.write(reinterpret_cast<char*>(&offSet), sizeof(offSet));
    out << (int)(choices.size()) << " " << answer + 1 << " " << (int)(roadSignURL.size()) << "\r\n";
    out << question << "\r\n";
    for (int i = 0; i < choices.size(); ++i)
        out << choices[i] << "\r\n";
    for (int i = 0; i < roadSignURL.size(); ++i)
        out << roadSignURL[i] << "\r\n";

    out.close();
    outBin.close();
}
