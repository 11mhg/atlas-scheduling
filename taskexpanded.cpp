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

ExpandedTask::ExpandedTask(QWidget *parent, task content, int origin_x, int origin_y) :
    QWidget(parent),
    ui(new Ui::TaskExpanded)
{
    ui->setupUi(this);
    this->parent = parent;

    ui->labelName->setText(QString::fromStdString(content.name));
    setGeometry(origin_x, origin_y, this->width(), this->height());
}

ExpandedTask::~ExpandedTask()
{
    delete ui;
}

void ExpandedTask::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(event->rect(), Qt::blue);
}

void ExpandedTask::leaveEvent(QEvent* event){
    this->close();
    QWidget::leaveEvent(event);
}

