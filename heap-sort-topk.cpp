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
T heap_sort_topk(T* begin, T* end, int k, F cmp) {
    if (begin >= end || begin == nullptr || end == nullptr || cmp == nullptr || k <= 0)
        throw std::invalid_argument("invalid arg");
    int length = end - begin;
    for (int parent = k / 2 - 1; parent >= 0; --parent) {
        adjust_heap(begin, parent, length, cmp);
    }
    for (int next = k; next < length; ++next) {
        if ( cmp(*begin, *(begin+next)) ) {
            std::swap(*begin, *(begin+next));
            adjust_heap(begin, 0, k, cmp);
        }
    }
    return *begin;
}

bool compare(int a, int b) {
    return a < b;
}

int main(int argc, char const *argv[]) {
    int test[6] = {4,1,3,0,2,5};

    int k = 3;

    int res = heap_sort_topk(test, test+6, k,  compare);

    cout << res << endl;

    return 0;
}
