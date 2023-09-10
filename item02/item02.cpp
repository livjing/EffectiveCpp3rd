// 条款02: 尽量以const, enum, inline 替换 #define
#include <iostream>
#include <string>
using namespace std;

// ----------------------------------------------------------------
// 纵横比, 屏幕宽高比 宏一般为全大写
#define ASPECT_RATIO 1.653
// 问题: 编译器由此产生的可能错误 会提到1.653, 不会提到ASPECT_RATIO, 因为它可能在预处理时直接被替换成1.653
// 更糟的是它在一个非你所写在的头文件中

// 替换上面的宏
const double AspectRatio = 1.653;
// ----------------------------------------------------------------
// 字符串
// 1
#define AUTHOR_NAME "Scott Meyers"
// 2
const char * const authorName = "Scott Meyers";
// 3
const std::string AuthorName("Scott Meyers");


// ----------------------------------------------------------------
class GamePlayer{
private:
    // 宏一旦定义, 在它后面编译的都可以看到并使用, 除非使用#undef
    // #define NumTurns 5



    // static const int NumTurns; // 4-正常用法 在此处声明
    // 类的专属常量, 如int,char,bool等,只要不取地址,可以声明并直接使用,无须提供定义
    static const int NumTurns = 5; // 5- 常量声明
    
    // 更好的替代-- 使用枚举
    enum { NumTurns_2 = 5 };

    int scores[NumTurns]; // 常量使用
    int sources_2[NumTurns_2]; // 上面的替代用法
    // ...

};

// const int GamePlayer::NumTurns = 5; // 4-正常用法 在此处定义
const int GamePlayer::NumTurns;  // 5-常量定义, 放在实现文件而非头文件中


// ----------------------------------------------------------------
int f(int num){
    return num;
}

// 使用较大参数,调用函数f
#define CALL_WITH_MAX(a, b) f((a) > (b) ? (a) : (b))

template<typename T>
inline void callWithMax(const T& a, const T& b){
    f(a > b ? a : b);
}

int main(int argc, char const *argv[])
{
    cout << "条款02: 尽量以const, enum, inline 替换 #define" << endl;

    int a = 5, b = 0;
    CALL_WITH_MAX(++a, b); // a = 7, b = 0, 变量a 被加了2次
    cout << "a = " << a << ", b = " << b << endl;

    CALL_WITH_MAX(++a, b + 10); 
    cout << "a = " << a << ", b = " << b << endl; // a = 8, b = 0, , 变量a 被加了1次

    callWithMax(++a, b); // a = 9, b = 0, 因为是引用, 但只会被加1次
    cout << "a = " << a << ", b = " << b << endl;
    callWithMax(++a, b+10); // a = 10, b = 0, 因为是引用, 但只会被加1次
    cout << "a = " << a << ", b = " << b << endl;

    return 0;
}
