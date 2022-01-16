#pragma once

#include <QFrame>
#include <QVBoxLayout>
#include "../Backend/Question.h"

namespace Ui {
class QuestionWidget;
}

class QuestionWidget : public QFrame
{
    Q_OBJECT

public:
    explicit QuestionWidget(QWidget *parent = nullptr, Question* quest = nullptr, QString code = "");
    ~QuestionWidget();

private slots:
    void on_btn_clicked();

private:
    Question* question;
    const QString greenText = "color: #51a325";
    const QString redText = "color: #d10000";
    const QString orangeText = "color: #e79a00";

private:
    void setup();
    void addTextQuestion(QVBoxLayout*, Question*);
    void addPictureQuestion(QVBoxLayout*, Question*);
    void addRoadSignQuestion(QVBoxLayout*, Question*);
    void add(QVBoxLayout*, Question*);

public:
    bool isChecked();
    void setViewOnly();

private:
    Ui::QuestionWidget *ui;
};

