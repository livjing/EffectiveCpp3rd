// 条款03: 尽可能使用const
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "条款03: 尽可能使用const" << endl;


    ////////////////////////////////
    // ----------------------------------------------------------------
    // 迭代器的作用像 T*
    // 迭代器的T* const 表示这个迭代器不得指向不同的东西, 但它所指向的东西的值是可以修改的
    // 如果希望迭代器所指的东西也不能修改值(类似 const T * 指针), 请使用 const_iterator

    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    for (int i = 0; i < vec.size(); ++i){  // 1 2 3
        cout << vec[i] << " ";
    }
    cout << endl;  

    const vector<int>::iterator it = vec.begin();  // it 相等于 T* const
    *it = 10; // 能修改指向的东西的值
    //++it; // error, it是cosnt

    for (int i = 0; i < vec.size(); ++i){ // 10 2 3
        cout << vec[i] << " ";
    }
    cout << endl;

    vector<int>::const_iterator cit = vec.cbegin(); // const T*
    // *cit = 20; // error, it 不能修改指向的东西的值
    cout << *cit << endl; // 10
    ++cit;
    cout << *cit << endl; // 2

    return 0;
}

