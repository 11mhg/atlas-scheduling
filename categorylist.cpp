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
   // update();
    //QApplication::processEvents();
    ui->setupUi(this);
} // end constructor

void CategoryList::setProfile(Profile* myProfile)
{
    this->myProfile = myProfile;
    for (int i = 0; i < checkBoxes.size(); i++) {
        delete checkBoxes.at(i); // or [i] ?
    }
    checkBoxes.clear();

    int xVal = this->geometry().left() - 15;
    int yVal = this->geometry().top() - 90;
    for (int i = 0; i < (myProfile->categories).size(); i++) {
        QString chBoxLabel = QString::fromStdString((myProfile->categories[i])->getName());
        checkBoxes.push_back(createChBox(QString::fromStdString("cb" + to_string(i)), chBoxLabel, xVal, yVal));
        checkBoxes[i]->setChecked(myProfile->categories[i]->isVisible());
        connect(checkBoxes[i], SIGNAL(stateChanged(int)), this, SLOT(checkEvent()));
        yVal = yVal + 25;
    }

} // end setProfile

void CategoryList::checkEvent(){
    for(unsigned int i = 0; i < checkBoxes.size(); i++){
        myProfile->categories[i]->setVisible(checkBoxes[i]->isChecked());
    }
}

QCheckBox* CategoryList::createChBox(QString chBoxName, QString chBoxLabel, int xVal, int yVal) {
    QCheckBox* chBox = new QCheckBox(this);
    chBox->setText(chBoxLabel);
    chBox->setGeometry(xVal, yVal, chBox->geometry().width(), chBox->geometry().height());
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
*/

void CategoryList::update(){
    QWidget::update();

    setProfile(this->myProfile);
    for(unsigned int i = 0; i < checkBoxes.size(); i++){
        checkBoxes[i]->setChecked(myProfile->categories[i]->isVisible());
    }
}

void CategoryList::paintEvent(QPaintEvent *pe) {
    QPainter painter(this);
    painter.setOpacity(1);

    painter.fillRect(pe->rect(), Qt::gray);
    QWidget::paintEvent(pe);

} // end paint event


CategoryList::~CategoryList()
{
    // delete all the checkboxes
    for (int i = 0; i < checkBoxes.size(); i++) {
        delete checkBoxes.at(i); // or [i] ?
    }
    checkBoxes.clear();
    delete ui;
} // end deconstructor
