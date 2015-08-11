/*************************************************************************
	> File Name: main.cpp
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2015年08月11日 星期二 22时15分09秒
    > Describition: 
 ************************************************************************/

#include <iostream>
#include "sample_column.h"
#include "column.h"

using namespace std;

int main()
{
    Column* c = sample_parse(string("abc"));
//    cout << (*(c->get_data())).x << (*(c->get_data())).y << (*(c->get_data())).str << endl; 
    (c->get_data())->x;
    return 0;
}
