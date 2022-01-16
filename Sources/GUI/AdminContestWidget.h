#pragma once

#include <QFrame>
#include <QFormLayout>
#include "../Backend/QuestionSet.h"

namespace Ui {
class AdminContestWidget;
}

class AdminContestWidget : public QFrame
{
    Q_OBJECT

private:
    QWidget* par;
    QWidget* content;
    QuestionSet qs;

public:
    explicit AdminContestWidget(QWidget *parent = nullptr, QuestionSet qs = 0);
    ~AdminContestWidget();

private slots:
    void on_view_clicked();

private:
    Ui::AdminContestWidget *ui;
};
