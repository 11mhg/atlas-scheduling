#pragma once

#include <profile.h>

class Scheduler {
private:

    std::vector<Task::free_time> ftimes;

    void removeTask(std::vector<Task>&,Task&);
    void getFreeTime();

    void setTime(Task*,Task::free_time*);
    bool fits(const Task*, const Task::free_time*);

public:
    Scheduler();
    ~Scheduler();

    void reschedule();
    void reschedule(Task*);
    void reschedule(std::vector<Task>&);
    void reschedule(Category&);


    /* CONSTRAINTS
     * priority 0 categories cannot be rescheduled
     * tasks are sorted by due date, then by priority
     * cannot start or end after due date
     * tasks may not overlap
     */


};

