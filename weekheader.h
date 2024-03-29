#ifndef WEEKHEADER_H
#define WEEKHEADER_H

#include <QWidget>
#include "ui_weekheader.h"
#include "profile.h"
#include "weeklycalendar.h"

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
    void setProfile(Profile* currentUser, WeeklyCalendar* cal);
private slots:
    void on_backButton_clicked();

    void on_forwardButton_clicked();

private:
    WeeklyCalendar* cal;
    Profile* currentUser;
    Ui::WeekHeader *ui;
};

#endif // WEEKHEADER_H
