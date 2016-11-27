#include <QPainter>
#include <QPaintEvent>
#include <string>

#include "taskcollapsed.h"
#include "weeklycalendar.h"

CollapsedTask::CollapsedTask(WeeklyCalendar *parent, task newContent) :
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
    if(content.name.size() > MAX_NAME_LENGTH){
        changedName =  content.name.substr(0, MAX_NAME_LENGTH - 3);
        changedName += "...";
    }
    else{
        changedName = content.name;
    }

    if(content.start_minute < 10){
        minute1Addition = "0";
    }
    if(content.end_minute < 10){
        minute2Addition = "0";
    }

    changedName += "\n";
    changedName += to_string(content.start_hour) + ":" + to_string(content.start_minute) + minute1Addition
                    + " - " + to_string(content.end_hour) + ":" + to_string(content.end_minute) + minute2Addition;

    return QString::fromStdString(changedName);
}

void CollapsedTask::update(){
    //drawing geometry logic
    int drawWidth = parent->columnWidth(content.day);
    int drawLeft = parent->columnViewportPosition(content.day);
    float percentOfSHour = ((float)content.start_minute/60.0);
    float percentOfEHour = ((float)content.end_minute/60.0);
    int drawTop = parent->rowViewportPosition(content.start_hour+1) + parent->rowHeight(content.start_hour+1)*percentOfSHour - 0.25*parent->rowHeight(content.start_hour);
    int drawBottom = parent->rowViewportPosition(content.end_hour+1) + parent->rowHeight(content.end_hour+1)*percentOfEHour - 0.25*parent->rowHeight(content.end_hour);
    QRect controlRect(drawLeft, drawTop, drawWidth, abs(drawBottom - drawTop));
    this->setGeometry(controlRect);

}

void CollapsedTask::paintEvent(QPaintEvent *pe){
    QString output = createString();
    QRect drawingRect = QRect(pe->rect().x(), pe->rect().y(), this->geometry().width(), this->geometry().height());
    QPainter painter(this);
    painter.setOpacity(0.75);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.fillRect(drawingRect, Qt::blue);
    painter.setOpacity(1);
    painter.drawText(drawingRect, Qt::AlignCenter | Qt::AlignHCenter, output);
}

void CollapsedTask::enterEvent(QEvent* /*event*/){
    currentExpanded = new ExpandedTask(parent, content, this->geometry().left(), this->geometry().top());
    currentExpanded->show();
}
