// 条款03: 尽可能使用const
#include <iostream>
#include <vector>

using namespace std;



class Rational{
    // ...
};
const Rational operator* (const Rational& lhs, const Rational& rhs);



int main(int argc, char const *argv[])
{
    cout << "条款03: 尽可能使用const" << endl;


    Rational a, b, c;

    //  要有 operator= 操作符重载
    (a*b) = c; 

    //  要有 operator= 操作符重载
    if (a*b = c) // if (a*b == c)

    // 一个类的两个成员函数如果只是常量性不同, 也是可以被重载的



    return 0;
}



