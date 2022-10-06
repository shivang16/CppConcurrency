#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;

class temp{
    private:
        int x;
    public:
        temp(int x=0){
            cout << "inside constructor\n";
            this->x = x;
        }
        void operator()(){
            cout << "inside fuction call operator overloading\n";
        }
        void print(){
            cout << "value of x is: " << x << endl; 
        }
};

int32_t main()
{
    temp t1;
    t1.print();
    temp t2(2);
    t2.print();
    temp t3;
    std::thread t(t3);
    t.join();

}