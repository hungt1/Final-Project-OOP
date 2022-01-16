#include "ContestGUI.h"
#include "ui_ContestGUI.h"
#include "../Backend/Account.h"
#include <QImageReader>

ShowQuestionWidget::ShowQuestionWidget(){
    for (int i = 0; i < N; i++){
        QLabel* lbl = new QLabel;
        QRadioButton* btn = new QRadioButton;

        lbl->setAlignment(Qt::AlignTop);
        lbl->setFont(QFont("LMHGUI", 14));
        lbl->setWordWrap(true);
        lbl->hide();

        btn->setMinimumHeight(25);
        btn->hide();

        btns.push_back(btn);
        lbls.push_back(lbl);
    }
    hang = new QRadioButton;
    hang->hide();
}

ShowQuestionWidget::~ShowQuestionWidget(){
    for (int i = 0; i < N; i++){
        delete btns[i];
        delete lbls[i];
    }
    for (int i = 0; i < num; i++){
        delete shortcuts[i];
    }
    delete hang;
}

void ShowQuestionWidget::createButton(int num){
    this->num = num;
    for (int i = 0; i < num; i++){
        QPushButton* btn = new QPushButton;
        btn->setMinimumHeight(35);
        btn->setFlat(true);
        btn->setText("Câu " + QString::number(i + 1));
        btn->setFont(QFont("Sitka Text", 14));
        shortcuts.push_back(btn);
    }
}

ContestGUI::ContestGUI(QWidget *parent, int num, QString type, int duration):
    QDialog(parent, Qt::CustomizeWindowHint),
    ui(new Ui::ContestGUI), current(QuestionSet(num, type.toStdString()))
{
    ui->setupUi(this);
    countDown = 60 * duration + 1;
    setup();
    handleEventClicked();
}

ContestGUI::ContestGUI(QWidget *parent, QString type):
    QDialog(parent, Qt::CustomizeWindowHint),
    ui(new Ui::ContestGUI), current(QuestionSet(type.toStdString()))
{
    ui->setupUi(this);
    countDown = current.getDuration() * 60 + 1;
    setup();
    handleEventClicked();
}

void ContestGUI::setup(){
    ui->lblType->setText("Hạng " + QString::fromStdString(current.getType().substr(0, 2)));
    ui->lblName->setText("Thí sinh: " + QString::fromStdString(Account::getName()));
    ui->lblUsername->setText("Tài khoản: " + QString::fromStdString(Account::getUsername()));
    for (int i = 0; i < qwg.N; i++){
        ui->opt->addRow(qwg.btns[i], qwg.lbls[i]);
    }
    ui->opt->addRow(qwg.hang, qwg.hang);
    idx = 0;
    showQuestion(current.getQuestion(0));
    ui->btnPrev->hide();
    qwg.createButton(current.getNumQuestion());
    for (int i = 0; i < qwg.num; i++){
        ui->grid->addWidget(qwg.shortcuts[i], i / 3, i % 3);
    }
    myTimer = new QTimer(this);
    connect(myTimer, SIGNAL(timeout()), this, SLOT(showTime()));
    myTimer->start(1000);
}

ContestGUI::~ContestGUI()
{
    delete ui;
}

