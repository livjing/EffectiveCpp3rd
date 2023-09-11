// 条款04: 确定对象被使用前已先被初始化
#include <iostream>
#include <string>
#include <list>
using namespace std;

class PhoneNumber
{
    // ...
};

class ABEntry
{
public:
    ABEntry();
    ABEntry(const string &name, const string &address, const list<PhoneNumber> &phones);

private:  // 注意点: 类的成员的初始化顺序是其声明的顺序决定的, 如果有父类 先初始化父类的
    string theName;
    string theAddress;
    list<PhoneNumber> thePhones;
    int numberTimesConsulted;
};

// 在构造函数中赋值
// ABEntry::ABEntry(const string &name, const string &address, const list<PhoneNumber> &phones)
// {
//     // 注意: 以下不是初始化, 而是赋值, 也就是说它们先被初始化过了, 然后在这里又被赋值了, 相当于被操作了2次
//     theName = name;
//     theAddress = address;
//     thePhones = phones;
//     numberTimesConsulted = 0;
// }

// 关于以上更好的性能做法是使用成员初始化列表
 ABEntry::ABEntry(const string &name, const string &address, const list<PhoneNumber> &phones) 
                : theName(name), theAddress(address), thePhones(phones), numberTimesConsulted(0)
{
    // 在这里赋值的变量 由文件或数据库读入 的情况下更好
}

// 无参构造
ABEntry::ABEntry() : theName(), theAddress(), thePhones(), numberTimesConsulted(0){}

int main(int argc, char const *argv[])
{

    cout << "条款04: 确定对象被使用前已先被初始化" << endl;
    return 0;
}

