/*************************************************************************
	> File Name: column_test.cpp
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2015年08月11日 星期二 22时47分20秒
    > Describition: 
 ************************************************************************/

#include <iostream>
#include <string>

using namespace std;

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

class SampleColumn 
{
public:
    int x;
    double y;
    string str;

    SampleColumn& parse(const string& s)
    {
        x = 1;
        y = 2.0;
        str = s;
        return *this;
    }
};

int main()
{
    Column<SampleColumn> a("hello, world");
//    cout << a.get_data().x << a.get_data().y << a.get_data().str << endl;
    return 0;
}
