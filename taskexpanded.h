#ifndef TASKEXPANDED_H
#define TASKEXPANDED_H

#include <QWidget>
#include <QMouseEvent>
#include "task.h"

#pragma once

using namespace std;

namespace Ui {
class TaskExpanded;
}

class ExpandedTask : public QWidget
{
    Q_OBJECT

public:
    explicit ExpandedTask(QWidget *parent = 0);
    ExpandedTask(QWidget *parent, Task* newContent, int origin_x, int origin_y);
    ~ExpandedTask();
    void update();
    void leaveEvent(QEvent* event);
    void paintEvent(QPaintEvent* event);

private:
    QString createString();
    Task* content;
    QWidget* parent;
    Ui::TaskExpanded *ui;
};

#endif // TASKEXPANDED_H
