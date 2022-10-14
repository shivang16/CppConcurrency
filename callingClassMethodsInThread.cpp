#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;
class Fun{
    public:
        void fun1(){
        for(int i=0;i<10;i++)
            cout << "Inside function1" << endl;
        }
        void fun2(){
            for(int i=0;i<10;i++)
                cout << "Inside function2" << endl;    
        }

        void operator ()(int selector){
            if(selector==1){
                fun1();
            }else{
                fun2();
            }
        }
        ~Fun(){
            
        }

};
int32_t main()
{
    // Fun f;
    cout << "main start" << endl;
    std::thread t1(&Fun::fun1);
    std::thread t2(&Fun::fun2);
    t1.join();
    t2.join();
    cout << "after lambda" << endl;
}