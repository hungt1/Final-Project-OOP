#pragma once

#include <QFrame>
#include "../Backend/QuestionSet.h"

namespace Ui {
class AdminHistoryWidget;
}

class AdminHistoryWidget : public QFrame
{
    Q_OBJECT

public:
    explicit AdminHistoryWidget(QWidget *parent = nullptr, string code = "");
    ~AdminHistoryWidget();

private slots:
    void on_view_clicked();

private:
    void setup(string);

private:
    Ui::AdminHistoryWidget *ui;
};

