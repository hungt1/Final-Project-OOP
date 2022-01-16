#pragma once

#include <QFrame>
#include "../Backend/QuestionSet.h"
#include "HistoryGUI.h"

namespace Ui {
class HistoryWidget;
}

class HistoryWidget : public QFrame
{
    Q_OBJECT

private:
    QWidget* par;
    QuestionSet history;

public:
    explicit HistoryWidget(QWidget *parent = nullptr, QuestionSet cur = 0);
    ~HistoryWidget();

private slots:
    void on_view_clicked();

private:
    Ui::HistoryWidget *ui;
};
