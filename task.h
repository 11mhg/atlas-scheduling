#pragma once

#include <string>
#include <ctime>
#include <chrono>
#include <category.h>

class Profile;

class Task {
private:


    std::string task_name,
                start_date_time,
                end_date_time,
                due_date_time,
                duration_date_time;

    Category* category;

    //static std::chrono::system_clock::time_point<std::chrono::system_clock::now()> now;

    static Category* findCategory(std::string& catName);
    static time_t strToTime(std::string&);
    void setTimes();
    void updateTimeString();
public:
    struct time_period {
        time_t start,
               end;
        double duration;
        bool operator<(const time_period& right);
        bool operator==(const time_period& right);
    };
    typedef struct time_period time_period;
    typedef time_period free_time;

    time_t due;
    time_period task_time;

    Task(std::string& name, std::string& start, std::string& end, std::string& due, std::string& category);
    Task(std::string& in);

    std::string getName() const;
    std::string getDue() const;
    std::string getStart() const;
    std::string getEnd() const;
    std::string getDuration() const;
    Category* getCategory() const;

    std::string fileWrite() const;

    void setStart(const time_t&);

    int compare(const Task&);
    bool operator<(const Task& right);
    bool operator==(const Task& right);
};

class TaskException{
private:
    std::string message;
public:
    TaskException(std::string msg);
    std::string& what();
};
