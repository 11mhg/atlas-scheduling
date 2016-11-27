#ifndef WEEKHEADER_H
#define WEEKHEADER_H

#include <QWidget>
#include "ui_weekheader.h"

namespace Ui {
class WeekHeader;
}

class WeekHeader : public QWidget
{
    Q_OBJECT

public:
    explicit WeekHeader(QWidget *parent = 0);
    ~WeekHeader();
    time_t StartOfWeek();
    time_t EndOfWeek();

private:
    Ui::WeekHeader *ui;
};

#endif // WEEKHEADER_H
