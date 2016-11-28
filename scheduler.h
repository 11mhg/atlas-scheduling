#pragma once

#include <profile.h>

class Scheduler {
private:
    Scheduler();
    static std::vector<Task::free_time> ftimes;
    static std::vector<Task> sleep;
    static Task* selected_task;
    static void getFreeTime();
    static void setTime(Task*,Task::free_time*);
    static bool fits(const Task*, const Task::free_time*);
    static void restartWeek(struct std::tm*);
    static void getSleepTimes();

public:
    static void reschedule(Task*);

    /* CONSTRAINTS
     * priority 0 categories cannot be rescheduled
     * tasks are sorted by due date, then by priority
     * cannot start or end after due date
     * tasks may not overlap
     */

};

