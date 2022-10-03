#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;
int32_t main()
{
    int x = 1;
    cout << "before lambda" << endl;
    std::thread myThread([](int g=10){
        cout << "Inside thread" << endl;
        for(int i=0;i<g;i++)
            cout << i << endl;
    });
    myThread.join();
    // x = 4;
    // cout << "Outside lambda, value of x is: " << x << endl;
    cout << "after lambda" << endl;
}