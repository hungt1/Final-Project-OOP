#include "HistoryGUI.h"
#include "ui_HistoryGUI.h"
#include <QImageReader>

HistoryGUI::HistoryGUI(QWidget *parent, QuestionSet history) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::HistoryGUI), current(history)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setAttribute(Qt::WA_TranslucentBackground);
    QString type = QString::fromStdString(current.getType().substr(0, 4));
    if (type[3] == '0'){
        ui->label->setText("Kết quả thi thử " + type.left(2));
    }
    else {
        ui->label->setText("Kết quả kì thi " + type.left(2));
    }
    showSummary();
    showDetail();
    on_view_clicked();
}

HistoryGUI::~HistoryGUI(){
    delete ui;
}



void HistoryGUI::on_btnExit_clicked(){
    this->parentWidget()->show();
    this->close();
}

void HistoryGUI::on_view_clicked(){
    if (ui->frame02->isHidden()){
        ui->view->setIcon(QIcon("./icon/white/minimize.svg"));
        ui->frame02->show();
    }
    else {
        ui->view->setIcon(QIcon("./icon/white/maximize.svg"));
        ui->frame02->hide();
    }
}

void HistoryGUI::add(QGridLayout* grid, Question* q){
    int num = q->getNumChoice();
    int ans = q->fakeUserAnswer();
    for (int i = 0; i < num; i++){
        QLabel* lbl = new QLabel(this);
        lbl->setAlignment(Qt::AlignTop);
        lbl->setFont(QFont("LMHGUI", 14));
        lbl->setWordWrap(true);
        lbl->setText(QString::fromStdString(q->getChoice(i)));
        if (i == ans){
            if (q->checkAnswer()){
                lbl->setStyleSheet(greenText);
            }
            else {
                lbl->setStyleSheet(redText);
            }
        }
        else if (q->checkAnswer(i)){
            if (ans != -1) lbl->setStyleSheet(greenText);
            else lbl->setStyleSheet(orangeText);
        }
        grid->addWidget(lbl);
    }
}

void HistoryGUI::addTextQuestion(QGridLayout* grid, Question* q, int idx){
    QTextEdit* txt = new QTextEdit(this);
    txt->setText("Câu " + QString::number(idx + 1) + ":\n" + QString::fromStdString(q->getQuestion()));
    txt->setMaximumHeight(150);
    grid->addWidget(txt);
    add(grid, q);
}

void HistoryGUI::addPictureQuestion(QGridLayout* grid, Question* q, int idx){
    QTextEdit* txt = new QTextEdit(this);
    txt->setText("Câu " + QString::number(idx + 1) + ":\n" + QString::fromStdString(q->getQuestion()));
    txt->setMaximumHeight(120);
    grid->addWidget(txt);
    PictureQuestion* downcasting = (PictureQuestion*)q;
    QLabel* image = new QLabel(this);
    image->setScaledContents(true);
    image->setPixmap(QPixmap(QString::fromStdString(downcasting->_picURL)));
    QImageReader reader(QString::fromStdString(downcasting->_picURL));
    float ratio = 1.0  * reader.size().width() / reader.size().height();
    int h = 250; int w = h * ratio;
    image->setMaximumHeight(h); image->setMinimumHeight(h);
    image->setMaximumWidth(w); image->setMinimumWidth(w);
    grid->addWidget(image);
    add(grid, q);
}

void HistoryGUI::addRoadSignQuestion(QGridLayout* grid, Question* q, int idx){
    QTextEdit* txt = new QTextEdit(this);
    txt->setText("Câu " + QString::number(idx + 1) + ":\n" + QString::fromStdString(q->getQuestion()));
    txt->setMaximumHeight(120);
    grid->addWidget(txt);
    RoadSignQuestion* downcasting = (RoadSignQuestion*)q;
    QLabel* image = new QLabel(this);
    image->setScaledContents(true);
    image->setPixmap(QPixmap(QString::fromStdString(downcasting->_roadSignURL[0])));
    QImageReader reader(QString::fromStdString(downcasting->_roadSignURL[0]));
    float ratio = 1.0  * reader.size().width() / reader.size().height();
    int h = 200; int w = h * ratio;
    image->setMaximumHeight(h); image->setMinimumHeight(h);
    image->setMaximumWidth(w); image->setMinimumWidth(w);
    grid->addWidget(image);
    add(grid, q);
}

void HistoryGUI::showSummary(){
    QWidget* contentWidget = new QWidget(this);
    QGridLayout* grid = new QGridLayout(contentWidget);
    grid->setSpacing(10);
    int x = current.getPoint();
    int checked = current.getChecked();
    int n = current.getNumQuestion();
    ui->score->setText("Điểm: " + QString::number(x) + "/" + QString::number(n));
    if (x * 4 < n * 3){
        ui->status->setText("Trượt");
        ui->status->setStyleSheet(redStyle);
        ui->score->setStyleSheet(redText);
    }
    else {
        ui->status->setText("Đạt");
        ui->status->setStyleSheet(greenStyle);
        ui->score->setStyleSheet(greenText);
    }
    ui->sum->setText("  " + QString::number(n));
    ui->right->setText("  " + QString::number(x));
    ui->wrong->setText("  " + QString::number(checked - x));
    ui->unfinished->setText(" " + QString::number(n - checked));
    grid->setAlignment(Qt::AlignTop);
    for (int i = 0; i < n; i++){
        QPushButton* btn = new QPushButton(this);
        btn->setMinimumHeight(60);
        int x = current.getStatus(i);
        if (x == 1) btn->setStyleSheet(greenStyle);
        else if (x == 0) btn->setStyleSheet(redStyle);
        else btn->setStyleSheet(orangeStyle);
        btn->setText("Câu " + QString::number(i + 1));
        grid->addWidget(btn, i / 3, i % 3);
        grid->setAlignment(btn, Qt::AlignTop);
    }
    ui->scroll->setWidget(contentWidget);
    ui->frame07->layout()->addWidget(ui->scroll);
}

void HistoryGUI::showDetail(){
    QWidget* contentWidget = new QWidget(this);
    QGridLayout* grid = new QGridLayout(contentWidget);
    grid->setSpacing(10);
    int n = current.getNumQuestion();
    for (int i = 0; i < n; i++){
        Question* cur = current.getQuestion(i);
        if (cur->getType() == 0) addTextQuestion(grid, cur, i);
        else if (cur->getType() == 1) addPictureQuestion(grid, cur, i);
        else addRoadSignQuestion(grid, cur, i);
    }
    ui->scroll01->setWidget(contentWidget);
    ui->frame08->layout()->addWidget(ui->scroll01);
}
