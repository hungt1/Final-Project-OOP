#pragma once
#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QRadioButton>
#include <QVector>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QTimer>
#include <QTime>
#include "../Backend/QuestionSet.h"
#include "UserGUI.h"

class ShowQuestionWidget{
public:
    const int N = 5;
    int num;
    QVector<QRadioButton*> btns;
    QVector<QLabel*> lbls;
    QRadioButton* hang;
    QVector<QPushButton*> shortcuts;

public:
    ShowQuestionWidget();
    ~ShowQuestionWidget();

public:
    void createButton(int);
};

namespace Ui {
class ContestGUI;

}

class ContestGUI : public QDialog
{
    Q_OBJECT

private:
    int idx;
    QuestionSet current;
    ShowQuestionWidget qwg;
    QTimer* myTimer;
    int countDown;

private:
    void showQuestion(Question*);
    void updateAnswer();
    void handleEventClicked();
    void setup();

public:
    explicit ContestGUI(QWidget *parent = nullptr, int num = 25, QString type = "A1", int duration = 25);
    explicit ContestGUI(QWidget *parent, QString type);
    ~ContestGUI();

private slots:
    void on_btnSubmit_clicked();
    void on_btnPrev_clicked();
    void on_btnNxt_clicked();
    void showTime();

private:
    Ui::ContestGUI *ui;
};
