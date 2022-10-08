#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>
using namespace std;
std::mutex m1,m2;
void fun1(){
    m1.lock();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    m2.lock();
    cout << "Critical section of t1\n";
    m2.unlock();
    m1.unlock();
}
void fun2(){
    m2.lock();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    m1.lock();
    cout << "Critical section of t2\n";
    m1.unlock();
    m2.unlock();
}
int32_t main(){
    std::thread t1(fun1);
    std::thread t2(fun2);
    t1.join();
    t2.join();
}