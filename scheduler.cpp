

#include <cstring>
#include <vector>
#include <scheduler.h>

std::vector<Category*> Profile::categories;
std::vector<Task> Profile::ptasks;
std::vector<Task*> Profile::wtasks;

std::vector<Task::free_time> Scheduler::ftimes;
std::vector<Task> Scheduler::sleep;
Task* Scheduler::selected_task;
class Profile;

void Scheduler::reschedule(Task* task){
    task->print();
    Scheduler::selected_task = task;
    getFreeTime();
    for(int j = 0; j < Scheduler::ftimes.size(); j++){
        if(fits(task, &Scheduler::ftimes[j])){
            setTime(task, &Scheduler::ftimes[j]);
            break;
        }
    }
    Scheduler::sleep.clear();
    Scheduler::ftimes.clear();
    task->print();
    std::cout << "--------------" << std::endl;
    for(int i = 0; i < Profile::wtasks.size(); i++){
        Profile::wtasks[i]->print();
    }

}

void Scheduler::setTime(Task* task,Task::free_time* ft){
    task->setStart(ft->start);
    ft->start = task->task_time.end;
    ft->duration = difftime(ft->end, ft->start);
}

bool Scheduler::fits(const Task* task, const Task::free_time* ft){
    return (task->task_time.duration) <= (ft->duration);
}

void Scheduler::getFreeTime(){
    //starts from chrono::now(), goes until things are done
    getSleepTimes();

    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    Scheduler::ftimes.clear();
    std::vector<Task> static_tasks;

    static_tasks.reserve(Profile::ptasks.size() + 6);
    static_tasks.insert(static_tasks.end(), Profile::ptasks.begin(),  Profile::ptasks.end());
    static_tasks.insert(static_tasks.end(), Scheduler::sleep.begin(), Scheduler::sleep.end());

    for(int i = 0; i < static_tasks.size(); i++){
        //Scheduler::selected_task->print();
        //std::cout << "------" << std::endl;
        //static_tasks[i].print();
        if(*Scheduler::selected_task == static_tasks[i]){
            std::swap(static_tasks[i], static_tasks[static_tasks.size() - 1]);
            static_tasks.pop_back();
        }
    }

    std::sort(static_tasks.begin(),static_tasks.end(),Task::less_than_key());

    for(int i = 0;i < static_tasks.size() - 1; i++){
        Task::free_time ft;
        ft.start = static_tasks[i].task_time.end;
        ft.end = static_tasks[i+1].task_time.start;
        ft.duration = std::difftime(ft.end,ft.start);
        if(ft.start != ft.end)
            Scheduler::ftimes.push_back(ft);
    }
    //subset of ftimes from now() to end of week
    int i = (Scheduler::ftimes.size());

    for(i -= 1; i > -1;i--){
        if(Scheduler::ftimes[i].end < now){//already ended
            Scheduler::ftimes.erase(Scheduler::ftimes.begin() + i);//remove unusable time periods
        }
        else if(Scheduler::ftimes[i].start < now && Scheduler::ftimes[i].end > now){//now is during period
            Scheduler::ftimes[i].start = now;
            Scheduler::ftimes[i].duration = difftime(Scheduler::ftimes[i].end,Scheduler::ftimes[i].start);
        }
    }

    std::cout << "----FTIMES START----" << std::endl;
    for(int i = 0; i < ftimes.size(); i++){
        ftimes[i].print();
        std::cout << std::endl;
    }
    std::cout << "-----FTIMES END-----" << std::endl;
}

void Scheduler::restartWeek(struct std::tm* tm){
    time_t t = Profile::StartOfWeek();
    tm = localtime(&t);
}

void Scheduler::getSleepTimes(){
    Scheduler::sleep.clear();
    time_t t = time(NULL);
    std::tm tm =  *localtime(&t),
            tm2 = *localtime(&t),
            tm3 = *localtime(&t);

    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;

    tm2.tm_hour = 8;
    tm2.tm_min = 0;
    tm2.tm_sec = 0;

    tm3.tm_hour = 8;
    tm3.tm_min = 0;
    tm3.tm_sec=0;

    restartWeek(&tm);
    restartWeek(&tm2);
    restartWeek(&tm3);

    for(; tm.tm_wday < 7; tm.tm_wday++, tm.tm_mday++,
                           tm2.tm_mday++, tm2.tm_wday++,
                           tm3.tm_mday++, tm3.tm_wday++) {
        std::string t_name = "SLEEP";
        time_t a = mktime(&tm),
               b = mktime(&tm2),
               c = mktime(&tm3);
        a -= 4*3600;//4h
        std::string s_time(ctime(&a)),
                    e_time(ctime(&b)),
                    d_time(ctime(&c));
        Task t(t_name,s_time,e_time,d_time,Profile::categories[0]->getName());
        Scheduler::sleep.push_back(t);
    }
}

Scheduler::Scheduler(){}
