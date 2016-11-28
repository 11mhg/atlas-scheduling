

#include <cstring>
#include <vector>
#include <scheduler.h>

std::vector<Category*> Profile::categories;
std::vector<Task> Profile::ptasks;
std::vector<Task> Profile::wtasks;

std::vector<Task::free_time> Scheduler::ftimes;
std::vector<Task> Scheduler::sleep;
std::vector<Task*> Scheduler::selected_tasks;
class Profile;

void Scheduler::reschedule(){
    std::vector<Task*> temp;
    for(int i = 0; i < Profile::ptasks.size(); i++){
        Task* ptr = &(Profile::ptasks[i]);
        temp.push_back(ptr);
    }
    Scheduler::selected_tasks = temp;
    Scheduler::reschedule(temp);
}

void Scheduler::reschedule(Task* task){
    std::cout << "----------------------------------\nrescheduling task" << std::endl;
    std::vector<Task*> t = {task};
    Scheduler::selected_tasks = t;
    Scheduler::reschedule(t);
}

void Scheduler::reschedule(std::vector<Task>& tasks){
    std::vector<Task*> v;
    for(int i = 0; i < tasks.size(); i++){
        Task* t = &tasks[i];
        v.push_back(t);
    }
    Scheduler::selected_tasks = v;
    Scheduler::reschedule(v);
}

void Scheduler::reschedule(Category* cat){
    std::vector<Task*> temp;
    for(int i = 0; i < Profile::ptasks.size(); i++){
        if( (Profile::ptasks[i].getCategory())->getPriority() == cat->getPriority()){
            Task* ptr = &(Profile::ptasks[i]);
            temp.push_back(ptr);
        }
    }
    Scheduler::selected_tasks = temp;
    Scheduler::reschedule(temp);
}

void Scheduler::reschedule(std::vector<Task*> r_tasks){
    std::sort(r_tasks.begin(), r_tasks.end());
    getFreeTime();
    for(int i = 0; i < r_tasks.size(); i++){
        for(int j = 0; j < Scheduler::ftimes.size(); j++){
            if(Scheduler::ftimes[j].start >= Scheduler::ftimes[j].end){
                Scheduler::ftimes.erase(Scheduler::ftimes.begin()+j);
                j = 0;
            }
            if(fits(r_tasks[i], &Scheduler::ftimes[j])){
                setTime(r_tasks[i], &Scheduler::ftimes[j]);
                break;
            }
        }
    }
    Scheduler::sleep.clear();
    Scheduler::ftimes.clear();
    Scheduler::selected_tasks.clear();
    //std::vector<Task> v;
    //for(int i = 0; i < r_tasks.size(); i++){
    //    Task t = *r_tasks[i];
    //    v.push_back(t);
    //}
    //Profile::ptasks = v;
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

    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    Scheduler::ftimes.clear();
    std::vector<Task> static_tasks;

    static_tasks.reserve(Profile::wtasks.size() + Profile::ptasks.size() + 7 - selected_tasks.size());
    static_tasks.insert(static_tasks.end(), Profile::wtasks.begin(),Profile::wtasks.end());
    getSleepTimes();
    static_tasks.insert(static_tasks.end(), Scheduler::sleep.begin(), Scheduler::sleep.end());
    //remove all elements in selected_tasks from static_tasks

    //std::sort(Scheduler::selected_tasks.begin(), Scheduler::selected_tasks.end(), Task::less_than_key());
    //std::sort(static_tasks.begin(),static_tasks.end(),Task::less_than_key());

    //if not in selected_tasks, add to static_tasks
    for(int i = 0; i < Profile::ptasks.size(); i++){
        bool add = true;
        for(int j = 0; j < Scheduler::selected_tasks.size();j++){
            if(Scheduler::selected_tasks[j] == &Profile::ptasks[i]){
                add = false;
                break;

            }
        }
        if(add){
            Task t = Profile::ptasks[i];
            static_tasks.push_back(t);
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
        else{//hasn't started yet

        }
    }


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
