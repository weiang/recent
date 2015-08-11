/*************************************************************************
	> File Name: column.cpp
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2015年08月11日 星期二 22时41分05秒
    > Describition: 
 ************************************************************************/

#include "column.h"
#include <string>

template <typename T>
T& Column<T>::parse(const std::string& s)
{
    return _data.parse(s);
}

template <typename T>
T& Column<T>::get_data()
{
    return _data;
}


