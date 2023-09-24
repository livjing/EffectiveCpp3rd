#include <iostream>

using namespace std;

class Empty_0
{
};

// 一个空类 编译器会做什么?

// 默认生成的都是 public and inline
class Empty_1
{
public:
    Empty_1() {}                     // 构造
    Empty_1(const Empty_1 &other) {} // 拷贝构造
    ~Empty_1() {}                    // 析构

    Empty_1 &operator=(const Empty_1 &other) {} // 拷贝赋值
};
// 注意点:
/*
1. 自动生成的析构都是非虚的, 除非基类有虚析构
2. copy构造和copy assignment操作符, 编译器只会将non-static成员变量拷贝到目标对象
3. 只要你自己声明了一个构造函数,编译器就不会再创建默认的构造函数了
*/

// 引用所指向的对象不能更换, 只能修改这个指向的对象的值
template <class T>
class NamedObject
{
public:
    // ...
    NamedObject(std::string &name, cosnt T &value) : nameValue(name), objectValue(value)
    {
    }
    // ...

private:
    std::string &nameValue;
    const T objectValue;
};

int main(int argc, char const *argv[])
{
    cout << "条款05: 了解c++默默编写并调用哪些函数" << endl;

    Empty_1 e1;     // 默认构造
    Empty_1 e2(e1); // 拷贝构造
    e2 = e1;        // 拷贝赋值

    std::string newDog("Persephone");
    std::string oldDog("Satch");
    NamedObject<int> p(newDog, 2);
    NamedObject<int> s(oldDog, 36);

    // p = s; // 无法修改引用指向对象, 也无法修改 const的值

    return 0;
}
