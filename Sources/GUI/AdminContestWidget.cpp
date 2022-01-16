#include "AdminContestWidget.h"
#include "ui_AdminContestWidget.h"
#include "ContestAdderGUI.h"
#include <QDateTime>

AdminContestWidget::AdminContestWidget(QWidget *parent, QuestionSet qs) :
    QFrame(parent), qs(qs), par(parent),
    ui(new Ui::AdminContestWidget)
{
    ui->setupUi(this);
    ui->ID->setText("ID: " + QString::fromStdString(qs.getType()));
    string contest_time = qs.getTime();
    QDateTime cur_time = QDateTime::fromString(QString::fromStdString(contest_time), "yyyy-MM-dd HH:mm:ss");
    ui->date->setText("Ngày thi: " + cur_time.toString("MM-dd-yyyy"));
    ui->time->setText("Giờ thi: " + cur_time.toString("HH:mm"));
    ui->num->setText("Số câu: " + QString::number(qs.getNumQuestion()));
}

AdminContestWidget::~AdminContestWidget(){
    delete ui;
}

void AdminContestWidget::on_view_clicked()
{
    ContestAdder* viewer = new ContestAdder(par, qs);
    viewer->show(); par->hide();
}

