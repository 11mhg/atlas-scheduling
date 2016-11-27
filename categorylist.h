#ifndef CATEGORYLIST_H
#define CATEGORYLIST_H

#include <QWidget>
#include "ui_categorylist.h"
#include "profile.h"

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

private:
    Profile* myProfile;
    Ui::CategoryList *ui;
};

#endif // CATEGORYLIST_H
