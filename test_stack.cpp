#include <iostream>
#include "stack.hpp"

using namespace std;

int main()
{
    stack<int> s1;

    s1.Push(1);
    s1.Push(2);
    s1.Push(3);

    cout << s1 << endl;         // Ожидается: 3->2->1
    cout << s1.Size() << endl;
    
    stack<int> s2 (s1), s3;

    s1.Pop();
    s1.Push(4);
    s1.Push(5);
    
    s2.Pop();
    s2.Push(6);

    cout << s1 << endl;         // Ожидается: 5->4->2->1
    cout << s1.Size() << endl;
    
    cout << s2 << endl;         // Ожидается: 6->2->1
    cout << s2.Size() << endl;
    
    s3 = s1;   // Копирующее присваивание
    
    s1.Pop();
    s1.Push(7);
    s1.Push(8);
    
    s3.Pop();
    s3.Push(9);

    cout << s1 << endl;         // Ожидается: 8->7->4->2->1
    cout << s1.Size() << endl;
    
    cout << s2 << endl;         // Ожидается: 6->2->1
    cout << s2.Size() << endl;
    
    cout << s3 << endl;         // Ожидается: 9->4->2->1
    cout << s3.Size() << endl;

    return 0;
}

