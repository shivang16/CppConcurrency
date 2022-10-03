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
    std::thread t2 = std::move(t1);
    //If we have t1.join() instead of t2.join() then we will get error because ownership is transfered and now t1 does not hold anything
    // t1.join();
    t2.join();
    t1 = std::thread(fun2);
    t1.join();
    cout << "after lambda" << endl;
}