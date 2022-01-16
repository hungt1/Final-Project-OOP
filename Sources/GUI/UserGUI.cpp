#include "UserGUI.h"
#include "ui_UserGUI.h"
#include <QDateTime>
#include "../Backend/Account.h"
#include "../Backend/LoginManager.h"
#include <QMessageBox>

UserGUI::UserGUI(QWidget *parent) :
    QDialog(parent, Qt::CustomizeWindowHint),
    ui(new Ui::UserGUI)
{
    ui->setupUi(this);
    setupContestPage();
    setupPracticePage();
    setupHistoryPage();
    on_btnHome_clicked();
    ui->lblName->setText(QString::fromStdString(Account::getName()));
}

UserGUI::~UserGUI(){
    delete ui;
}

void UserGUI::on_btnExit_clicked(){
    this->parentWidget()->show(); this->close();
}


void UserGUI::on_btnShowMinimize_clicked(){
    this->showMinimized();
}

void UserGUI::on_btnChangeSize_clicked(){
    if (this->isMaximized()){
        this->showNormal();
        ui->btnChangeSize->setIcon(QIcon("./icon/light-purple/maximize-2.svg"));
    }
    else {
        this->showMaximized();
        ui->btnChangeSize->setIcon(QIcon("./icon/light-purple/minimize-2.svg"));
    }
}

void UserGUI::on_btnHome_clicked(){
    ui->stackedWidget->setCurrentWidget(ui->homePage);
    ui->label->setText("Trang Chủ");
}

void UserGUI::on_btnContest_clicked(){
    ui->stackedWidget->setCurrentWidget(ui->contestPage);
    ui->label->setText("Các cuộc thi");
}

void UserGUI::on_btnPractice_clicked(){
    ui->stackedWidget->setCurrentWidget(ui->practicePage);
    ui->label->setText("Luyện tập");
}

void UserGUI::on_btnHistory_clicked(){
    ui->stackedWidget->setCurrentWidget(ui->historyPage);
    ui->label->setText("Lịch sử");
}

void UserGUI::setupContestPage(){
    for (int i = 0; i < 3; i++){
        ContestWidget* myWidget = new ContestWidget(this, contestName[i]);
        ui->Frame01->layout()->addWidget(myWidget);
        contests.push_back(myWidget);
    }
    for (int i = 3; i < 6; i++){
        ContestWidget* myWidget = new ContestWidget(this, contestName[i]);
        ui->Frame02->layout()->addWidget(myWidget);
        contests.push_back(myWidget);
    }
    vector<string> cur_contest = QuestionSet::getUpcomingContest();
    sort(cur_contest.begin(), cur_contest.end(), [](const string& cur, const string& other){
        string time_cur = QuestionSet::getContestTime(cur);
        string time_other = QuestionSet::getContestTime(other);
        return time_cur < time_other;
    });
    QDateTime cur_time = QDateTime::currentDateTime();
    for (int i =0 ; i < cur_contest.size(); i++){
        string contest_time = QuestionSet::getContestTime(cur_contest[i]);
        QDateTime up = QDateTime::fromString(QString::fromStdString(contest_time), "yyyy-MM-dd HH:mm:ss");
        if (up.addSecs(300) < cur_time) continue;
        int p = -1;
        for (int j = 0; j < 6; j++){
            if (QString::fromStdString(cur_contest[i].substr(0, 2)) == contestName[j]){
                p = j; break;
            }
        }
        if (contests[p]->getDate() != "Ngày thi: --/--/----") continue;
        contests[p]->setDate("Ngày thi: " + up.toString("dd/MM/yyyy"));
        contests[p]->setTime("Giờ thi: " + up.toString("HH:mm"));
        contests[p]->setContestName(QString::fromStdString(cur_contest[i]));
    }
}

void UserGUI::setupPracticePage(){
    for (int i = 0; i < 3; i++){
        ContestWidget* myWidget = new ContestWidget(this, contestName[i], 1);
        ui->Frame03->layout()->addWidget(myWidget);
    }
    for (int i = 3; i < 6; i++){
        ContestWidget* myWidget = new ContestWidget(this, contestName[i], 1);
        ui->Frame04->layout()->addWidget(myWidget);
    }
}

void UserGUI::setupHistoryPage(){
    QWidget* contentWidget = new QWidget(this);
    historyPanel = new QVBoxLayout(contentWidget);
    historyPanel->setSpacing(15);
    historyPanel->setAlignment(Qt::AlignTop);
    vector<QuestionSet> history = QuestionSet::loadUserHistory(Account::getUsername());
    for (int i = 0; i < history.size(); i++){
        HistoryWidget* cur = new HistoryWidget(this, history[i]);
        cur->setMinimumHeight(70);
        historyPanel->insertWidget(0, cur);
        historyPanel->setAlignment(cur, Qt::AlignTop);
    }
    ui->scroll->setWidget(contentWidget);
    ui->historyPage->layout()->addWidget(ui->scroll);
}


