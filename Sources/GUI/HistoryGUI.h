#pragma once

#include <QDialog>
#include <QGridLayout>
#include <QTextEdit>
#include "../Backend/QuestionSet.h"


namespace Ui {
class HistoryGUI;
}

class HistoryGUI : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryGUI(QWidget *parent = nullptr, QuestionSet cur = 0);
    ~HistoryGUI();

private:
    const QString greenStyle = "background-color: #8fffa9; border-radius: 15px; border-style: solid; \
                                border-width: 3px;border-color: #51a325; color: #156a0e; font: 15pt \"LMHGUI\";";
    const QString redStyle = "background-color: #ff8f8b; border-radius: 15px; border-style: solid; \
                              border-width: 3px;border-color: #d10000; color: #d10000; font: 15pt \"LMHGUI\";";
    const QString orangeStyle = "background-color: #ffd058; border-radius: 15px; border-style: solid; \
                                 border-width: 3px;border-color: #e79a00; color: #e79a00; font: 15pt \"LMHGUI\";";
    const QString greenText = "color: #51a325";
    const QString redText = "color: #d10000";
    const QString orangeText = "color: #e79a00";

    QuestionSet current;

private slots:
    void on_btnExit_clicked();
    void on_view_clicked();

private:
    void showSummary();
    void showDetail();
    void addTextQuestion(QGridLayout*, Question*, int);
    void addPictureQuestion(QGridLayout*, Question*, int);
    void addRoadSignQuestion(QGridLayout*, Question*, int);
    void add(QGridLayout*, Question*);

private:
    Ui::HistoryGUI *ui;
};
