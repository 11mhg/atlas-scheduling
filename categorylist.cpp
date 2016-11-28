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
    // create all the labels
    /*    for(int i = 0; i < 24; i++){
        QString timeLabel = QString("%1:00-%2:00").arg(QString::number(i), QString::number(i+1));
        this->setItem(i, 0, new QTableWidgetItem(timeLabel));
    }

     */
    for (int i = 0; i < (myProfile->categories).size(); i++) {
        QString chBoxLabel = QString::fromStdString((myProfile->categories.at(i))->getName());
        QCheckBox *chboxlabel = new QCheckBox(chBoxLabel, this);
    }
}

void CategoryList::setProfile(Profile* myProfile)
{
    //QCheckBox::QCheckBox(const QString & text, QWidget * parent = 0)
  //  for (int i = 0; i < )
 /*  ui->category1->s
    if (ui->category1->isChecked()) {
        // draw all tasks in category1
    }
    if (ui->category2->isChecked()) {
        // draw all tasks in category2
    }
    if (ui->category3->isChecked()) {
        // draw all tasks in category3
    }*/
}

CategoryList::~CategoryList()
{
    delete ui;
}
