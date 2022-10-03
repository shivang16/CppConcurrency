#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;
void hello(){
    cout << "hello";
}
int32_t main()
{
    std::thread t1(hello);
    std::thread t2(hello);
    cout << t1.get_id() << " " << t2.get_id() << endl;
    t1.join();
    t2.join();
}