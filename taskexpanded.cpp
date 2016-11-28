#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>

#include "taskexpanded.h"
#include "ui_taskexpanded.h"
#include "weeklycalendar.h"
#include "scheduler.h"

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
    QPalette tempPalette(palette());
    this->content = newContent;
    ui->setupUi(this);
    this->parent = parent;

    string styleString = "QLabel { background-color :";
    styleString += content->getCategory()->getColour() == Qt::red ? "red" : content->getCategory()->getColour() == Qt::green ? "light green" : "blue";
    styleString += "}";

    ui->labelName->setStyleSheet(QString::fromStdString(styleString));
    ui->labelTime->setStyleSheet(QString::fromStdString(styleString));
    ui->labelStatus->setStyleSheet(QString::fromStdString(styleString));

    ui->buttonComplete->setStyleSheet("QPushButton { background-color : white; }");
    ui->buttonDelay->setStyleSheet("QPushButton { background-color : white; }");

    if(content->getComplete()){
        statusText = "Complete";
    }
    else{
        statusText = chrono::system_clock::to_time_t(chrono::system_clock::now()) > content->task_time.end ? "Late" : "Pending";
    }
    ui->labelStatus->setText(QString::fromStdString("Status: " + statusText));
    ui->labelTime->setText(createString());
    ui->labelName->setText(QString::fromStdString(content->getName()));

    ui->buttonComplete->setEnabled(!content->getComplete());

    if(origin_y + this->height() > parent->geometry().height()){
        origin_y -= ((origin_y + this->height()) - parent->geometry().height());
    }
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


void ExpandedTask::on_buttonDelay_clicked()
{
    Scheduler().reschedule(content);
    content->TaskUser->SaveUserInfo();
    vector<Task*> weekTasks;
    Profile *User = content->TaskUser;
    for (int i = 0 ; i < content->TaskUser->wtasks.size();i++){
        weekTasks.push_back(&User->wtasks.at(i));
    }
    dynamic_cast<WeeklyCalendar*>(parent)->loadTasks(weekTasks);
    this->close();
    parent->update();
}

void ExpandedTask::on_buttonComplete_clicked()
{
    content->setComplete(true);
    parent->update();
}
