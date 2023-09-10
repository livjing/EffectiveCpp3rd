// 条款03: 尽可能使用const
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "条款03: 尽可能使用const" << endl;


    char gretting[] = "Hello";
    char* p  = gretting;
    const char* s = gretting;
    char const* s1 = gretting; // equal to 前者, 注意 const的位置是以*为分界点的
    char* const s2 = gretting;
    const char* const s3 = gretting;

    return 0;
}
