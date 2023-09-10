// 条款02: 尽量以const, enum, inline 替换 #define
#include <iostream>
#include <string>
using namespace std;

// 纵横比, 屏幕宽高比 宏一般为全大写
#define ASPECT_RATIO 1.653
// 问题: 编译器由此产生的可能错误 会提到1.653, 不会提到ASPECT_RATIO, 因为它可能在预处理时直接被替换成1.653
// 更糟的是它在一个非你所写在的头文件中

// 替换上面的宏
const double AspectRatio = 1.653;

#define AUTHOR_NAME "Scott Meyers"
const char * const authorName = "Scott Meyers";
const std::string AuthorName("Scott Meyers");


class GamePlayer{
private:
    // 宏一旦定义, 在它后面编译的都可以看到并使用, 除非使用#undef
    // #define NumTurns 5
    // 类的专属常量, 如int,char,bool等,只要不取地址,可以声明并直接使用,无须提供定义
    static const int NumTurns = 5; // 常量声明
    int scores[NumTurns]; // 常量使用
    // ...

};

// const int GamePlayer::NumTurns = 5;
const int GamePlayer::NumTurns;  // 常量定义, 放在实现文件而非头文件中


int main(int argc, char const *argv[])
{
    cout << "条款02: 尽量以const, enum, inline 替换 #define" << endl;
    return 0;
}
