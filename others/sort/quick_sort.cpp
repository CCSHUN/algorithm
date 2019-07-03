#include <iostream>
using namespace std;

template<typename T, typename F>
void quick_sort(T* begin, T* end, F cmp) {
    if (begin >= end-1 || begin == nullptr || end == nullptr)
        return;

    T* left = begin, *right = end;
    T pivot = *left; //base
    while (left < right) {
        while (left < right && cmp(pivot, *right)) 
            --right;
        *left = *right;
        while (left < right && cmp(*left, pivot))
            ++left;
        *right = *left;
    }
    *left = pivot;

    quick_sort(begin, left - 1, cmp);
    quick_sort(right + 1, end, cmp);
}

bool compare(int a, int b) {
    return a < b;
}

int main(int argc, char const *argv[]) {
    int test[5] = {4,1,3,0,2};
    quick_sort(test, test+5, compare);

    for (int i = 0; i < 5; ++i) {
        cout << test[i] << " ";
    }

    cout << endl;

    return 0;
}
