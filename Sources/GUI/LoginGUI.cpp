#include "LoginGUI.h"
#include "ui_LoginGUI.h"

LoginGUI::LoginGUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginGUI)
{
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setFocusPolicy(Qt::NoFocus);
    ui->setupUi(this);
    on_loginTab_clicked();
}

LoginGUI::~LoginGUI(){
    delete ui;
}

void LoginGUI::on_loginTab_clicked(){
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    ui->signupTab->setStyleSheet(defaultStyle);
    ui->loginTab->setStyleSheet(clickedStyle);
    ui->img->setIcon(QIcon("./icon/white/user.svg"));
    ui->label->setText("Đăng nhập");
}


void LoginGUI::on_signupTab_clicked(){
    ui->stackedWidget->setCurrentWidget(ui->signupPage);
    ui->loginTab->setStyleSheet(defaultStyle);
    ui->signupTab->setStyleSheet(clickedStyle);
    ui->img->setIcon(QIcon("./icon/white/user-plus.svg"));
    ui->label->setText("Đăng kí");
}


void LoginGUI::on_loginBtn_clicked(){
    string username = ui->lblUsername->text().toStdString();
    string password = ui->lblPassword->text().toStdString();
    Account* acc = LoginManager::findRole(username, password);
    if (acc == nullptr){
        ui->warning->setText("Tên đăng nhập hoặc mật khẩu sai");
        return;
    }
    else {
        if (Account::getRole() == 0){
            UserGUI* user = new UserGUI(this);
            this->hide();
            user->show();
        }
        else{
            AdminGUI* ad = new AdminGUI(this);
            this->hide();
            ad->show();
        }
    }
}


void LoginGUI::on_signupBtn_clicked(){
    string name = ui->lblName->text().toStdString();
    string email = ui->lblEmail->text().toStdString();
    string phoneNum = ui->lblPhoneNumber->text().toStdString();
    string username = ui->lblRUsername->text().toStdString();
    string password = ui->lblRPassword->text().toStdString();
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
        ui->lblRUsername->setText("");
        ui->lblRPassword->setText("");
    }
}

