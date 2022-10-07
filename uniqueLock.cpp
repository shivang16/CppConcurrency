#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;
// 1. The class unique_lock is a mutex ownership wrapper.
// 2. It Allows:
//     a. Can Have Different Locking Strategies
//     b. time-constrained attempts at locking (try_lock_for, try_lock_until)
//     c. recursive locking
//     d. transfer of lock ownership (move not copy)
//     e. condition variables. (See this in coming videos)
// Locking Strategies
//    TYPE           EFFECTS(S)
// 1. defer_lock  do not acquire ownership of the mutex.
// 2. try_to_lock  try to acquire ownership of the mutex without blocking.
// 3. adopt_lock  assume the calling thread already has ownership of the mutex.

std::mutex m1;
int counter = 0;

void fun1(int val,string thread){
    std::unique_lock <mutex> ul(m1); // This will automatically lock the mutex and unlock will also be done automatically
    for(int i=0;i<val;i++){
        counter++;
        cout << thread << " counter: " << counter << endl;
    }
}

void fun2(int val,string thread){
    std::unique_lock <mutex> ul(m1,std::defer_lock); // Get the ownership but doesnot lock it
    // ul.lock(); // We will have to lock it by our own
    for(int i=0;i<val;i++){
        counter++;
        cout << thread << " counter: " << counter << endl;
    }
}

int32_t main()
{
    std::thread t1(fun2,10,"thread1");
    std::thread t2(fun2,4,"thread2");
    t1.join();
    t2.join();
}