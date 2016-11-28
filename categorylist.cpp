#include "categorylist.h"
#include "ui_categorylist.h"
#include <QCheckBox>
#include <QString>
#include <QPainter>
#include <QPaintEvent>

/*  static std::vector<Category*> categories; in profile
 *
void Category::changeVisible(){ visible = !visible; }

bool Category::isVisible() { return visible; } */
CategoryList::CategoryList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CategoryList)
{
    update();
    ui->setupUi(this);
} // end constructor

void CategoryList::setProfile(Profile* myProfile)
{
    int xVal = 50 * (myProfile->categories).size();
    int yVal = 50 * (myProfile->categories).size();
    const vector<QString> chBoxNames = {"cb1", "cb2", "cb3", "cb4","cb5","cb5","cb6"};
    for (int i = 0; i < (myProfile->categories).size(); i++) {
        QString chBoxLabel = QString::fromStdString((myProfile->categories[i])->getName());
        checkBoxes.push_back(createChBox(chBoxNames[i], chBoxLabel, xVal, yVal));
        xVal = xVal - 50;
        yVal = yVal - 50;
    }

} // end setProfile

QCheckBox* CategoryList::createChBox(QString chBoxName, QString chBoxLabel, int xVal, int yVal) {
    QCheckBox* chBox = new QCheckBox(this);
    chBox->setText(chBoxLabel);
    chBox->setGeometry(0,0,xVal,yVal);
    chBox->setObjectName(chBoxName);
    chBox->show();
    return chBox;
} // end createChBox
/*
 * void ExpandedTask::leaveEvent(QEvent* event){
    this->close();
    QWidget::leaveEvent(event);
}
void CollapsedTask::paintEvent(QPaintEvent *pe){
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

void CategoryList::paintEvent(QPaintEvent *pe) {
    QRect drawingRect = QRect(pe->rect().x(), pe->rect().y(), this->geometry().width(), this->geometry().height());
    QPainter painter(this);
    painter.setOpacity(1);
    painter.setPen(Qt::black);

   // painter.fillRect(drawingRect, QBrush::setColor(blue());
    painter.setOpacity(1);
 //   painter.drawText(drawingRect, Qt::AlignCenter | Qt::AlignHCenter, output);

} // end paint event
*/

CategoryList::~CategoryList()
{
    // delete all the checkboxes
    for (int i = 0; i < checkBoxes.size(); i++) {
        delete checkBoxes.at(i); // or [i] ?
    }
    checkBoxes.clear();
    delete ui;
} // end deconstructor
