#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;
void hello()
{
    std::cout<<"Hello Concurrent World\n";
    
}
int main()
{
   auto start = chrono::steady_clock::now();
    //  Insert the code that will be timed
    std::thread t1(hello);
    t1.join();
    
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    double duration = chrono::duration <double, milli> (diff).count();
    cout << duration << "ms" << endl;
}