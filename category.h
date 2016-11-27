#ifndef SRC_CATEGORY_H_
#define SRC_CATEGORY_H_
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <QColor>


class Category{
private:
    int priority;//sleep = 0, lectures = 1, work = 2, other values are variable, values < 3 cannot be rescheduled
    int colour;//0x000000 to 0xFFFFFF
    std::string catName;
    bool visible;
    void init(std::string&,int,int);
    enum CatColour{red, green, mauve};
    CatColour categorycolour;
public:
    Category(std::string&);
    Category(std::string&,int,int);
    CatColour categoryColour();
    bool isVisible() const;
    std::string getName() const;
    QColor getColour();
    int getPriority() const;
    void changeVisible();
    void setPriority(int);
    void incPriority();
    void decPriority();
    void swap(Category& c);

    std::string fileWrite() const;


};



#endif /* SRC_CATEGORY_H_ */
