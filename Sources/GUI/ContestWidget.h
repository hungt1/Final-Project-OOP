#pragma once

#include <QVBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QDebug>
#include <QInputDialog>

namespace Ui {
class ContestWidget;
}

class ContestWidget : public QFrame
{
    Q_OBJECT

private:
    QWidget* par;
    QString contestName;
    bool isPractice;

public:
    explicit ContestWidget(QWidget *parent = nullptr, QString name = "", bool isPractice = false);
    ~ContestWidget();

private slots:
    void on_btnJoin_clicked();

public:
    QString getDate();
    void setLabel(QString);
    void setDate(QString);
    void setTime(QString);
    void setContestName(QString);

private:
    Ui::ContestWidget *ui;
};

