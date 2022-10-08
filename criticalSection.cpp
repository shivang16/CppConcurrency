#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>
using namespace std;
int balance = 0;
std::mutex m;
void addBalance(int money){
    std::unique_lock<mutex> ul(m);
    balance+=money;

}
int32_t main(){
    vector <std::thread> v;
    for(int i=1;i<=10;i++){
        std::thread t(addBalance,i*10);
        v.push_back(std::move(t));
    }
    for(int i=0;i<10;i++)
        v[i].join();
    cout << "Final Balance is: " << balance << endl;
}