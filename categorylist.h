#ifndef CATEGORYLIST_H
#define CATEGORYLIST_H

#include <QWidget>
#include "ui_categorylist.h"
#include "profile.h"
#include <QCheckBox>
#include <vector>

using namespace std;

namespace Ui {
class CategoryList;
}

class CategoryList : public QWidget
{
    Q_OBJECT

public:
   explicit CategoryList(QWidget *parent = 0);
   void setProfile(Profile* myProfile);
   ~CategoryList();
   QCheckBox* createChBox(QString chBoxName, QString chBoxLabel, int xVal, int yVal);
   void update();
   void paintEvent(QPaintEvent *pe);

public slots:
   void checkEvent();

private:
   vector<QCheckBox*> checkBoxes;
   Profile* myProfile;
   Ui::CategoryList *ui;
};

#endif // CATEGORYLIST_H
