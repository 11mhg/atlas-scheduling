#ifndef WEEKLYCALENDAR_H
#define WEEKLYCALENDAR_H

#include <QTableWidget>
#include <QLabel>
#include <QHeaderView>
#include <QMessageBox>
#include "taskcollapsed.h"
#include <vector>

#pragma once

using namespace std;

class WeeklyCalendar : public QTableWidget
{
public:
    WeeklyCalendar();
    WeeklyCalendar(QWidget* parent);
    ~WeeklyCalendar();
    void paintEvent(QPaintEvent *pe);
    void loadTasks(vector<task> newTasks);

private:
    vector<CollapsedTask*> currentTasks;
};

#endif // WEEKLYCALENDAR_H
