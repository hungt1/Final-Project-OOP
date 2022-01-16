#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QScrollBar>
#include <QMessageBox>
#include "../Backend/LoginManager.h"
#include "AdminGUI.h"
#include "UserGUI.h"
#include "QuestionAdderGUI.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginGUI; }
QT_END_NAMESPACE

class LoginGUI : public QMainWindow
{
    Q_OBJECT

public:
    LoginGUI(QWidget *parent = nullptr);
    ~LoginGUI();

private slots:
    void on_loginTab_clicked();
    void on_signupTab_clicked();
    void on_loginBtn_clicked();

    void on_signupBtn_clicked();

private:
    const QString defaultStyle = "color: #aaaaff;";
    const QString clickedStyle = "border: none; border-bottom: 2px solid #7446ff; color: #7446ff;";

private:
    Ui::LoginGUI *ui;
};
