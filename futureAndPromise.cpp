#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>
#include<future>
using namespace std;
// Basically std::promise is sent to the called thread and once the value is ready 
// we set that value in promise object, now at calling thread side we get that value 
// using std::future object which was created using std::promise object before sending it to the called thread. 
// And this is how we receive value from one thread to another in synchronization.
void getMessage(std::promise<string> &&messagePromise,string name){
    string message = "Hello " +name+"!!";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    messagePromise.set_value(message);
}


int32_t main(){
    std::promise<string> messagePromise;
    std::future<string> messageFuture = messagePromise.get_future();
    string name = "Shivang";
    std::thread t1(getMessage,move(messagePromise),name);
    cout << "Waiting for the result\n";
    cout << "New Message is: " << messageFuture.get() << endl;
    cout << "Completed\n";
    t1.join();

}