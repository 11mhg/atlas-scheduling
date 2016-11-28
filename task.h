#pragma once

#include <string>
#include <ctime>
#include <chrono>
#include <category.h>
#include <utility>
#include <QTime>


class Profile;

using namespace std;

class Task {
private:
    string task_name,
                start_date_time,
                end_date_time,
                due_date_time,
                duration_date_time;

    bool completeFlag;
    Category* category;

    //static chrono::system_clock::time_point<chrono::system_clock::now()> now;

    static Category* findCategory(string& catName);
    static time_t strToTime(string&);
    void setTimes();
    void updateTimeString();
public:
    Profile* TaskUser;
    struct time_period {
        time_t start,
               end;
        double duration;
        bool operator<(const time_period& right);
        bool operator==(const time_period& right);
		void print();
    };
    typedef struct time_period time_period;
    typedef time_period free_time;

	struct less_than_key
    {
        inline bool operator() (const Task& t1, const Task& t2)
        {
            return (t1.task_time.start < t2.task_time.start);
        }
    };
    time_t due;
    time_period task_time;

    Task(string& name, string& start, string& end, string& due, string& category,Profile *User);
    Task(string& name, string& start, string& end, string& due, string& category);
    Task(string& name, QDateTime start, QDateTime end, QDateTime due, string& category,Profile *User);
    Task(string& in,Profile *User);

    bool getComplete() const;
    void setComplete(bool t);
    void increment();
    string getName() const;
    string getDue() const;
    int getDrawingDay() const;
    string getStart() const;
    pair<int, int> getDrawingStart() const;
    string getEnd() const;
    pair<int, int> getDrawingEnd() const;
    string getDuration() const;
    Category* getCategory() const;
    time_t getDueTime() const;

    string fileWrite() const;

    void setStart(const time_t&);
	void print();

    bool compare(const Task&);
    bool operator<(const Task& right);
    bool operator==(const Task& right);
};

class TaskException{
private:
    string message;
public:
    TaskException(string msg);
    string& what();
};
