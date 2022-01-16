#pragma once

#include <QDialog>
#include <QGridLayout>
#include <QVector>
#include "ContestWidget.h"
#include "HistoryWidget.h"

namespace Ui {
class UserGUI;
}

class UserGUI : public QDialog
{
    Q_OBJECT

private:
   const QString contestName[6] = {"A1", "A2", "A3", "A4", "B1", "B2"};
   QString name, username;
   QVector<ContestWidget*> contests;
   //ContestWidget* wtf;

public:
   static QVBoxLayout* historyPanel;

public:
    explicit UserGUI(QWidget *parent = nullptr);
    ~UserGUI();

private slots:
    void on_btnExit_clicked();
    void on_btnShowMinimize_clicked();
    void on_btnChangeSize_clicked();
    void on_btnHome_clicked();
    void on_btnContest_clicked();
    void on_btnPractice_clicked();
    void on_btnHistory_clicked();

private:
    void setupContestPage();
    void setupPracticePage();
    void setupHistoryPage();

private:
    Ui::UserGUI *ui;
};

