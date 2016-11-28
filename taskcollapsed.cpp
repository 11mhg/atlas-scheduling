#include <QPainter>
#include <QPaintEvent>
#include <string>

#include "taskcollapsed.h"
#include "weeklycalendar.h"

CollapsedTask::CollapsedTask(WeeklyCalendar *parent, Task* newContent) :
    QWidget((QWidget*)parent),
    content(newContent)
{
    this->setParent((QWidget*)parent);
    this->parent = parent;
}

CollapsedTask::~CollapsedTask()
{
}

QString CollapsedTask::createString(){
    string changedName;
    string minute1Addition = "";
    string minute2Addition = "";
    pair<int, int> startTime = content->getDrawingStart();
    pair<int, int> endTime = content->getDrawingEnd();
    if(content->getName().size() > MAX_NAME_LENGTH){
        changedName =  content->getName().substr(0, MAX_NAME_LENGTH - 3);
        changedName += "...";
    }
    else{
        changedName = content->getName();
    }

    if(startTime.second < 10){
        minute1Addition = "0";
    }
    if(endTime.second < 10){
        minute2Addition = "0";
    }

    changedName += "\n";
    changedName += to_string(startTime.first) + ":" + to_string(startTime.second) + minute1Addition
                    + " - " + to_string(endTime.first) + ":" + to_string(endTime.second) + minute2Addition;

    return QString::fromStdString(changedName);
}

void CollapsedTask::update(){
    pair<int, int> startTime = content->getDrawingStart();
    pair<int, int> endTime = content->getDrawingEnd();
    //drawing geometry logic
    int drawWidth = parent->columnWidth(content->getDrawingDay());
    int drawLeft = parent->columnViewportPosition(content->getDrawingDay());
    float percentOfSHour = ((float)startTime.second/60.0);
    float percentOfEHour = ((float)endTime.second/60.0);
    int drawTop = parent->rowViewportPosition(startTime.first-7) + parent->rowHeight(startTime.first-7)*percentOfSHour - 0.25*parent->rowHeight(startTime.first-7);
    int drawBottom = parent->rowViewportPosition(endTime.first-7) + parent->rowHeight(endTime.first-7)*percentOfEHour - 0.25*parent->rowHeight(endTime.first-7);
    QRect controlRect(drawLeft, drawTop, drawWidth, abs(drawBottom - drawTop));
    this->setGeometry(controlRect);

    QWidget::update();
}

void CollapsedTask::paintEvent(QPaintEvent *pe){
    if(!content->getCategory()->isVisible()){
        return;
    }
    QString output = createString();
    QRect drawingRect = QRect(pe->rect().x(), pe->rect().y(), this->geometry().width(), this->geometry().height());
    QPainter painter(this);
    painter.setOpacity(0.75);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.fillRect(drawingRect, content->getCategory()->getColour());
    painter.setOpacity(1);
    painter.drawText(drawingRect, Qt::AlignCenter | Qt::AlignHCenter, output);
}

void CollapsedTask::enterEvent(QEvent* /*event*/){
    if(!content->getCategory()->isVisible()){
        return;
    }
    currentExpanded = new ExpandedTask(parent, content, this->geometry().left(), this->geometry().top());
    currentExpanded->show();
}
