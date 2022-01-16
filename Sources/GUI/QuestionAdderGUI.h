#pragma once

#include <QDialog>
#include <QFormLayout>
#include <QRadioButton>
#include <QFileDialog>
#include <QTextEdit>

namespace Ui {
class QuestionAdder;
}

class QuestionAdder : public QDialog
{
    Q_OBJECT

private:
    QFormLayout* grid;
    int num;
    QVector<QRadioButton*> btns;
    QVector<QTextEdit*> txts;
    QString url;

private:
    void setup();

public:
    explicit QuestionAdder(QWidget *parent = nullptr);
    ~QuestionAdder();

private slots:
    void on_add_clicked();
    void on_quit_clicked();
    void on_comboBox_activated(int index);
    void on_image_clicked();
    void on_saveAndQuit_clicked();

private:
    Ui::QuestionAdder *ui;
};

