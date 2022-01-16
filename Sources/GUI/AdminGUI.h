#pragma once

#include <QDialog>
#include <QGridLayout>
#include "QuestionWidget.h"
#include "QuestionAdderGUI.h"
#include "AdminContestWidget.h"
#include "ContestAdderGUI.h"
#include "AdminHistoryWidget.h"

namespace Ui {
class AdminGUI;
}

class AdminGUI : public QDialog
{
    Q_OBJECT

public:
    explicit AdminGUI(QWidget *parent = nullptr);
    ~AdminGUI();

private slots:
    void on_btnShowMinimize_clicked();
    void on_btnChangeSize_clicked();
    void on_btnExit_clicked();
    void on_addQuestion_clicked();
    void on_btnContest_clicked();
    void on_addContest_clicked();
    void on_btnHistory_clicked();

    void on_pushButton_clicked();

    void on_signupBtn_clicked();

private:
    void setupContestPage();
    void setupHistoryPage();

public:
    static QVBoxLayout* contestsPanel;
    static QVBoxLayout* problemSetPanel;
    static QWidget* current_panel;
    static void reload();

private:
    Ui::AdminGUI *ui;
};
