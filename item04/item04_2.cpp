#include <iostream>

using namespace std;

/*
静态对象, 生命周期从构造出来到程序结束为止.
    包含: 全局对象, 命名空间作用域内的对象, 在类内\函数内\文件作用域内被声明为static的对象

    函数内的 static对象: local static object
    其它的 static object, 为 non-local static object

    如果一个源文件中的 non-local static object 初始化时调用了 另一个源文件中的 non-local static object, 可能这个被调用的对象还尚未初始化
    -- 因为c++对于定义在不同的编译单元内的 non-local static object 的初始化顺序并无明确定义
*/



// file1.cpp --------------------------------
class FileSystem{
public:
    // ...
    size_t numDisks() const{
        // ...
    }
    // ...
};
extern FileSystem fs;  //  the file system, 预备给其它程序员使用

// file2.cpp --------------------------------
class Directory{
public:
    Directory(){
        // ...
        size_t disks = fs.numDisks(); // 最大的问题是如何确保tfs先被初始化?
        // ...
    }
    // ...
};
// ----------------------------------------------------------------
// 最大的问题是如何确保tfs先被初始化?
// 解决方案
// 1. 模板隐式具现化 , 但后者也可能也是用模板隐式具现化形成
// 2. 用函数封装返回 non-local static object的引用( 相当于 non-local static object >> local static object), 其实就是后来大名鼎鼎的单例模式

// file3.cpp --------------------------------
class FileSystem2{
public:
    // ...
    size_t numDisks() const{
        // ...
    }
    // ...
};
FileSystem2& tfs(){
    static FileSystem2 fs;
    return fs;
}

// file4.cpp --------------------------------
class Directory2{
public:
    Directory2(){
        // ...
        size_t disks = tfs().numDisks(); // 最大的问题是如何确保tfs先被初始化?
        // ...
    }
    // ...
};
Directory& tempDir(){
    static Directory td;
    return td;
}

// 如果是多线程中, 要确保它们在多线程启用它们前, 先被调用过; 消除与初始化有关的"竞争 race condition"
// 同时避免设计 你中有我, 我中有你的 初始化条件




int main(int argc, char const *argv[])
{

    cout << "条款04: 确定对象被使用前已先被初始化" << endl;
    return 0;
}

