#include "AdminHistoryWidget.h"
#include "ui_AdminHistoryWidget.h"
#include <QTableWidgetItem>
#include <QDebug>
#include <QDateTime>

AdminHistoryWidget::AdminHistoryWidget(QWidget *parent, string code) :
    QFrame(parent),
    ui(new Ui::AdminHistoryWidget)
{
    ui->setupUi(this);
    setup(code);
    ui->frame02->hide();
    string contest_time = QuestionSet::getContestTime(code);
    QDateTime cur_time = QDateTime::fromString(QString::fromStdString(contest_time), "yyyy-MM-dd HH:mm:ss");
    ui->date->setText("Ngày thi: " + cur_time.toString("MM-dd-yyyy"));
    ui->time->setText("Giờ thi: " + cur_time.toString("HH:mm"));
}

AdminHistoryWidget::~AdminHistoryWidget()
{
    delete ui;
}

void AdminHistoryWidget::setup(string code){
    ui->ID->setText("ID: " + QString::fromStdString(code));
    string url = "./data/history/contest/" + code + ".csv";
    vector<vector<string>> contents;
    vector<string> row;

    fstream file(url.c_str(), ios::in);
    if (file.is_open()){
        string line, word;
        while (getline(file, line)){
            row.clear();
            stringstream ss(line);
            while (getline(ss, word, ',')){
                row.push_back(word);
            }
            contents.push_back(row);
        }
        for (int i = 0; i < contents.size(); i++){
            ui->tableWidget->insertRow(i);
            for (int j = 0; j < contents[i].size(); j++){
                QString data = QString::fromStdString(contents[i][j]);
                QTableWidgetItem* item = new QTableWidgetItem(data);
                ui->tableWidget->setItem(i, j, item);
                ui->tableWidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

void AdminHistoryWidget::on_view_clicked(){
    if (ui->frame02->isHidden()){
        ui->frame02->show();
        ui->view->setText("Ẩn");
    }
    else{
        ui->frame02->hide();
        ui->view->setText("Xem");
    }
}

