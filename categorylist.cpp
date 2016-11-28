#include "categorylist.h"
#include "ui_categorylist.h"
#include <QCheckBox>
#include <QString>

/*  static std::vector<Category*> categories; in profile
 *
void Category::changeVisible(){ visible = !visible; }

bool Category::isVisible() { return visible; } */
CategoryList::CategoryList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CategoryList)
{
    ui->setupUi(this);
} // end constructor

void CategoryList::setProfile(Profile* myProfile)
{
    int xVal = 100;
    int yVal = 100;
    const vector<QString> chBoxNames = {"cb1", "cb2", "cb3", "cb4","cb5","cb5","cb6"};
    for (int i = 0; i < (myProfile->categories).size(); i++) {
        QString chBoxLabel = QString::fromStdString((myProfile->categories[i])->getName());
        checkBoxes.push_back(createChBox(chBoxNames[i], chBoxLabel, xVal, yVal));
        xVal = xVal - 35;
        yVal = yVal - 35;
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
 * */


CategoryList::~CategoryList()
{
    // delete all the checkboxes
    for (int i = 0; i < checkBoxes.size(); i++) {
        delete checkBoxes.at(i); // or [i] ?
    }
    delete ui;
} // end deconstructor
