#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>
#include<future>
#include<shared_mutex>
#include<atomic>
using namespace std;

class BoundedBlockingQueue{
    public:
        deque <int> Q;
        std::mutex m;
        std::condition_variable cv;
        int capacity;
        int sz;
        BoundedBlockingQueue(int capacity){
            //The constructor initializes the queue with a maximum capacity
            this->capacity = capacity;
            sz = 0;
        }

        void enqueue(int element){
            //Adds an element to the front of the queue. If the queue is full, the calling thread is blocked until the queue is no longer full.
            std::unique_lock <std::mutex> ul(m);
            cv.wait(ul,[this](){return sz<capacity});
            Q.push_back(element);
            sz++;
            cv.notify_all();
        }

        int dequeue(){
            //Returns the element at the rear of the queue and removes it. If the queue is empty, the calling thread is blocked until the queue is no longer empty.
            std::unique_lock <std::mutex> ul(m);
            cv.wait(ul,[this](){return sz>0});
            int el = Q.front();
            Q.pop_front();
            sz--;
            cv.notify_all();
            return el;
        } 

        int size(){
            //Returns the number of elements currently in the queue.
            std::unique_lock <std::mutex> ul(m);
            cv.notify_all();
            return sz;
        } 
};
int32_t main(){
    cout << "Before "
}