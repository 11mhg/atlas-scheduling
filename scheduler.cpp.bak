

#include <cstring>
#include <vector>
#include <scheduler.h>

std::vector<Category*> Profile::categories;
std::vector<Task> Profile::ptasks;
std::vector<Task> Profile::wtasks;

void Scheduler::reschedule(){
    reschedule(Profile::ptasks);
}

void Scheduler::reschedule(Task* task){
    std::vector<Task> t = {*task};
    reschedule(t);
}

void Scheduler::reschedule(std::vector<Task>& r_tasks){
    //do stuff

    std::sort(r_tasks.begin(), r_tasks.end());
    //remove tasks to be sorted from the master tasks vector
    for(Task t: r_tasks){
        removeTask(r_tasks,t);
    }
    //be greedy
    for(int j = 0; j < ftimes.size(); j++){
        Task::free_time* ft = &ftimes[j];
        for(int i = 0; i < r_tasks.size(); i++){
            Task* t = &r_tasks[i];
            if(fits(t, ft)){
                setTime(t, ft);
                removeTask(r_tasks,r_tasks[i]);
                if(ft->start < ft->end)
                    i = 0;//see if anything else fits inside the free space
            }
        }
    }

}

void Scheduler::reschedule(Category& cat){
    std::vector<Task> temp;
    for(int i = 0; i < Profile::ptasks.size(); i++){
        if( (Profile::ptasks[i].getCategory())->getPriority() == cat.getPriority())
            temp.push_back(Profile::ptasks[i]);
    }
    reschedule(temp);
}

void Scheduler::removeTask(std::vector<Task>& r_tasks, Task& task){
    auto it = std::find(r_tasks.begin(),r_tasks.end(),task);
    if(it != r_tasks.end()){
        using std::swap;
        swap(*it,r_tasks.back());
        r_tasks.pop_back();
    }
}

void Scheduler::setTime(Task* task,Task::free_time* ft){
    task->setStart(ft->start);
    ft->start = task->task_time.end;

    ft->duration = difftime(task->task_time.end, task->task_time.start);
}

bool Scheduler::fits(const Task* task, const Task::free_time* ft){
    using namespace std::chrono;
    return (task->task_time.duration) <= (ft->duration);
}

void Scheduler::getFreeTime(){
    std::vector<Task> all_tasks;
    all_tasks.reserve((Profile::ptasks).size() + (Profile::wtasks).size() + 7);
    all_tasks.insert(all_tasks.end(), (Profile::ptasks).begin(), (Profile::ptasks).end());
    all_tasks.insert(all_tasks.end(), (Profile::wtasks).begin(), (Profile::wtasks).end());
    ftimes.clear();
    std::sort(all_tasks.begin(), all_tasks.end());

    time_t t = time(NULL);
    std::tm* tm = localtime(&t),
            *tm2 = localtime(&t),
            *tm3 = localtime(&t);

    tm->tm_hour = 0;
    tm->tm_min = 0;
    tm->tm_sec = 0;
    tm2->tm_hour = 7;
    tm2->tm_min = 0;
    tm2->tm_sec = 0;
    tm3->tm_hour = 7;
    tm3->tm_min = 0;
    tm3->tm_sec=0;

    tm->tm_mday -= tm->tm_wday;
    tm->tm_wday = 0;
    tm2->tm_mday -= tm2->tm_wday;
    tm2->tm_wday = 0;
    tm3->tm_mday -= tm3->tm_wday;
    tm3->tm_wday = 0;

    for(; tm->tm_wday < 7; tm->tm_wday++, tm->tm_mday++,
                           tm2->tm_mday++, tm2->tm_wday++,
                           tm3->tm_mday++, tm3->tm_wday++) {
        std::string t_name = "SLEEP";
        char *s,*e,*d;
        strftime(s,80,"%c",tm);
        strftime(e,80,"%c",tm2);
        strftime(d,80,"%c",tm3);
        std::string s_time(s),
                    e_time(e),
                    d_time(d);
        Task t(t_name,s_time,e_time,d_time,Profile::categories[0]->getName());
        all_tasks.push_back(t);
    }
    sort(all_tasks.begin(),all_tasks.end());

    for(int i = 0;i < all_tasks.size() - 1; i++){
        Task::free_time ft;
        //conditions for checking sleep time as well
        ft.start = all_tasks[i].task_time.end;
        ft.end = all_tasks[i+1].task_time.start;
        if(ft.start != ft.end)
            ftimes.push_back(ft);
    }
}

Scheduler::Scheduler(){}
