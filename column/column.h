/*************************************************************************
	> File Name: column.h
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2015年08月11日 星期二 22时08分28秒
    > Describition: 
 ************************************************************************/

#ifndef COLUMN_H_
#define COLUMN_H_

#include <string>

template <typename T>
class Column {
public:
    Column(const std::string& s) 
    {
        parse(s);
    }

    T& parse(const std::string& s);

    T& get_data();
private:
    T _data;
};

#endif // COLUMN_H_
