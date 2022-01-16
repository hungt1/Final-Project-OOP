#include "QuestionSet.h"

string toString(int x) {
    stringstream ss;
    ss << x;
    return ss.str();
}

bool checkExist(string URL) {
    ifstream inp(URL.c_str());
    if (inp) {
        inp.close();
        return true;
    }
    return false;
}

QuestionSet::QuestionSet(int sz, string type) {
    TextQuestion::resetRandomID(type);
    PictureQuestion::resetRandomID(type);
    RoadSignQuestion::resetRandomID(type);
    _code = type + "-0";
    _password = "";
    for (int i = 0; i < sz; ++i)
        _questions.push_back(QuestionFactory::getRandomQuestion(type));
}

QuestionSet::QuestionSet(string code) {
    _code = code;
    string URL = "data/questionset/" + _code + ".txt";
    string hour, contestType = _code.substr(0, 2);
    ifstream inp(URL.c_str(), ios::in | ios::binary);

    getline(inp, hour);
    getline(inp, hour);
    getline(inp, _password);
    _password.pop_back();
    int numQuestions;
    inp >> numQuestions;
    for (int i = 0; i < numQuestions; ++i) {
        int questionType, ID;
        inp >> questionType >> ID;
        _questions.push_back(QuestionFactory::getQuestion(questionType, ID, contestType));
        // _questions.back()->show();
    }

    inp.close();
}

QuestionSet::QuestionSet(const QuestionSet &other) {
    _code = other._code;
    _password = other._password;
    for (int i = 0; i < other._questions.size(); ++i) {
        //other._questions[i]->show();
        this->_questions.push_back(QuestionFactory::getCopy(other._questions[i], _code.substr(0, 2)));
        //other._questions[i]->show();
    }
}

QuestionSet& QuestionSet::operator = (const QuestionSet &other) {
    _questions.clear();
    _code = other._code;
    _password = other._password;
    for (int i = 0; i < other._questions.size(); ++i)
        this->_questions.push_back(QuestionFactory::getCopy(other._questions[i], _code.substr(0, 2)));
    return *this;
}

QuestionSet::~QuestionSet() {
    for (int i = 0; i < _questions.size(); ++i)
        delete _questions[i];
}

Question* QuestionSet::getQuestion(int idx){
    if (idx < 0 || idx >= getNumQuestion()) return nullptr;
    return _questions[idx];
}

bool QuestionSet::checkPassword(string code, string pass) {
    string URL = "data/questionset/" + code + ".txt";
    string password;
    ifstream inp(URL.c_str(), ios::in | ios::binary);
    getline(inp, password);
    getline(inp, password);
    getline(inp, password);
    password.pop_back();
    inp.close();
    return (password == pass);
}

int QuestionSet::getNumQuestion() const {
    return _questions.size();
}

int QuestionSet::getPoint() const {
    int ret = 0;
    for (int i = 0; i < _questions.size(); ++i)
        ret += _questions[i]->checkAnswer();
    return ret;
}

void QuestionSet::setUserAnswer(int idQuestion, int userAnswer) {
    if (idQuestion >= _questions.size())
        return;
    _questions[idQuestion]->setUserAnswer(userAnswer);
}

void QuestionSet::getAllQuestion(string type) {
    for (int i = 0; i < _questions.size(); i++){
        delete _questions[i];
    }
    _questions.clear();
    _code = type;
    TextQuestion::resetRandomID(type);
    PictureQuestion::resetRandomID(type);
    RoadSignQuestion::resetRandomID(type);
    while (TextQuestion::randomID.size())
        _questions.push_back(QuestionFactory::getRandomQuestion(0, type));
    while (PictureQuestion::randomID.size())
        _questions.push_back(QuestionFactory::getRandomQuestion(1, type));
    while (RoadSignQuestion::randomID.size())
        _questions.push_back(QuestionFactory::getRandomQuestion(2, type));
}

// contestType
//      0: practice history (user)
//      1: contest (admin)
//      2: contest history (user)
void QuestionSet::saveHistory(string username, string name) {
    int contestType = _code[3] == '0' ? 0 : 2;
    string URL = "data/history/user/" + username + ".txt";
    ofstream out(URL.c_str(), ios::app);
    out << _code << endl << _questions.size() << endl;
    for (int i = 0; i < _questions.size(); ++i)
        _questions[i]->saveQuestion(out, contestType);
    out.close();
    if (contestType == 2) {
        URL = "data/history/contest/" + _code + ".csv";
        out.open(URL.c_str(), ios::app);
        out << name << "," << this->getPoint() << "/" << this->getNumQuestion() << endl;
        out.close();
    }
}

