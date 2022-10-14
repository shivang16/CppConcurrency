#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;
class Fun{
    string name;
    public:
        Fun(string name){
            this->name = name;
        }
        void fun1(int n){
            for(int i=0;i<n;i++){
                cout << "Inside function1 for thread: " << name << endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));    
            }
        }
        void fun2(){
            for(int i=0;i<10;i++){
                cout << "Inside function2 for thread " << name << endl;  
                std::this_thread::sleep_for(std::chrono::seconds(1));  
            }
        }
        void operator()(int n){
            cout << "Inside operator for thread " << name << " values " << n << endl;
        }
        void operator()(){
            cout << "Inside operator for thread " << name << endl;
        }
        std::thread fun1Thread(int n){
            return std::thread(&Fun::fun1,this,n);
        }

        std::thread fun2Thread(){
            return std::thread(&Fun::fun2,this);
        }

};
int32_t main()
{
    Fun *f = new Fun("Shivang");
    cout << "main start" << endl;
    std::thread t1 = f->fun1Thread(5);
    std::thread t2 = f->fun2Thread();
    Fun k("Ashutosh");
    std::thread t3 = std::thread(k,3);
    std::thread t4 = std::thread(k);
    t1.join();
    t2.join();
    cout << "after lambda" << endl;
}