#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;
int32_t main()
{
    //This tells how many concurrent threads our machine can support
    cout << std::thread::hardware_concurrency() << endl;
}