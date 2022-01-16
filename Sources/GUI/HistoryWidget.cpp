#include "HistoryWidget.h"
#include "ui_HistoryWidget.h"

HistoryWidget::HistoryWidget(QWidget *parent, QuestionSet cur) :
    QFrame(parent), par(parent), history(cur),
    ui(new Ui::HistoryWidget)
{
    ui->setupUi(this);
    string code = cur.getType().substr(0, 4);
    string _type = code.substr(0, 2);
    if (code.back() == '0'){
        ui->label->setText("Thi thử bằng " + QString::fromStdString(_type));
    }
    else{
        ui->label->setText("Kì thi bằng " + QString::fromStdString(_type));
    }
    ui->lblScore->setText("Điểm số: " + QString::number(cur.getPoint()) + "/" + QString::number(cur.getNumQuestion()));
}

HistoryWidget::~HistoryWidget()
{
    delete ui;
}

void HistoryWidget::on_view_clicked()
{
    HistoryGUI* cur = new HistoryGUI(par, history);
    cur->show(); par->hide();
}

