class DiningPhilosophers {
private:
    mutex m;
    condition_variable c;
    vector<bool> forks;
    
public:
    DiningPhilosophers() {
        for(int i = 0; i < 5; i++){
            forks.push_back(true);
        }
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        {
            unique_lock<mutex> ul(m);
            c.wait(ul, [this, philosopher](){
                return forks[philosopher] && forks[(philosopher + 1) % 5]; 
            });
            
            pickLeftFork();
            pickRightFork();
            
            forks[philosopher] = false;
            forks[(philosopher + 1) % 5] = false;
        }
        
        eat();
        
        {
            lock_guard<mutex> lg(m);
            
            putLeftFork();
            putRightFork();
            
            forks[philosopher] = true;
            forks[(philosopher + 1) % 5] = true;
        }
        c.notify_all();
    }
};