void QuestionSet::saveContest(string startTime, string password, int duration) {
    string URL;
    int l = 1, r = (int)(1e9);
    while (l <= r) {
        int mid = l + r >> 1;
        if (checkExist("data/questionset/" + _code + "-" + toString(mid) + ".txt"))
            l = mid + 1;
        else
            r = mid - 1;
    }
    URL = "data/questionset/" + _code + "-" + toString(l) + ".txt";

    ofstream out(URL.c_str(), ios::out);
    out << duration << endl << startTime << endl << password << endl;
    int sz = 0;
    for (int i = 0; i < _questions.size(); ++i)
        sz += _questions[i]->isChecked();
    out << sz << endl;
    for (int i = 0; i < _questions.size(); ++i)
        if (_questions[i]->isChecked())
            _questions[i]->saveQuestion(out, 1);
    out.close();

    out.open("data/upcoming/contest.txt", ios::app);
    out <<  _code + "-" + toString(l) << endl;
    out.close();
}

void QuestionSet::show() {
    cout << _questions.size() << endl;
    for (int i = 0; i < _questions.size(); ++i) {
        cout << "Cau " << i << ": " << _questions[i]->checkAnswer() << "/1" << endl;
        _questions[i]->show();
    }
    cout << "Diem: " << this->getPoint() << endl;
}

bool QuestionSet::loadHistory(istream &inp) {
    if (!(inp >> _code))
        return false;
    _questions.clear();
    int numQuestions;
    inp >> numQuestions;
    if (_code[3] != '0') {
        this->~QuestionSet();
        new (this)QuestionSet(_code);
    }
    for (int i = 0; i < numQuestions; ++i) {
        int questionType, ID, userAnswer;
        if (_code[3] == '0') {
            inp >> questionType >> ID;
            _questions.push_back(QuestionFactory::getQuestion(questionType, ID, _code.substr(0, 2)));
        }
        inp >> userAnswer;
        _questions[i]->removePermutation();
        _questions[i]->setUserAnswer(userAnswer);
        // cout << questionType << " " << ID << " " << userAnswer << " " << i << endl;
    }
    return true;
}

vector<QuestionSet> QuestionSet::loadUserHistory(string username) {
    string URL = "data/history/user/" + username + ".txt";
    ifstream inp(URL.c_str(), ios::in);
    vector<QuestionSet> history;
    while (true) {
        QuestionSet qs;
        if (!qs.loadHistory(inp))
            break;
        history.push_back(qs);
    }
    inp.close();
    return history;
}

string QuestionSet::getTime() {
    if (_code[3] == 0)
        return "";
    ifstream inp("data/questionset/" + _code + ".txt");
    string Time;
    getline(inp, Time);
    getline(inp, Time);
    inp.close();
    return Time;
}

string QuestionSet::getType() {
    return _code;
}

int QuestionSet::getStatus(int idQuestion) {
    if (!_questions[idQuestion]->isChecked())
        return -1;
    return _questions[idQuestion]->checkAnswer();
}

int QuestionSet::getChecked() {
    int sum = 0;
    for (int i = 0; i < _questions.size(); ++i)
        sum += _questions[i]->isChecked();
    return sum;
}

string QuestionSet::getContestTime(string code) {
    string URL = "data/questionset/" + code + ".txt";
    ifstream inp(URL.c_str());
    string Time;
    getline(inp, Time);
    getline(inp, Time);
    inp.close();
    return Time;
}

vector<string> QuestionSet::getUpcomingContest() {
    string URL = "data/upcoming/contest.txt";
    ifstream inp(URL.c_str());
    vector<string> uContest;
    string buffer;
    while (getline(inp, buffer)) {
        if (buffer.back() < '0' || '9' < buffer.back())
            buffer.pop_back();
        uContest.push_back(buffer);
    }
    inp.close();
    return uContest;
}

int QuestionSet::getDuration() {
    if (_code[3] == 0)
        return 0;
    ifstream inp("data/questionset/" + _code + ".txt");
    int duration;
    inp >> duration;
    inp.close();
    return duration;
}

string QuestionSet::getPassword(){
    return _password;
}
