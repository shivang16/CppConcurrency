#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>
using namespace std;
// NOTES:
// 1. Condition variables allow us to synchronize threads via notifications.
//    a. notify_one();
//    b. notify_all();
// 2. You need mutex to use condition variable
// 3. Condition variable is used to synchronize two or more threads.
// 4. Best use case of condition variable is Producer/Consumer problem.
// 5. Condition variables can be used for two purposes:
//     a. Notify other threads
//     b. Wait for some condition

std::mutex m1;
int balance = 0;
std::condition_variable cv;
void printBalance(){
    cout << "Your current balance is: " << balance <<endl;
}
void addMoney(int amount){
    std::unique_lock <mutex> ul(m1);
    cout << "Adding " << amount << " to balance\n";
    balance+=amount;
    cv.notify_one();
    printBalance();
}

void withDrawMoney(int amount){
    std::unique_lock <mutex> ul(m1);
    cv.wait(ul,[] {return balance==0 ? false:true;});
    if(amount>balance)
        cout << "Money can't be withdrawn since amount is less than balance\n";
    else{
        balance-=amount;
        cout << "Money with drawn\n";
    }
    printBalance();
}
int32_t main(){
    std::thread t1(withDrawMoney,100);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::thread t2(addMoney,200);
    t1.join();
    t2.join();
}