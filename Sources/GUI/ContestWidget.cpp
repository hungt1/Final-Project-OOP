#include "ContestWidget.h"
#include "ui_ContestWidget.h"
#include "ContestGUI.h"

ContestWidget::ContestWidget(QWidget *parent, QString code, bool isPractice) :
    QFrame(parent), contestName(code), par(parent), isPractice(isPractice),
    ui(new Ui::ContestWidget)
{
    ui->setupUi(this);
    ui->icon->setIcon(QIcon("./icon/traffic/" + code.left(2) + ".png"));
    ui->title->setText("Loại bằng " + code.left(2));
}

ContestWidget::~ContestWidget(){
    delete ui;
}

void ContestWidget::on_btnJoin_clicked(){
    if (isPractice){
        int num = QInputDialog::getInt(this, "Số câu (20-30)", "Số câu: ");
        if (20 <= num && num <= 30){
            ContestGUI* contest = new ContestGUI(par, num, contestName);
            contest->show(); par->hide();
        }
    }
    else {
        if (ui->lblDate->text() == "Ngày thi: --/--/----"){
            QMessageBox::information(this, "Thông báo", "Kì thi không có sẵn");
        }
        else {
            QString date = ui->lblDate->text().right(10);
            QString time = ui->lblTime->text().right(5);
            QString dateTime = date + " " + time;
            QDateTime left = QDateTime::fromString(dateTime, "dd/MM/yyyy HH:mm");
            QDateTime right = left.addSecs(300);
            QDateTime cur_time = QDateTime::currentDateTime();
            if (left <= cur_time && cur_time <= right){
                QString pass = QInputDialog::getText(this, "", "Mật khẩu: ");
                if (!QuestionSet::checkPassword(contestName.toStdString(), pass.toStdString())){
                    QMessageBox::information(this, "Thông báo", "Mật khẩu sai");
                    return;
                }
                ContestGUI* contest = new ContestGUI(par, contestName);
                contest->show(); par->hide();
            }
            else {
                QMessageBox::information(this, "Thông báo", "Ngoài thời gian thi");
            }
        }
    }
}

QString ContestWidget::getDate(){
    return ui->lblDate->text();
}

void ContestWidget::setLabel(QString title){
    ui->title->setText(title);
}

void ContestWidget::setDate(QString date){
    ui->lblDate->setText(date);
}

void ContestWidget::setTime(QString time){
    ui->lblTime->setText(time);
}

void ContestWidget::setContestName(QString newName){
    contestName = newName;
}
