#include <iostream>
#include <mutex>
#include <condition_variable>
#include <list>
#include <atomic>
#include <thread>
#include <functional>
using namespace std;

template<typename T>
class SyncQueue {
public:
    SyncQueue(int capacity) : capacity_(capacity), stoping_(false) {

    }

    void Put(const T& x) {
        Add(x);
    }

    void Put(T&& x) {
        Add(std::forward<T>(x));
    }

    void Take(std::list<T>& list) {
        std::unique_lock<std::mutex> locker(mutex_);
        while (!stoping_ && queue_.empty()) {
            not_empty_.wait(locker);
        }
        if (stoping_) {
            return;
        }
        list = std::move(queue_);
        not_full_.notify_one();
    }

    void Take(T& t) {
        std::unique_lock<std::mutex> locker(mutex_);
        while (!stoping_ && queue_.empty()) {
            not_empty_.wait(locker);
        }
        if (stoping_) {
            return;
        }
        t = queue_.front();
        queue_.pop_front();
        not_full_.notify_one();
    }

    bool Empty() {
        std::lock_guard<std::mutex> locker(mutex_);
        return queue_.empty();
    }

    bool Full() {
        std::lock_guard<std::mutex> locker(mutex_);
        return queue_.size() == capacity_;
    }

    void Stop() {
        {
            std::lock_guard<std::mutex> locker(mutex_);
            stoping_ = true;
        }
        not_empty_.notify_all();
        not_full_.notify_all();
    }


private:
    template<typename F>
    void Add(F&& x) {
        std::unique_lock<std::mutex> locker(mutex_); //lock
        while (!stoping_ && queue_.size() >= capacity_) {
            not_full_.wait(locker); //unlock & lock
        }
        if (stoping_) {
            return;
        }
        queue_.emplace_back(std::forward<F>(x));
        not_empty_.notify_one();
    }

private:
    std::mutex mutex_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
    int capacity_;
    bool stoping_;
    std::list<T> queue_;
};

class ThreadPool {
private:
    using Task = std::function<void()>;

public:
    ThreadPool(int thread_numbers = std::thread::hardware_concurrency(), int capacity = 100) 
        : queue_(capacity) {
        Start(thread_numbers);
    }

    ~ThreadPool() {
        Stop();
    }

    void Stop() {
        std::call_once(once_flag_, [this] { StopThreads(); });
    }

    void AddTask(const Task& task) {
        queue_.Put(task);
    }

    void AddTask(Task&& task) {
        queue_.Put(std::forward<Task>(task));
    }

private:
    void Start(int thread_numbers) {
        running_ = true;
        for (int i = 0; i < thread_numbers; ++i) {
            thread_list_.emplace_back(std::make_shared<std::thread>(std::bind(&ThreadPool::Run, this)));
        }
    }

    void Run() {
        while (running_) {
            std::list<Task> task_list;
            queue_.Take(task_list);
            for (auto& task : task_list) {
                if (!running_) {
                    return;
                }
                task();
            }
        }
    }

    void StopThreads() {
        queue_.Stop();
        running_ = false;
        for (auto thd : thread_list_) {//shared_ptr
            if(thd) {
                thd->join();
            }
        }
        thread_list_.clear();
    }

private:
    SyncQueue<Task> queue_;
    std::list<std::shared_ptr<std::thread>> thread_list_;
    std::atomic_bool running_;
    std::once_flag once_flag_;
};


int main(int argc, char const *argv[]) {
    ThreadPool pool;

    pool.AddTask([] { std::cout << "hello "; });
    pool.AddTask([] { std::cout << "world!" << std::endl; });//flush

    auto task1 = [](int value) { std::cout << value << std::endl; };
    int value = 123; //Parameter passing
    auto task2 = std::bind(task1, value);
    pool.AddTask(task2);

    getchar();

    return 0;
}
