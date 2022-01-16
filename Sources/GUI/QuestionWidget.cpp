#include "QuestionWidget.h"
#include "ui_QuestionWidget.h"
#include <QImageReader>

QuestionWidget::QuestionWidget(QWidget *parent, Question* quest, QString code) :
    QFrame(parent), question(quest),
    ui(new Ui::QuestionWidget)
{
    ui->setupUi(this);
    ui->frame02->hide();
    ui->label->setText("Câu hỏi bằng " + code);
    setup();
}

QuestionWidget::~QuestionWidget(){
    delete ui;
}

void QuestionWidget::on_btn_clicked(){
    if (ui->frame02->isHidden()){
        ui->frame02->show();
        ui->btn->setText("Ẩn");
    }
    else{
        ui->frame02->hide();
        ui->btn->setText("Chi tiết");
    }
}

void QuestionWidget::add(QVBoxLayout* grid, Question* q){
    int num = q->getNumChoice();
    for (int i = 0; i < num; i++){
        QLabel* lbl = new QLabel(this);
        lbl->setAlignment(Qt::AlignTop);
        lbl->setFont(QFont("LMHGUI", 14));
        lbl->setWordWrap(true);
        lbl->setText(QString::fromStdString(q->getChoice(i)));
        if (q->checkAnswer(i)){
            lbl->setStyleSheet(orangeText);
        }
        grid->addWidget(lbl); grid->setAlignment(lbl, Qt::AlignTop);
    }
}

void QuestionWidget::addTextQuestion(QVBoxLayout* grid, Question* q){
    add(grid, q);
}

void QuestionWidget::addPictureQuestion(QVBoxLayout* grid, Question* q){
    PictureQuestion* downcasting = (PictureQuestion*)q;
    QLabel* image = new QLabel(this);
    image->setScaledContents(true);
    image->setPixmap(QPixmap(QString::fromStdString(downcasting->_picURL)));
    QImageReader reader(QString::fromStdString(downcasting->_picURL));
    float ratio = 1.0  * reader.size().width() / reader.size().height();
    int h = 250; int w = h * ratio;
    image->setMaximumHeight(h); image->setMinimumHeight(h);
    image->setMaximumWidth(w); image->setMinimumWidth(w);
    grid->addWidget(image); grid->setAlignment(image, Qt::AlignLeft);
    add(grid, q);
}

void QuestionWidget::addRoadSignQuestion(QVBoxLayout* grid, Question* q){
    RoadSignQuestion* downcasting = (RoadSignQuestion*)q;
    QLabel* image = new QLabel(this);
    image->setScaledContents(true);
    image->setPixmap(QPixmap(QString::fromStdString(downcasting->_roadSignURL[0])));
    QImageReader reader(QString::fromStdString(downcasting->_roadSignURL[0]));
    float ratio = 1.0  * reader.size().width() / reader.size().height();
    int h = 200; int w = h * ratio;
    image->setMaximumHeight(h); image->setMinimumHeight(h);
    image->setMaximumWidth(w); image->setMinimumWidth(w);
    grid->addWidget(image); grid->setAlignment(image, Qt::AlignLeft);
    add(grid, q);
}

void QuestionWidget::setup(){
    ui->text->setText(QString::fromStdString(question->getQuestion()));
    ui->layout->setAlignment(Qt::AlignTop);
    if (question->getType() == 0){
        addTextQuestion(ui->layout, question);
    }
    else if (question->getType() == 1){
        addPictureQuestion(ui->layout, question);
    }
    else addRoadSignQuestion(ui->layout, question);
}

bool QuestionWidget::isChecked(){
    return ui->checkBox->isChecked();
}

void QuestionWidget::setViewOnly(){
    ui->checkBox->hide();
}
