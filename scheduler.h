#pragma once

#include <profile.h>

class Scheduler {
private:
    static std::vector<Task::free_time> ftimes;
    static std::vector<Task> sleep;
    static void getFreeTime();
    static void setTime(Task*,Task::free_time*);
    static bool fits(const Task*, const Task::free_time*);
    static void restartWeek(struct std::tm*);
    static void getSleepTimes();

public:
    Scheduler();
    static void reschedule();
    static void reschedule(Task*);
    static void reschedule(std::vector<Task*>);
    static void reschedule(Category*);
    static void reschedule(std::vector<Task>&);

    /* CONSTRAINTS
     * priority 0 categories cannot be rescheduled
     * tasks are sorted by due date, then by priority
     * cannot start or end after due date
     * tasks may not overlap
     */

};

