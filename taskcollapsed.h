#ifndef TASKCOLLAPSED_H
#define TASKCOLLAPSED_H

#include <QWidget>
#include "taskexpanded.h"

#pragma once

class WeeklyCalendar;

using namespace std;

class CollapsedTask : public QWidget
{
    Q_OBJECT

public:
    CollapsedTask(WeeklyCalendar *parent, task content);
    ~CollapsedTask();

    void update();
    void paintEvent(QPaintEvent *pe);
    void enterEvent(QEvent * event);

    ExpandedTask* currentExpanded;

private:
    bool justUpdated;
    const int MAX_NAME_LENGTH = 20;
    task content;
    QString createString();
    WeeklyCalendar* parent;
};

#endif // TASKCOLLAPSED_H
