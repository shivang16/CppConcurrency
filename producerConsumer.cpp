#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>
#include<future>
using namespace std;
std::mutex m;
queue <pair<string,int>> Q;
std::condition_variable cv;
void producer(int val,string name){
    while(val>=0){
        std::unique_lock<mutex> l(m);
        cout << "Producer " << name << " is producing\n";
        val--;
        int num = rand();
        cout << "value produced is: " << num << endl;
        Q.push({name,num});
        l.unlock();
        cv.notify_all();
    }
}
void consumer(){
    while(true){
            std::unique_lock<mutex> l(m);
            cv.wait(l,[]{return Q.empty()?false:true;});
            cout << "Consuming value produced by " << Q.front().first << " value consumed = " << Q.front().second << endl;
            Q.pop();
            l.unlock();
    }
}

int32_t main(){
    int val1 = 10,val2=20,val3=5;
    std::thread p1(producer,val1,"Shivang");
    std::thread p2(producer,val2,"Ashutosh");
    std::thread p3(producer,val3,"Saksham");
    std::thread c(consumer);
    p1.join();
    p2.join();
    p3.join();
    c.join();
}