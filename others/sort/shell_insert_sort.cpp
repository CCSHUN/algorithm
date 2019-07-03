#include <iostream>
using namespace std;

template<typename T, typename F>
void shell_insert_sort(T* begin, T* end, F cmp) {
    if (begin >= end-1 || begin == nullptr || end == nullptr)
        return;
    for (int d = (end - begin)/2; d > 0; d /= 2) {
        for (T* rear = begin + d; rear < end; ++rear) {
            if ( cmp(*rear, *(rear - d)) ) {//cmp
                T tmp = *rear;
                T* front = rear - d;
                for (; cmp(tmp, *front); front-=d) {
                    *(front+d) = *front;
                }
                *(front+d) = tmp;
            }
        }
    }
}

bool compare(int a, int b) {
    return a < b;
}

int main(int argc, char const *argv[]) {
    int test[5] = {4,1,3,0,2};
    shell_insert_sort(test, test+5, compare);

    for (int i = 0; i < 5; ++i) {
        cout << test[i] << " ";
    }

    cout << endl;

    return 0;
}
