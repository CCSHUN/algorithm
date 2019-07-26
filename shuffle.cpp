#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h> //sleep
using namespace std;

template <typename T>
void shuffle(const vector<T>& data, vector<T>& res) {
    if (data.empty()) {
        return;
    }
    res.assign(data.begin(), data.end());
    std::srand(std::time(nullptr)); 
    for (int i = 1; i < data.size(); ++i) {
        int number = std::rand() % i;
        res[i] = res[number];
        res[number] = data[i];
    }
}

template <typename T>
void shuffle(vector<T>& data) {
    if (data.empty()) {
        return;
    }
    std::srand(std::time(nullptr)); 
    for (int i = 1; i < data.size(); ++i) {
        int number = std::rand() % i;
        std::swap(data[i], data[number]);
    }
}

int main(int argc, char const *argv[]) {
    vector<int> data = {1,2,3,4,5,6,7,8,9,0};
    vector<int> res;
    shuffle(data, res);

    for (auto v : res) {
        cout << v << " ";
    }

    sleep(1); // std::srand(std::time(nullptr)); 
    cout << endl;
    shuffle(data);

    for (auto v : data) {
        cout << v << " ";
    }

    return 0;
}
