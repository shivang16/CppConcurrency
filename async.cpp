#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>
#include<future>
using namespace std;
// DESCRIPTION :
// Here we will learn std::async and its usage like how to create task. There are three different launch policy for creating task using std::async are as follows:
// 1. std::launch::async
// 2. std::launch::deffered
// 3. std::launch::async | std::launch::deffered

int fun(int val){
    cout << "Inside function\n";
    int newVal = val*1000;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return newVal;
}

int32_t main(){
    cout << "Inside main\n";
    int val = 20;
    cout << "Initial value is: " << val << endl;
    // std::future<int> messageFuture = std::async(std::launch::deferred,fun,val);
    std::future<int> messageFuture = std::async(std::launch::async,fun,val);
    cout << "Waiting for output\n";
    int newVal = messageFuture.get();
    cout << "new value is: " <<newVal << endl;
    cout << "Completed!!\n";
}