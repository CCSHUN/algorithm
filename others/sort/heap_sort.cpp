#include <iostream>
using namespace std;

template<typename T, typename F>
void adjust_heap(T* begin, int parent, int length, F cmp) {
    T tmp = *(begin + parent);
    for (int child = 2 * parent + 1; child < length; child = 2 * parent + 1) {
        if (child+1 < length && cmp(*(begin+child+1), *(begin+child)))
            ++child;
        if (cmp(tmp, *(begin+child)))
            break;
        *(begin+parent) = *(begin+child);
        parent = child;
    }
    *(begin+parent) = tmp;
}

template<typename T, typename F>
void heap_sort(T* begin, T* end, F cmp) {
    if (begin >= end-1 || begin == nullptr || end == nullptr)
        return;
    int length = end - begin;
    for (int parent = length / 2 - 1; parent >= 0; --parent) {
        adjust_heap(begin, parent, length, cmp);
    }
    for (int last = length - 1; last > 0; --last) {
        std::swap(*(begin+last), *begin);
        adjust_heap(begin, 0, last, cmp);
    }
}

bool compare(int a, int b) {
    return a > b;
}

int main(int argc, char const *argv[]) {
    int test[6] = {4,1,3,0,2,5};
    heap_sort(test, test+6, compare);

    for (int i = 0; i < 6; ++i) {
        cout << test[i] << " ";
    }

    cout << endl;

    return 0;
}
