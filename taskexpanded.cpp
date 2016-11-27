#include <QPainter>
#include <QPaintEvent>

#include "taskexpanded.h"
#include "ui_taskexpanded.h"

ExpandedTask::ExpandedTask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskExpanded)
{
    ui->setupUi(this);
}

ExpandedTask::ExpandedTask(QWidget *parent, Task* newContent, int origin_x, int origin_y) :
    QWidget(parent),
    ui(new Ui::TaskExpanded)
{
    string statusText;
    QPalette tempPalette;
    this->content = newContent;
    ui->setupUi(this);
    this->parent = parent;

    ui->labelName->setText(QString::fromStdString(content->getName()));
    tempPalette = ui->labelName->palette();
    tempPalette.setColor(ui->labelName->backgroundRole(), content->getCategory()->getColour());
    ui->labelName->setPalette(tempPalette);

    tempPalette = ui->buttonComplete->palette();
    tempPalette.setColor(ui->buttonComplete->backgroundRole(), Qt::white);
    ui->buttonComplete->setPalette(tempPalette);

    tempPalette = ui->buttonDelay->palette();
    tempPalette.setColor(ui->buttonDelay->backgroundRole(), Qt::white);
    ui->buttonDelay->setPalette(tempPalette);

    if(content->getComplete()){
        statusText = "Complete";
    }
    else{
        statusText = chrono::system_clock::to_time_t(chrono::system_clock::now()) > content->task_time.end ? "Late" : "Pending";
    }
    ui->labelStatus->setText(QString::fromStdString("Status: " + statusText));
    tempPalette = ui->labelStatus->palette();
    tempPalette.setColor(ui->labelStatus->backgroundRole(), content->getCategory()->getColour());
    ui->labelStatus->setPalette(tempPalette);

    ui->labelTime->setText(createString());
    tempPalette = ui->labelTime->palette();
    tempPalette.setColor(ui->labelTime->backgroundRole(), content->getCategory()->getColour());
    ui->labelTime->setPalette(tempPalette);

    setGeometry(origin_x, origin_y, this->width(), this->height());
}

ExpandedTask::~ExpandedTask()
{
    delete ui;
}

void ExpandedTask::update(){
    ui->buttonComplete->setEnabled(content->getComplete());
}

void ExpandedTask::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(event->rect(), content->getCategory()->getColour());
}

void ExpandedTask::leaveEvent(QEvent* event){
    this->close();
    QWidget::leaveEvent(event);
}

QString ExpandedTask::createString(){
    string changedName;
    string minute1Addition = "";
    string minute2Addition = "";
    pair<int, int> startTime = content->getDrawingStart();
    pair<int, int> endTime = content->getDrawingEnd();
    if(startTime.second < 10){
        minute1Addition = "0";
    }
    if(endTime.second < 10){
        minute2Addition = "0";
    }

    changedName = to_string(startTime.first) + ":" + to_string(startTime.second) + minute1Addition
                    + " - " + to_string(endTime.first) + ":" + to_string(endTime.second) + minute2Addition;

    return QString::fromStdString(changedName);
}

