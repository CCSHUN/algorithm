#include <iostream>
using namespace std;

template<typename T, typename F>
T quick_sort_topk(T* begin, T* end, int k, F cmp) {//[begin, end]
    if (begin == nullptr || end == nullptr || cmp == nullptr || k <= 0) {
        throw std::invalid_argument("invalid arg");
    } 

    T* left = begin, *right = end;
    T pivot = *left; //base
    while (left < right) {
        while (left < right && cmp(pivot, *right)) {         
            --right;
        }
        *left = *right;
        while (left < right && cmp(*left, pivot)) {
            ++left;
        }
        *right = *left;
    }
   *left = pivot;
   
    int length = left - begin + 1;
    if (length > k) {
        return quick_sort_topk(begin, left - 1, k, cmp);
    } else if (length < k) {
        return quick_sort_topk(right + 1, end, k-length, cmp);
    } 

    return *left;
}

bool compare(int a, int b) {
    return a < b;
}

int main(int argc, char const *argv[]) {
    int test[6] = {4,1,3,0,2,5};
    int k = 2;
    int res = quick_sort_topk(test, test+5, k,  compare);

    cout << res << endl;

    return 0;
}
