#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>
using namespace std;
// TOPIC: std::lock() In C++11

// It is used to lock multiple mutex at the same time.

// IMPORTANT:
// styntax: std::lock(m1, m2, m3, m4);
// 1. All arguments are locked via a sequence of calls to lock(),  try_lock(), or unlock() on each argument.
// 2. Order of locking is not defined (it will try to lock provided mutex in any order and ensure that
//     there is no dead lock).
// 3. It is a blocking call.


// [Example:0] -- No deadlock.
//     Thread 1                    Thread 2
//     std::lock(m1,m2);           std::lock(m1,m2);

// [Example:1] -- No deadlock. 

//     Thread 1                    Thread 2
//     std::lock(m1, m2);          std::lock(m2, m1);

// [Example:2] -- No deadlock. 

//     Thread 1                    Thread 2
//     std::lock(m1, m2, m3, m4);  std::lock(m3, m4);
//                                 std::lock(m1, m2);

// [Example:3] -- Yes, the below can deadlock. 

//     Thread 1                    Thread 2
//     std::lock(m1,m2);           std::lock(m3,m4);
//     std::lock(m3,m4);           std::lock(m1,m2);

std::mutex m1,m2;
int val = 0;

void task(int t){
    if(t==0){
        while(1){
            std::lock(m1,m2);
            // m1.lock();
            // m2.lock();
            val++;
            cout << "task " << t << " count " << val << endl;
            m2.unlock();
            m1.unlock();
        }
    }else{
        while(1){
            std::lock(m1,m2);
            
            // m2.lock();
            // m1.lock();
            val++;
            cout << "task " << t << " count " << val << endl;
            m1.unlock();
            m2.unlock();
        }
    }
}
int32_t main(){
    std::thread t1(task,0);
    std::thread t2(task,1);
    t1.join();
    t2.join();
}