#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>
#include<future>
#include<shared_mutex>
#include<atomic>
using namespace std;

// class Client{
    std::shared_mutex m1;
    std::condition_variable_any cv;
    string clientName;
    bool isClientInitialised = false; 
    bool isClosed = false;
    // public: 
        // Client(string clientName){
        //     this->clientName = clientName;
        //     isClientInitialised = false;
        //     isClosed = false;
        //     cout << "This is client constructor for client" << this->clientName << endl;
        // }

        void init(){
            std::unique_lock<std::shared_mutex> ul(m1);
            cv.wait(ul,[]{return !isClientInitialised;});
            cout << "Connection initalized for client " << clientName << endl;
            isClientInitialised = true;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            ul.unlock();
            cv.notify_all();       
        }

        void request(int val){
            std::shared_lock <std::shared_mutex> sl(m1);
            cv.wait(sl,[]{return isClientInitialised && !isClosed;});
            cout << "Client " << clientName << " requested " << val << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cv.notify_all();
        }


        void close(){
            std::unique_lock <std::shared_mutex> ul(m1);
            cv.wait(ul,[]{return isClientInitialised &&!isClosed;});
            cout << "Closing the connection for client " << clientName << endl;
            isClosed = true;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }


// };

int32_t main(){
    // Client c1("Shivang");
    // Client c2("Saksham");
    // Client c3("Ashutosh");
    clientName="Shivang";
    vector <std::thread> th;
    for(int i=0;i<30;i++){
        int operationSelector = rand()%4;
        cout << operationSelector << endl;
        if(operationSelector==2){
            std::thread t(init);
             th.push_back(std::move(t));
        }else if(operationSelector==3){
            int val = rand()%100;
            std::thread t(request,val);
             th.push_back(std::move(t));
        }else{
            std::thread t(close);
             th.push_back(std::move(t));
        }
       
    }
    for(int i=0;i<30;i++)
        th[i].join();
    cout << "After operations\n";
}