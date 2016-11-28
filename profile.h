#ifndef PROFILE_H
#define PROFILE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <chrono>
#include "task.h"
#include "botan/botan.h"
#include "botan/pipe.h"
#include "botan/bcrypt.h"
#include "botan/sha2_32.h"
#include "botan/basefilt.h"
#include "botan/filters.h"
#include "botan/pbkdf2.h"
#include "botan/hmac.h"
#include "botan/sha160.h"
#include "botan/kdf.h"
#include "botan/secmem.h"



class Profile
{
public:
    struct stats{
        int productivity;
        int timeManagement;
    };
    static std::vector<Category*> categories;
    static std::vector<Task> ptasks;//user defined tasks
    static std::vector<Task*> wtasks;//weekly tasks

    time_t currentWeek; //really the second you log in...shhhhhhhh
    void SetTasks(vector<Task> t);
    std::map<std::string,std::string> settings;
    Profile(std::string User, std::string Pass);
    bool lockedItem;
    void SaveUserInfo();
    void UpdateSave();
    void LogOut();
    void LoadInfo();
    void LoadTasks();
    void pushTasks();
    std::string combo;
    Profile();
    stats Stats;
    std::string name;
    std::string gender;
    std::string DoB;
    std::string email;
    std::string characterSelect;
    static time_t StartOfWeek();
    time_t EndOfWeek();
    std::vector<Task*> getWeeklyTasks();
    std::vector<Task*> getTasksInTime(time_t start, time_t end);
    void addTask(Task newTask);
    void setUserName(std::string un);
private:
    std::string Encrypt(std::string s);
    std::string Decrypt(std::string s);
    std::string username;
    std::string password;
};

std::string EncryptLogin(std::string user, std::string pass);
std::string HashUserName(std::string User);
bool SuccessfulLogin(std::string username, std::string password);
bool UserNameExists(std::string username);



#endif // PROFILE_H
