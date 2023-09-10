// 条款03: 尽可能使用const
#include <iostream>
#include <string>

using namespace std;

class TextBlock
{
public:
    TextBlock(const std::string s) : text(s) {}
    // ...
    const char &operator[](size_t pos) const
    { // for const 对象
        cout << "call const char& operator[]" << endl;
        // ... 边界检验
        // ... 日志数据访问
        // ... 检验数据完整性
        return text[pos];
    }
    char &operator[](size_t pos)
    { // for non-const 对象
        cout << "call char& operator[]" << endl;
        // ... 边界检验
        // ... 日志数据访问
        // ... 检验数据完整性
        return text[pos];
    }

private:
    string text;
};

class TextBlock2
{
public:
    TextBlock2(const std::string s) : text(s) {}
    // ...
    const char &operator[](size_t pos) const
    { // for const 对象
        // cout << "call const char& operator[]" << endl;
        // ... 边界检验
        // ... 日志数据访问
        // ... 检验数据完整性
        return text[pos];
    }
    char &operator[](size_t pos)
    { // for non-const 对象
        // cout << "call char& operator[]" << endl;

        // return const_cast<char &>((*this)[pos]); // 这样的写法可以吗? 为什么?
        //--- 不行, 因为它会调用自己的non-const版本, 就是递归自己了, 所以要强制转型成调用const版本

        // 这里这样写的目的就是了避免代码重复
        return const_cast<char &>( // 去除 operator[] 返回的 const
            static_cast<const TextBlock2 &>(*this) // 为 *this 加上 const
                [pos]); // 调用 const operator[]
    }

private:
    string text;
};

int main(int argc, char const *argv[])
{
    cout << "条款03: 尽可能使用const" << endl;

    // 一个类的两个成员函数如果只是常量性不同, 也是可以被重载的
    // 现在以上两个重载的函数最大的问题是除了const不同, 其它基本一样, 我们相当于重复写了2次
    // 我们最好的做法应该是一次实现, 2次不同的调用(也就是说应该是一个调用另一个)
    // 方法一: 常量函数调用非常量函数
    // 方法二: 非常量函数调用常量函数

    // TextBlock tb("Hello");
    // cout << tb[0] << endl;
    // tb[0] = 'x'; // 注意: non-const operator[] 能修改成功的原因是返回的 char&
    // cout << tb[0] << endl;

    // const TextBlock ctb("World");
    // cout << ctb[0] << endl;
    // ctb[0] = 'x'; // error, 无法修改一个 const object

    // ----------------------------------------------------------------
    // 方法二: 非常量函数调用常量函数
    TextBlock2 tb("Hello");
    cout << tb[0] << endl;
    tb[0] = 'x'; // 注意: non-const operator[] 能修改成功的原因是返回的 char&
    cout << tb[0] << endl;

    const TextBlock2 ctb("World");
    cout << ctb[0] << endl;
    // ctb[0] = 'x'; // error, 无法修改一个 const object

    // ----------------------------------------------------------------

    // 能使用 方法一: 常量函数调用非常量函数 吗????
    // 最好不要这样, 因为你承诺了不改变任何东西, 但又引进了 non-const, 可以任意修改东西, 违背了初衷

    return 0;
}
