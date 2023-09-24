#include <iostream>
using namespace std;

// 目的: 要售卖的房子是独一无二的, 所以我们应该让它不能被拷贝及赋值拷贝
// ----------------------------------------------------------------

class HomeForSale
{
    // ...
};

// 在类中不声明它的copy构造及copy assignment操作符函数 行不行呢?

/*
如果有人尝试使用
HomeForSale h1;
HomeForSale h2;
HomeForSale h3(h1); // 尝试调用 copy
h2 = h1; // 尝试调用 copy assignment

如果你不声明它们, 编译器会偷偷为我们声明
*/

// ----------------------------------------------------------------
/*
防止类被调用copy构造 及 copy assignment操作符
方法1: 把它们声明为private
*/

class HomeForSale_2
{
public:
    friend void friendFunc();

    HomeForSale_2() {}
    ~HomeForSale_2() {}
    // ...

    void memberFunc()
    {
        HomeForSale_2 h1;
        HomeForSale_2 h2;
        HomeForSale_2 h3(h1); // 尝试调用 copy, 报 undefined reference to `HomeForSale_2::HomeForSale_2(HomeForSale_2 const&)
        h2 = h1;              // 尝试调用 copy assignment, 报 undefined reference to `HomeForSale_2::operator=(HomeForSale_2 const&)
                              // 最终 error: ld returned 1 exit status
    }

private:
    // ...
    HomeForSale_2(const HomeForSale_2 &);            // 只声明
    HomeForSale_2 &operator=(const HomeForSale_2 &); // 只声明
};

// 缺点: 它们能在 成员函数 及 友元函数 中被调用,  链接器会报错

void friendFunc()
{
    HomeForSale_2 h1;
    HomeForSale_2 h2;
    //HomeForSale_2 h3(h1); // 尝试调用 copy, 报 undefined reference to `HomeForSale_2::HomeForSale_2(HomeForSale_2 const&)
    //h2 = h1;              // 尝试调用 copy assignment, 报 undefined reference to `HomeForSale_2::operator=(HomeForSale_2 const&)
                          // 最终 error: ld returned 1 exit status
}

// ----------------------------------------------------------------
/*
如何让 链接期错误 转移至 编译期呢?  (越早越好)

-- 将本身类中的定义的私有 copy 及 copy assignment 转移到 它的基类中
*/

class Uncopyable
{
protected:
    // 允许它的派生类构造及析构
    Uncopyable() {}
    ~Uncopyable() {}

private:
    // 不允许它的派生类 copy 及 copy assignment
    Uncopyable(const Uncopyable &);
    Uncopyable &operator=(const Uncopyable &);
};

class HomeForSale_3 : public Uncopyable
{
    // ...

    // 这里我们不再需要声明私有的copy 及 copy assignment
};


// ----------------------------------------------------------------
// c++11 使用delete
class HomeForSale_4
{
    // ...

private:
    HomeForSale_4(const HomeForSale_4 &) = delete;
    HomeForSale_4 &operator=(const HomeForSale_4&) = delete;
};

int main(int argc, char const *argv[])
{

    // HomeForSale h1;
    // HomeForSale h2;
    // HomeForSale h3(h1); // 尝试调用 copy, 成功
    // h2 = h1;            // 尝试调用 copy assignment, 成功
    // 编译器会偷偷为我们声明它们

    // ----------------------------------------------------------------
    // HomeForSale_2 h1;
    // HomeForSale_2 h2;
    // HomeForSale_2 h3(h1); // 尝试调用 copy, 报调用不可访问
    // h2 = h1;              // 尝试调用 copy assignment, 报调用不可访问

    // HomeForSale_2 h;
    // h.memberFunc();

    // friendFunc(); // 错误结果和调用 memberFunc() 一样

    // ----------------------------------------------------------------
    HomeForSale_3 h1;
    HomeForSale_3 h2;
    // HomeForSale_3 h3(h1); // 尝试调用 copy, 报 隐式声明私有, 是已删除的函数
    // h2 = h1;              // 尝试调用 copy assignment, 报 隐式声明私有, 是已删除的函数

    return 0;
}
