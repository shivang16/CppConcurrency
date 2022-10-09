#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>
#include<future>
#include<shared_mutex>
using namespace std;

std::shared_mutex m1;
vector <int> DB;
int sz;
int readerSize = 0;
std::condition_variable cv;
void initDB(){
    DB.clear();
    for(int i=0;i<sz;i++){
        DB.push_back(0);
    }
}
bool indChecker(int ind){
    if(ind<0 || ind>=sz){
        cout << "invalid index";
        return false;
    }
    return true;
}
void reader(string reader,int ind){
    if(!indChecker(ind)){
        return;
    }
    m1.lock_shared();
    cout << reader << " is reading value from index: " << ind << " value is: " << DB[ind] << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    m1.unlock_shared();
    
}
void writer(string writer,int val,int ind){
    if(!indChecker(ind)){
        return;
    }
    m1.lock();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout << "Writer: " << writer << " writing value: " << val << " at index: " << ind << endl;
    cout << "Old value: " << DB[ind] << endl;
    DB[ind] = val;
    cout << "new value is: " << DB[ind] << endl;
    m1.unlock();
}
int32_t main(){
    sz = 100;
    initDB();
    vector <std::thread> T;
    for(int i=0;i<100;i++){
        int choose = std::rand()%2;
        int num = std::rand()%100;
        int ind = std::rand()%sz;    
        if(choose==0){
            //reader thread
            string name = "reader"+to_string(num);
            std::thread nt(reader,name,ind);
            T.push_back(std::move(nt));
        }else{
            //Writer thread
            string name = "writer"+to_string(num);
            int val = std::rand()%1000;
            std::thread nt(writer,name,val,ind);
            T.push_back(std::move(nt));
        }
    }
    for(int i=0;i<100;i++)
        T[i].join();
}