void ContestGUI::showQuestion(Question* cur){
    if (cur == nullptr) return;
    int num = cur->getNumChoice();
    ui->text->setText("Câu " + QString::number(idx + 1) + ":\n" + QString::fromStdString(cur->getQuestion()));
    int type = cur->getType();
    if (type == 0){
        ui->text->setMaximumHeight(150);
        ui->image->hide();
    }
    else {
        ui->text->setMaximumHeight(120);
        ui->image->show();
        if (type == 1){
            PictureQuestion* downcasting = (PictureQuestion*)cur;
            ui->image->setPixmap(QPixmap(QString::fromStdString(downcasting->_picURL)));
            QImageReader reader(QString::fromStdString(downcasting->_picURL));
            float ratio = 1.0  * reader.size().width() / reader.size().height();
            int h = 250; int w = h * ratio;
            ui->image->setMaximumHeight(h); ui->image->setMinimumHeight(h);
            ui->image->setMaximumWidth(w); ui->image->setMinimumWidth(w);
        }
        else {
            RoadSignQuestion* downcasting = (RoadSignQuestion*)cur;
            ui->image->setPixmap(QPixmap(QString::fromStdString(downcasting->_roadSignURL[0])));
            QImageReader reader(QString::fromStdString(downcasting->_roadSignURL[0]));
            float ratio = 1.0  * reader.size().width() / reader.size().height();
            int h = 200; int w = h * ratio;
            ui->image->setMaximumHeight(h); ui->image->setMinimumHeight(h);
            ui->image->setMaximumWidth(w); ui->image->setMinimumWidth(w);
        }
    }
    qwg.hang->setChecked(true);
    for (int i = 0; i < num; i++){
        qwg.btns[i]->show();
        qwg.lbls[i]->setText(QString::fromStdString(cur->getChoice(i)));
        qwg.lbls[i]->show();
    }
    if (cur->fakeUserAnswer() != -1) qwg.btns[cur->fakeUserAnswer()]->setChecked(true);
    for (int i = num; i < qwg.N; i++){
        qwg.btns[i]->hide(); qwg.lbls[i]->hide();
    }
}

void ContestGUI::updateAnswer(){
    Question* cur = current.getQuestion(idx);
    if (cur == nullptr) return;
    int num = cur->getNumChoice();
    for (int i = 0; i < num; i++){
        if (qwg.btns[i]->isChecked()){
            current.setUserAnswer(idx, i);
            break;
        }
    }
}

void ContestGUI::handleEventClicked(){
    for (int i = 0; i < qwg.num; i++){
        connect(qwg.shortcuts[i], &QPushButton::clicked, [this, i]{
            this->updateAnswer();
            idx = i;
            this->showQuestion(current.getQuestion(idx));
            ui->btnNxt->show(); ui->btnPrev->show();
            if (idx == 0) ui->btnPrev->hide();
            if (idx + 1 == current.getNumQuestion()) ui->btnNxt->hide();
        });
    }
    for (int i = 0; i < qwg.N; i++){
        connect(qwg.btns[i], &QPushButton::clicked, [this, i]{
            QString style = "background-color: #70c6ff; border-radius: 10px; border-style: outset; border-width: 2px; border-color: #3eff95;";
            qwg.shortcuts[idx]->setStyleSheet(style);
        });
    }
}

void ContestGUI::on_btnSubmit_clicked()
{
    myTimer->stop();
    updateAnswer();
    QString score = QString::number(current.getPoint()) + "/" +  QString::number(current.getNumQuestion());
    QMessageBox::information(this, "Thông báo", "Bạn đã hoàn thành bài thi với số điểm " + score);
    current.saveHistory(Account::getUsername(), Account::getName());
    HistoryWidget* his = new HistoryWidget(this->parentWidget(), current);
    his->setMinimumHeight(70);
    UserGUI::historyPanel->insertWidget(0, his);
    this->parentWidget()->show();
    this->close();
}


void ContestGUI::on_btnNxt_clicked()
{
    updateAnswer();
    this->idx++;
    ui->btnPrev->show();
    this->showQuestion(current.getQuestion(idx));
    if (idx + 1 == current.getNumQuestion()) ui->btnNxt->hide();
}


void ContestGUI::on_btnPrev_clicked()
{
    updateAnswer();
    this->idx--;
    ui->btnNxt->show();
    this->showQuestion(current.getQuestion(idx));
    if (idx == 0) ui->btnPrev->hide();
}

void ContestGUI::showTime(){
    countDown--;
    ui->progressBar->setValue((1500 - countDown) / 1500);
    QTime cur(0, countDown / 60, countDown % 60);
    ui->lblTime->setText(cur.toString("mm:ss"));
    if (countDown == 0){
        this->on_btnSubmit_clicked();
    }
}
