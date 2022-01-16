#pragma once

#include <QDialog>
#include "QuestionWidget.h"
#include "../Backend/QuestionSet.h"

namespace Ui {
class ContestAdder;
}

class ContestAdder : public QDialog
{
    Q_OBJECT

public:
    explicit ContestAdder(QWidget *parent = nullptr);
    explicit ContestAdder(QWidget *parent, QuestionSet qs);
    ~ContestAdder();

private:
    const QString contestName[6] = {"A1", "A2", "A3", "A4", "B1", "B2"};
    QVBoxLayout* grid;
    QuestionSet qs;
    QVector<QuestionWidget*> added;

private:
    void setup();
    void load();
    void setViewOnly();

private slots:
    void on_quit_clicked();
    void on_comboBoxType_activated(int index);
    void on_saveAndQuit_clicked();

private:
    Ui::ContestAdder *ui;
};

