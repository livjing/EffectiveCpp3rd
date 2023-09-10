// 条款03: 尽可能使用const
#include <iostream>
#include <string>
#include <cstring>

using namespace std;


class TextBlock{
public:
    TextBlock(const char* s) { strcpy(pText, s); }
    // ...

    char& operator[](size_t pos) const { 
        cout << "call char& operator[]" << endl;
        return pText[pos];
    }

    size_t length() const {

        if (!lengthIsValid){ 
            textLength = strlen(pText);// error: 在 const成员函数 中不能赋值成员变量, 解决方案只要在想要经常改变的成员变量前加上mutable
            lengthIsValid = true;// error: 在 const成员函数 中不能赋值成员变量, 解决方案只要在想要经常改变的成员变量前加上mutable
        }
        return textLength;
    }

private:
    char* pText;
    //size_t textLength; // 最近一次的文本长度
    //bool lengthIsValid; // 目前的长度是否有效
    mutable size_t textLength;
    mutable bool lengthIsValid;
};



int main(int argc, char const *argv[])
{
    cout << "条款03: 尽可能使用const" << endl;


    const TextBlock ctb("World"); // const object 本意不想被改变
    char* pc = &ctb[0];
    cout << *pc << endl;
    *pc = 'J';  // 但通过指针仍然被改变了
    cout << *pc << endl;

    

    return 0;
}



