#include <sstream>
#include <ctime>
#include <iomanip>
#include <task.h>
#include <profile.h>

Task::Task(std::string& name, std::string& start, std::string& end, std::string& due, std::string& catName):
    task_name(name),
    start_date_time(start),
    end_date_time(end),
    due_date_time(due) {
    try{
        category = findCategory(catName);
    }catch(TaskException e){
        std::cout << e.what() << std::endl;
    }
    setTimes();
}

Task::Task(std::string& in){
    std::string inputs[5];
    int i = 0;
    while(in.find('|') != -1){
        size_t pos = in.find('|');
        inputs[i] = in.substr(0,pos);
        in = in.substr(pos);
    }

    try{
        category = findCategory(inputs[4]);
    }catch(TaskException e){
        std::cout << e.what() << std::endl;
    }
    task_name = inputs[0];
    start_date_time = inputs[1];
    end_date_time = inputs[2];
    due_date_time = inputs[3];
    setTimes();
}

Category* Task::findCategory(std::string& catName){
    Category* ptr = NULL;
    int i;
    for(i = 0; i < Profile::categories.size(); i++){
        if(Profile::categories[i]->getName() == catName){
            ptr = Profile::categories[i];
            break;
        }
    }
    if(ptr == NULL){
        throw TaskException("No category exists with this name");
    }
    else
        return ptr;
}

void Task::updateTimeString(){
    start_date_time = ctime(&task_time.start);
    start_date_time.erase(std::remove(start_date_time.begin(), start_date_time.end(), '\n'), start_date_time.end());
    end_date_time = ctime(&task_time.end);
    end_date_time.erase(std::remove(end_date_time.begin(), end_date_time.end(), '\n'), end_date_time.end());
    due_date_time = ctime(&due);
    due_date_time.erase(std::remove(due_date_time.begin(), due_date_time.end(), '\n'), due_date_time.end());

}

void Task::setTimes(){
    task_time.start = strToTime(start_date_time);
    task_time.end = strToTime(end_date_time);
    due = strToTime(due_date_time);
    task_time.duration = difftime(task_time.end,task_time.start);
}

time_t Task::strToTime(std::string& t){
    //string must have structure DDD MMM NN hh:mm:ss YYYY
    struct std::tm* tm;
    std::istringstream ss(t);
    ss >> std::get_time(tm, "%c");
    return mktime(tm);
}

void Task::setStart(const time_t& time){
    task_time.start = time;
    task_time.end = task_time.start + task_time.duration;
}

Category* Task::getCategory() const{ return category; }

std::string Task::getName() const{ return task_name; }

std::string Task::getDue() const{ return due_date_time; }

std::string Task::getStart() const{ return start_date_time; }

std::string Task::getEnd() const{ return end_date_time; }

std::string Task::getDuration() const{ return duration_date_time; }

std::string Task::fileWrite() const{
    std::string output = task_name+"|"+start_date_time+"|"+end_date_time+"|"+due_date_time+"|"+ category->getName();
    return output;
}

int Task::compare(const Task& right){
    //due date > duration > priority
    if(due > right.due){
        return 1;
    }
    else if (due < right.due){
        return -1;
    }
    else{
        if(task_time.duration > right.task_time.duration){
            return 1;
        }
        else if(task_time.duration < right.task_time.duration){
            return -1;
        }
        else{
           if(category->getPriority() > right.getCategory()->getPriority())
               return 1;
           else
               return -1;
        }
    }
}

bool Task::operator<(const Task& right){
    return compare(right) < 0;
}

bool Task::operator==(const Task& right){
    return task_time == right.task_time &&
            task_name == right.getName() &&
            duration_date_time == right.getDuration() &&
            due_date_time == right.getDue();
}

bool Task::time_period::operator==(const time_period& right){
    return start == right.start && end == right.end;
}

bool Task::time_period::operator<( const time_period& right){
    if(duration != right.duration)
        return duration < right.duration;
    else{
        return start < right.start;
    }
}

TaskException::TaskException(std::string msg) : message(msg){}
std::string& TaskException::what() { return message; }
//----------------------------------------------------------------------------


Category::Category(std::string& name, int colour, int p){
    init(name,colour,p);

}

Category::Category(std::string& in){
    std::string inputs[3];
    int i = 0;
    while(in.find('|') != -1){
        size_t pos = in.find('|');
        inputs[i] = in.substr(0,pos);
        in = in.substr(pos);
    }

    int colour = atoi(inputs[1].c_str()),
        p = atoi(inputs[2].c_str());

    init(inputs[0],colour,p);
}

void Category::init(std::string& name, int colour, int p){
    this->catName = name;
    this->colour = colour;
    this->priority = p;
    visible = true;
}

void Category::incPriority(){
    if(priority > 3){
        swap(*Profile::categories[priority-1]);
        priority--;
    }
}

void Category::decPriority(){
    if(priority < Profile::categories.size() - 1){
        swap(*Profile::categories[priority + 1]);
        priority++;
    }
}

void Category::setPriority(int n){
    priority = n;
}

void Category::swap(Category& c){
    std::iter_swap(Profile::categories.begin()+priority, Profile::categories.begin()+c.getPriority());
    c.setPriority(priority);
}

std::string Category::fileWrite() const{
    std::string c = std::to_string(colour),
                p = std::to_string(priority);

    std::string output = catName+"|"+c+"|"+p;
    return output;
}

int Category::getColour() const{return colour;}

int Category::getPriority() const{return priority;}

std::string Category::getName() const{return catName;}

void Category::changeVisible(){ visible = !visible; }
