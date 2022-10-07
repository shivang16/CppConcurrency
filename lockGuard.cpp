#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;
std::mutex m;
int counter = 0;
void fun(int val,string thread){
    //Below line will lock the mutex automatically, which does not require to call unlock
    std::lock_guard <mutex> l(m);
    for(int i=0;i<val;i++){
        counter++;
        cout << thread << " running, counter = " << counter << endl;
    }

}
int32_t main()
{
    std::thread t1(fun,10,"thread1");
    std::thread t2(fun,2,"thread2");
    std::thread t3(fun,5,"thread3");
    t1.join();
    t2.join();
    t3.join();
}