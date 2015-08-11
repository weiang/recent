/*************************************************************************
	> File Name: sample_column.h
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2015年08月11日 星期二 22时10分38秒
    > Describition: 
 ************************************************************************/

#ifndef SAMPLE_COLUMN_H_
#define SAMPLE_COLUMN_H_

#include <string>
#include "column.h"

struct SampleColumn : public Column {
public:
    int x;
    double y;
    std::string str;

    virtual SampleColumn* get_data();
};

extern SampleColumn* sample_parse(const std::string&);

#endif 
