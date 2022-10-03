#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;
void fun1(){
    for(int i=0;i<10;i++)
        cout << "Inside function1" << endl;
}
void fun2(){
    for(int i=0;i<10;i++)
        cout << "Inside function2" << endl;
    
}
int32_t main()
{
    cout << "main start" << endl;
    std::thread t1(fun1);
    t1.join();
    std::thread t2(fun2);
    cout << "After t1" << endl;
    t2.join();
    cout << "after lambda" << endl;
}