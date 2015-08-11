/*************************************************************************
	> File Name: sample_column.cpp
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2015年08月11日 星期二 22时13分20秒
    > Describition: 
 ************************************************************************/

#include <iostream>
#include "sample_column.h"

SampleColumn* SampleColumn::get_data()
{
    std::cout << "In SampleColumn" << std::endl;
    return this;
}


SampleColumn* sample_parse(const std::string& s)
{
    SampleColumn* sc = new SampleColumn();
    sc->x = 1;
    sc->y = 2.0;
    sc->str = s;
    return sc;
}
