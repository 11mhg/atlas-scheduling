#ifndef SRC_CATEGORY_H_
#define SRC_CATEGORY_H_
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


class Category{
private:
    int priority;//sleep = 0, lectures = 1, work = 2, other values are variable, values < 3 cannot be rescheduled
    int colour;//0x000000 to 0xFFFFFF
    std::string catName;
    bool visible;
    void init(std::string&,int,int);
public:
    Category(std::string&);
    Category(std::string&,int,int);

    bool isVisible() const;
    std::string getName() const;
    int getColour() const;
    int getPriority() const;
    void changeVisible();
    void setPriority(int);

    void incPriority();
    void decPriority();
    void swap(Category& c);

    std::string fileWrite() const;


};



#endif /* SRC_CATEGORY_H_ */
