#include "AdminGUI.h"
#include "ui_AdminGUI.h"
#include "../Backend/QuestionSet.h"
#include "../Backend/LoginManager.h"
#include <QMessageBox>

AdminGUI::AdminGUI(QWidget *parent) :
    QDialog(parent, Qt::CustomizeWindowHint),
    ui(new Ui::AdminGUI)
{
    ui->setupUi(this);
    current_panel = this;
    on_btnContest_clicked();
    setupContestPage();
    setupHistoryPage();
}

AdminGUI::~AdminGUI(){
    delete ui;
}

void AdminGUI::on_btnContest_clicked(){
    ui->label->setText("Các cuộc thi");
    ui->stackedWidget->setCurrentWidget(ui->contestPage);
}

void AdminGUI::on_btnHistory_clicked(){
    ui->label->setText("Lịch sử thi");
    ui->stackedWidget->setCurrentWidget(ui->historyPage);
}

void AdminGUI::on_pushButton_clicked(){
    ui->label->setText("Thêm thí sinh");
    ui->stackedWidget->setCurrentWidget(ui->registrationPage);
}



void AdminGUI::setupContestPage(){
    QWidget* contentWidget = new QWidget(this);
    contestsPanel = new QVBoxLayout(contentWidget);
    contestsPanel->setSpacing(15);
    contestsPanel->setAlignment(Qt::AlignTop);
    vector<string> contests = QuestionSet::getUpcomingContest();
    for (int i = 0 ; i < contests.size(); i++){
        string contest_time = QuestionSet::getContestTime(contests[i]);
        QDateTime up = QDateTime::fromString(QString::fromStdString(contest_time), "yyyy-MM-dd HH:mm:ss");
        QuestionSet cur_contest(contests[i]);
        AdminContestWidget* myWidget = new AdminContestWidget(this, cur_contest);
        contestsPanel->insertWidget(0, myWidget);
        contestsPanel->setAlignment(myWidget, Qt::AlignTop);
    }
    ui->scroll02->setWidget(contentWidget);
    //ui->contestPage->layout()->addWidget(ui->scroll02);
}

void AdminGUI::setupHistoryPage(){
    QWidget* contentWidget = new QWidget(this);
    QVBoxLayout* grid = new QVBoxLayout(contentWidget);
    grid->setSpacing(15);
    grid->setAlignment(Qt::AlignTop);
    vector<string> contests = QuestionSet::getUpcomingContest();
    for (int i = 0 ; i < contests.size(); i++){
        AdminHistoryWidget* myWidget = new AdminHistoryWidget(this, contests[i]);
        grid->insertWidget(0, myWidget);
        grid->setAlignment(myWidget, Qt::AlignTop);
    }
    ui->scroll01->setWidget(contentWidget);
}

void AdminGUI::on_btnShowMinimize_clicked(){
    this->showMinimized();
}

void AdminGUI::on_btnChangeSize_clicked(){
    if (this->isMaximized()){
        this->showNormal();
        ui->btnChangeSize->setIcon(QIcon("./icon/light-purple/maximize-2.svg"));
    }
    else {
        this->showMaximized();
        ui->btnChangeSize->setIcon(QIcon("./icon/light-purple/minimize-2.svg"));
    }
}

void AdminGUI::on_btnExit_clicked(){
    this->parentWidget()->show(); this->close();
}

void AdminGUI::on_addQuestion_clicked(){
    QuestionAdder* adder = new QuestionAdder(this);
    adder->show(); this->hide();
}

void AdminGUI::on_addContest_clicked(){
    ContestAdder* adder = new ContestAdder(this);
    adder->show(); this->hide();
}

void AdminGUI::reload(){
    QLayoutItem* w;
    while (w = contestsPanel->layout()->takeAt(0)){
        if (w->widget() != nullptr){
            delete(w->widget());
        }
        delete w;
    }
    vector<string> contests = QuestionSet::getUpcomingContest();
    for (int i = 0 ; i < contests.size(); i++){
        string contest_time = QuestionSet::getContestTime(contests[i]);
        QDateTime up = QDateTime::fromString(QString::fromStdString(contest_time), "yyyy-MM-dd HH:mm:ss");
        QuestionSet cur_contest(contests[i]);
        AdminContestWidget* myWidget = new AdminContestWidget(current_panel, cur_contest);
        contestsPanel->insertWidget(0, myWidget);
        contestsPanel->setAlignment(myWidget, Qt::AlignTop);
    }
}

void AdminGUI::on_signupBtn_clicked(){
    string name = ui->lblName->text().toStdString();
    string email = ui->lblEmail->text().toStdString();
    string phoneNum = ui->lblPhoneNumber->text().toStdString();
    string username = ui->lblUsername02->text().toStdString();
    string password = ui->lblPassword->text().toStdString();
    int status = LoginManager::registerUser(username, password, name, email, phoneNum);
    if (status == 1){
        QMessageBox::information(this, "Thông báo", "Tên tài khoản chỉ gồm các kí tự in thường, in hoa và số");
    }
    else if (status == 2){
        QMessageBox::information(this, "Thông báo", "Mật khẩu phải tối thiểu 8 kí tự. Gồm các kí tự in thường, in hoa, số và các kí tự đặc biệt");
    }
    else if (status == 3){
        QMessageBox::information(this, "Thông báo", "Địa chỉ email không hợp lệ");
    }
    else if (status == 4){
        QMessageBox::information(this, "Thông báo", "Số điện thoại không hợp lệ");
    }
    else if (status == 5){
        QMessageBox::information(this, "Thông báo", "Tên tài khoản đã tồn tại");
    }
    else {
        QMessageBox::information(this, "Thông báo", "Bạn đã đăng kí thành công");
        ui->lblName->setText("");
        ui->lblEmail->setText("");
        ui->lblPhoneNumber->setText("");
        ui->lblUsername02->setText("");
        ui->lblPassword->setText("");
    }
}

