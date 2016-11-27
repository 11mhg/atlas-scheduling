#include "weeklycalendar.h"
#include <QScrollBar>;
#include <QStandardItem>;

WeeklyCalendar::WeeklyCalendar()
{
    QTableWidget::QTableWidget();
}

WeeklyCalendar::WeeklyCalendar(QWidget* parent)
{
    QTableWidget::QTableWidget(parent);
    this->setParent(parent);
    setMouseTracking(true);

    QStringList labels;
    labels.append("");
    labels.append("Sunday");
    labels.append("Monday");
    labels.append("Tuesday");
    labels.append("Wednesday");
    labels.append("Thursday");
    labels.append("Friday");
    labels.append("Saturday");
    this->setRowCount(24);
    this->setColumnCount(8);

    this->verticalHeader()->setVisible(false);
    this->setHorizontalHeaderLabels(labels);

    this->setStyleSheet("background-color: #D1FDFF");
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->verticalScrollBar()->setValue(8);
 //   QTableView::verticalHeader()->setDefaultSectionSize(50); // this fucks up the vertical from scroll starting at 8
    QTableView::horizontalHeader()->setDefaultSectionSize(150);

    this->setSelectionMode(QTableWidget::NoSelection);
    this->viewport()->setFocusPolicy(Qt::NoFocus);


    for(int i = 0; i < 24; i++){
        QString timeLabel = QString("%1:00-%2:00").arg(QString::number(i), QString::number(i+1));
        this->setItem(i, 0, new QTableWidgetItem(timeLabel));
    }

    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setColumnWidth(0,75);
}


WeeklyCalendar::~WeeklyCalendar(){
    for(unsigned int i = 0; i < currentTasks.size(); i++){
        delete(currentTasks[i]);
    }
    currentTasks.resize(0);
}

void WeeklyCalendar::paintEvent(QPaintEvent *pe){
    QTableWidget::paintEvent(pe);
    for(unsigned int i = 0; i < currentTasks.size(); i++){
        currentTasks[i]->update();
    }
}

void WeeklyCalendar::loadTasks(vector<Task*> newTasks){
    for(unsigned int i = 0; i < currentTasks.size(); i++){
        delete(currentTasks[i]);
    }
    currentTasks.resize(0);

    for(unsigned int i = 0; i < newTasks.size(); i++){
        currentTasks.push_back(new CollapsedTask(this, newTasks[i]));
    }
}
