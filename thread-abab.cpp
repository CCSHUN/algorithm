#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
using namespace std;

class Abab {
public:
    Abab() : b_check_(false) {

    }

    void printA() {
        std::unique_lock<std::mutex> locker(mutex_);
        while (b_check_) {
            a_.wait(locker);
        }
        cout << "a";
        b_check_ = true;
        b_.notify_one();
    }

    void printB() {
        std::unique_lock<std::mutex> locker(mutex_);
        while (!b_check_) {
            b_.wait(locker);
        }
        cout << "b";
        b_check_ = false;
        a_.notify_one();
    }

private:
    std::condition_variable a_;
    std::condition_variable b_;
    std::mutex mutex_;
    bool b_check_;
};

int main(int argc, char const *argv[]) {
    Abab ab;

    thread t1([&ab] {
        for (int i = 0; i < 20; ++i) {
            ab.printA();
        }
    });

    thread t2([&ab] {
        for (int i = 0; i < 20; ++i) {
            ab.printB();
        }
    });

    t1.join();
    t2.join();

    cout << endl;

    return 0;
}
