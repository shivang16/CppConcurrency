#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;
std::recursive_mutex m1;
void recursion(int count,string thread){
    if(count<=0){
        return;
    }
    else{
        m1.lock();
        cout << thread << " is running and locked, count= " << count << endl;
        recursion(count-1,thread);
        m1.unlock();
        cout << thread << " unlocked" << endl;
    }
}
int32_t main()
{

    cout << "This is an example of recursive mutex\n";
    std::thread t1(recursion,4,"thread1");
    std::thread t2(recursion,5,"thread2");
    t1.join();
    t2.join();
}