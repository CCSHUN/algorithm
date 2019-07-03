#include <iostream>
using namespace std;

template<typename T, typename F>
void select_sort(T* begin, T* end, F cmp) {
    if (begin >= end-1 || begin == nullptr || end == nullptr)
        return;
    for (T* rear = begin; rear < end; ++rear) {
        T* select = rear;
        for (T* front = rear+1; front < end; ++front) {
            if ( cmp(*front, *select) ) //cmp
                select = front;
        }
        std::swap(*select, *rear);
    }
}

bool compare(int a, int b) {
    return a < b;
}

int main(int argc, char const *argv[]) {
    int test[5] = {4,1,3,0,2};
    select_sort(test, test+5, compare);

    for (int i = 0; i < 5; ++i) {
        cout << test[i] << " ";
    }

    cout << endl;

    return 0;
}
