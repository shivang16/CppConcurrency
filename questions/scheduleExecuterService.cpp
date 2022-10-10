#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>
#include<future>
#include<shared_mutex>
#include<atomic>
using namespace std;

string greet(string name){
    cout << "Inside greet function " <<endl;
    string greetMessage = "Hello " + name+"!!!!";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return greetMessage;
}

class SchedulerExecuterService{
    public: 
        void operator()(std::function<string(string)> fun,int seconds,string s){
            cout << "Scheduler started\n";
            std::this_thread::sleep_for(std::chrono::seconds(seconds));
            cout << "After sleeping for " << seconds << " seconds" << endl;
            std::future<string> f = std::async(std::launch::async,fun,s);
            cout << "Computation is done" << endl;
            string result = f.get();
            cout << "Result of computation: " << result << endl;
        }

};
int32_t main(){
    SchedulerExecuterService ses;
    
    std::thread t1(ses(&greet,1,"Shivang"));
    // ses.schedule(&greet,1,"Shivang");
    t1.join();
    int i=4;
    while(i--)
        cout << "Doing normal task!!";
}