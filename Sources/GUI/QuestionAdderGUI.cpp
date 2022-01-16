#include "QuestionAdderGUI.h"
#include "ui_QuestionAdderGUI.h"
#include "../Backend/Question.h"
#include "AdminGUI.h"
#include <QMessageBox>

QuestionAdder::QuestionAdder(QWidget *parent) :
    QDialog(parent, Qt::CustomizeWindowHint),
    ui(new Ui::QuestionAdder)
{
    ui->setupUi(this);
    setup(); num = 0;
    ui->image->hide();
    ui->dir->hide();
}

QuestionAdder::~QuestionAdder(){
    delete ui;
}

void QuestionAdder::setup(){
    QWidget* content = new QWidget(this);
    grid = new QFormLayout(content);
    grid->setSpacing(10);
    ui->scroll->setWidget(content);
    ui->frame01->layout()->addWidget(ui->scroll);
}

void QuestionAdder::on_add_clicked(){
    QTextEdit* txt = new QTextEdit(this);
    QRadioButton* btn = new QRadioButton(this);

    btns.push_back(btn); txts.push_back(txt);

    txt->setMaximumHeight(50);

    btn->setMinimumHeight(25);
    grid->addRow(btn, txt);
    grid->setAlignment(btn, Qt::AlignTop);
    grid->setAlignment(txt, Qt::AlignTop);

    num++;
    if (num == 5) ui->add->hide();
}

void QuestionAdder::on_image_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open file"), "./", "Image file (*.jpg *.png)");
    QFileInfo cur(path);
    ui->dir->setText(cur.fileName());
    QDir dir("./");
    url = dir.relativeFilePath(path);
}

void QuestionAdder::on_quit_clicked(){
    this->close();
    this->parentWidget()->show();
}


void QuestionAdder::on_comboBox_activated(int index){
    if (index == 0){
        ui->image->hide();
        ui->dir->hide();
    }
    else {
        ui->image->show();
        ui->dir->show();
    }
}

void QuestionAdder::on_saveAndQuit_clicked(){
    if (btns.size() == 0){
        QMessageBox::information(this, "Thông báo", "Vui lòng thêm câu trả lời");
        return;
    }
    int ans = -1;
    for (int i = 0; i < btns.size(); i++){
        if (btns[i]->isChecked()){
            ans = i;
            break;
        }
    }
    if (ans == -1){
        QMessageBox::information(this, "Thông báo", "Vui lòng chọn đáp án");
        return;
    }
    int t = ui->comboBox->currentIndex();
    string type = ui->comboBoxType->currentText().toStdString();
    string question = ui->textEdit->toPlainText().toStdString();
    vector<string> choices;
    for (int i = 0; i < txts.size(); i++){
        string cur = txts[i]->toPlainText().toStdString();
        choices.push_back(cur);
    }
    if (t == 0){
        TextQuestion::addQuestion(type, question, choices, ans);
    }
    else if (t == 1){
        PictureQuestion::addQuestion(type, question, choices, ans, url.toStdString());
    }
    else {
        vector<string> urls; urls.push_back(url.toStdString());
        RoadSignQuestion::addQuestion(type, question, choices, ans, urls);
    }
    this->close();
    this->parentWidget()->show();
}


