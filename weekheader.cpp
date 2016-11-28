#include "weekheader.h"
#include "atlaswelcome.h"
#include <QLabel>
#include <QMessageBox>
#include <chrono>
#include <string>
#include <iostream>
/*
 *
 * ExpandedTask::ExpandedTask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskExpanded)
{
    ui->setupUi(this);
}

ExpandedTask::ExpandedTask(QWidget *parent, Task* newContent, int origin_x, int origin_y) :
    QWidget(parent),
    ui(new Ui::TaskExpanded)
{*/
/*
WeekHeader::WeekHeader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeekHeader) {
    ui->setupUi(this);
}
*/

WeekHeader::WeekHeader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeekHeader)
{
    ui->setupUi(this);
}

void WeekHeader::setProfile(Profile* currentUser){
    this->currentUser = currentUser;
    std::string days[] = {"Sun","Mon","Tue","Wed", "Thur"};//so on and so forth
    std::string months[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
    struct std::tm *tm;
    struct std::tm *tm2;
    struct std::tm *tm3;
    time_t t = currentUser->currentWeek;
    tm = localtime(&t);
    time_t t3;
    t3 = t - tm->tm_wday*24*3600;
    t -= t%86400;//sets time to 00:00:00
    t -= 19*3600;//clears the weird time offset
    time_t t2 = t3 + (6*24*3600);
    tm3 = localtime(&t3);
    std::string str = months[tm3->tm_mon] + " " + std::to_string(tm3->tm_mday) + " " + std::to_string(tm3->tm_year +1900) + " - ";
    tm2 = localtime(&t2);
    str += months[tm2->tm_mon] + " " + std::to_string(tm2->tm_mday) + " " + std::to_string(tm2->tm_year + 1900);
/*
    time_t t = StartOfWeek();
    time_t t2 = EndOfWeek();
    struct std::tm *tm3 = localtime(&t);
    struct std::tm *tm2 = localtime(&t2);*/



   // std::string str = days[tm->tm_wday] + " " + months[tm->tm_mon] + " " + tm->tm_mday + " "tm->tm_year;

   ui->labelHeader->setText(QString("Week of: %1").arg(QString::fromStdString(str)));
}

time_t WeekHeader::StartOfWeek(){
    time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct std::tm* tm = localtime(&t);
    //fix days
    if(tm->tm_mday < tm->tm_wday){
        tm->tm_mon--;
        if(tm->tm_mon < 0){
            tm->tm_mon = 11;
            tm->tm_year--;
        }
        switch(tm->tm_mon){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            tm->tm_mday = 31 - (tm->tm_wday - tm->tm_mday);
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            tm->tm_mday = 30 - (tm->tm_wday - tm->tm_mday);
            break;
        case 2:
            tm->tm_mday = 28 - (tm->tm_wday - tm->tm_mday);
            break;
        default:
            break;
        }
    }
    else{
        tm->tm_mday -= tm->tm_wday;
    }
    tm->tm_wday = 0;
    tm->tm_hour = 0;
    tm->tm_min = 0;
    tm->tm_sec = 0;
    return mktime(tm);
}
time_t WeekHeader::EndOfWeek(){
    time_t t = StartOfWeek();
    t += 7*24*3600 - 1;
    return t;
}

WeekHeader::~WeekHeader()
{
    delete ui;
}



void WeekHeader::on_backButton_clicked()
{
    currentUser->currentWeek -= 7*24*60*60;
    currentUser->LoadTasks();
    setProfile(currentUser);
}

void WeekHeader::on_forwardButton_clicked()
{
    currentUser->currentWeek += 7*24*60*60;
    currentUser->LoadTasks();
    setProfile(currentUser);
}
