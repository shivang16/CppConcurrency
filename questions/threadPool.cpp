#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>
#include<future>
#include<shared_mutex>
#include<atomic>
using namespace std;
class ThreadPool{
        int workerNodes;
        std::condition_variable workerConditionalVariable;
        std::mutex workerMutex;
        vector <std::thread> threads;
        queue <std::function<void()>> jobQueue;
        bool shouldTerminate;

        void ThreadLoop(){
            while(true){
                std::function <void()> job;
                {
                    std::unique_lock<std::mutex> ul(workerMutex);
                    workerConditionalVariable.wait(ul,[this]{return !q.empty() || shouldTerminate;});
                    job = jobQueue.front();
                    jobQueue.pop();
                }
                job();
            }
        }

    public:
        ThreadPool(int workerNodes=std::thread::hardware_concurrency()){
            this->workerNodes = workerNodes;
            threads.resize(workerNodes);
            
            for(int i=0;i<workerNodes;i++)
                threads[i] = std::thread(threadLoop);

            shouldTerminate = false;
        }


        QueueJob(std::function <void()> &job){
            {
                std::unique_lock<std::mutex> ul(workerMutex);
                jobQueue.push(job);
            }
            workerConditionalVariable.notify_one();
        }

        Stop(){
            {
                std::unique_lock<std::mutex> ul(workerMutex);
                shouldTerminate = true;
            }
            for(int i=0;i<workerNodes;i++)
                threads[i].join();
            threads.clear();
        }


};
int32_t main(){
    
}

// Task queue
// Thread queue