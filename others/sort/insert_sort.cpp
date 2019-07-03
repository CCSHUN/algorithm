#include <iostream>
using namespace std;

template<typename T, typename F>
void insert_sort(T* begin, T* end, F cmp) {
    if (begin >= end-1 || begin == nullptr || end == nullptr)
        return;
    for (T* rear = begin + 1; rear < end; ++rear) {
        if ( cmp(*rear, *(rear - 1)) ) {//cmp
            T tmp = *rear;
            T* front = rear - 1;
            for (; cmp(tmp, *front); --front) {
                *(front+1) = *front;
            }
            *(front+1) = tmp;
        }
    }
}

bool compare(int a, int b) {
    return a < b;
}

int main(int argc, char const *argv[]) {
    int test[5] = {4,1,3,0,2};
    insert_sort(test, test+5, compare);

    for (int i = 0; i < 5; ++i) {
        cout << test[i] << " ";
    }

    cout << endl;

    return 0;
}
