// 条款03: 尽可能使用const
#include <iostream>
#include <string>

using namespace std;


class TextBlock{
public:
    TextBlock(const std::string s) :  text(s){}
    // ...
    const char& operator[](size_t pos) const {  // for const 对象
        cout << "call const char& operator[]" << endl;
        return text[pos];
    }
    char& operator[](size_t pos){ // for non-const 对象
        cout << "call char& operator[]" << endl;
        return text[pos];
    }

private:
    string text;
};

int main(int argc, char const *argv[])
{
    cout << "条款03: 尽可能使用const" << endl;

    // 一个类的两个成员函数如果只是常量性不同, 也是可以被重载的
    TextBlock tb("Hello");
    cout << tb[0] << endl;

    const TextBlock ctb("World");
    cout << ctb[0] << endl;


    return 0;
}



