#include "ContestAdderGUI.h"
#include "ui_ContestAdderGUI.h"
#include "../Backend/QuestionSet.h"
#include <QDebug>
#include "AdminGUI.h"

ContestAdder::ContestAdder(QWidget *parent) :
    QDialog(parent, Qt::CustomizeWindowHint),
    ui(new Ui::ContestAdder)
{
    ui->setupUi(this);
    setup();
}


ContestAdder::ContestAdder(QWidget *parent, QuestionSet qs) :
    QDialog(parent, Qt::CustomizeWindowHint), qs(qs),
    ui(new Ui::ContestAdder)
{
    ui->setupUi(this);
    load(); setViewOnly();
}

ContestAdder::~ContestAdder(){
    delete ui;
}

void ContestAdder::on_quit_clicked(){
    this->close();
    this->parentWidget()->show();
}

void ContestAdder::setViewOnly(){
    ui->label->setText("ID cuộc thi: " + QString::fromStdString(qs.getType()));
    ui->password->setText(QString::fromStdString(qs.getPassword()));
    ui->password->setReadOnly(true);
    string contest_time = qs.getTime();
    ui->dateTimeEdit->setDateTime(QDateTime::fromString(QString::fromStdString(contest_time), "yyyy-MM-dd HH:mm:ss"));
    ui->dateTimeEdit->setReadOnly(true);
    ui->frame->hide();
    ui->frame04->hide();
    ui->saveAndQuit->hide();
}

void ContestAdder::load(){
    QWidget* contentWidget = new QWidget(this);
    grid = new QVBoxLayout(contentWidget);
    grid->setSpacing(15);
    grid->setAlignment(Qt::AlignTop);
    int n = qs.getNumQuestion();
    for (int i = 0; i < n; i++){
        QuestionWidget* myWidget = new QuestionWidget(this, qs.getQuestion(i), QString::fromStdString(qs.getType().substr(0, 2)));
        grid->addWidget(myWidget);
        myWidget->setViewOnly();
        grid->setAlignment(myWidget, Qt::AlignTop);
    }
    ui->scroll->setWidget(contentWidget);
    ui->frame01->layout()->addWidget(ui->scroll);
}

void ContestAdder::setup(){
    QWidget* contentWidget = new QWidget(this);
    grid = new QVBoxLayout(contentWidget);
    grid->setSpacing(15);
    grid->setAlignment(Qt::AlignTop);
    qs.getAllQuestion(contestName[0].toStdString());
    int n = qs.getNumQuestion();
    for (int i = 0; i < n; i++){
        QuestionWidget* myWidget = new QuestionWidget(this, qs.getQuestion(i), contestName[0]);
        grid->addWidget(myWidget);
        grid->setAlignment(myWidget, Qt::AlignTop);
        added.push_back(myWidget);
    }
    ui->scroll->setWidget(contentWidget);
    ui->frame01->layout()->addWidget(ui->scroll);
}

void ContestAdder::on_comboBoxType_activated(int index){
    QLayoutItem* w;
    while (w = grid->layout()->takeAt(0)){
        if (w->widget() != nullptr){
            delete(w->widget());
        }
        delete w;
    }
    added.clear();
    qs.getAllQuestion(contestName[index].toStdString());
    int n = qs.getNumQuestion();
    for (int i = 0; i < n; i++){
        QuestionWidget* myWidget = new QuestionWidget(this, qs.getQuestion(i), contestName[index]);
        grid->addWidget(myWidget);
        grid->setAlignment(myWidget, Qt::AlignTop);
        added.push_back(myWidget);
    }
}

void ContestAdder::on_saveAndQuit_clicked(){
    QDateTime date = ui->dateTimeEdit->dateTime();
    string start = date.toString("yyyy-MM-dd hh:mm:ss").toStdString();
    string pass = ui->password->text().toStdString();
    int dur = ui->comboBoxDuration->currentText().toInt();
    int cnt = 0;
    for (int i = 0; i < added.size(); i++){
        if (cnt < 30 && added[i]->isChecked()){
            qs.setUserAnswer(i, 0);
            cnt++;
        }
        else qs.setUserAnswer(i, -1);
    }
    qs.saveContest(start, pass, dur);
    AdminGUI::reload();
    this->close();
    this->parentWidget()->show();
}

