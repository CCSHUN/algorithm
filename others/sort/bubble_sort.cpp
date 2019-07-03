#include <iostream>
using namespace std;

template<typename T, typename F>
void bubble_sort(T* begin, T* end, F cmp) {
    if (begin >= end-1 || begin == nullptr || end == nullptr)
        return;
    for (T* rear = begin; rear < end; ++rear) {
        bool flag = true;
        for (T* front = end - 1; front > rear; --front) {
            if ( cmp(*(front-1), *front)) {//cmp
                std::swap(*(front-1), *front);
                flag = false;
            }
        }
        if (flag) break;
    }
}

bool compare(int a, int b) {
    return a < b;
}

int main(int argc, char const *argv[]) {
    int test[5] = {4,1,3,0,2};
    bubble_sort(test, test+5, compare);

    for (int i = 0; i < 5; ++i) {
        cout << test[i] << " ";
    }

    cout << endl;

    return 0;
}
