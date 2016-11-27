#ifndef TASKEXPANDED_H
#define TASKEXPANDED_H

#include <QWidget>
#include <QMouseEvent>

#pragma once

using namespace std;

enum Days{
    Sunday = 1,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

struct task{
    int start_hour, start_minute, end_hour, end_minute;
    string name;
    Days day;

    task(string n, int sh, int sm, int eh, int em, int d){
        name = n;
        start_hour = sh;
        start_minute = sm;
        end_hour = eh;
        end_minute = em;
        day = (Days)d;
    }
};

namespace Ui {
class TaskExpanded;
}

class ExpandedTask : public QWidget
{
    Q_OBJECT

public:
    explicit ExpandedTask(QWidget *parent = 0);
    ExpandedTask(QWidget *parent, task content, int origin_x, int origin_y);
    ~ExpandedTask();
    void leaveEvent(QEvent* event);
    void paintEvent(QPaintEvent* event);

private:
    QWidget* parent;
    Ui::TaskExpanded *ui;
};

#endif // TASKEXPANDED_H
