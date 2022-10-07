#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;
int amount = 0;
std::timed_mutex m;
void fun(int i){
    auto now = std::chrono::steady_clock::now();
    if(m.try_lock_for(std::chrono::seconds(1))){
        amount++;
        cout << "lock aquired by " << i << " thread\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        m.unlock(); 
    }else{
        cout << i << " cannot aquire lock\n";
    }
}
int32_t main()
{
    std::thread t1(fun,1);
    std::thread t2(fun,2);
    t1.join();
    t2.join();
    cout << "Final amout is: " << amount;
}