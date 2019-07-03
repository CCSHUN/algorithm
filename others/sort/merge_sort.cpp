#include <iostream>
using namespace std;

template<typename T, typename F>
void merge_sort2(T* begin, T* end, F cmp) {
    if (begin >= end-1 || begin == nullptr || end == nullptr)
        return;
    int length = end - begin;
    T* mid =  begin + length / 2;
    merge_sort2(begin, mid, cmp);
    merge_sort2(mid, end, cmp);
    //copy g++ -std=c++14 merge_sort.cpp
    auto memory = std::make_unique<T[]>(length);
    T* ptr= begin;
    for (int i = 0; i < length; ++i) {
        memory[i] = *(ptr++);
    }
    T* src = begin;
    int left = 0, memory_mid = length / 2;
    int right = memory_mid, memory_end = length;
    //merge
    for ( ; left < memory_mid && right < memory_end; ++src) {
        *src = cmp(memory[left], memory[right]) ? memory[left++] : memory[right++];
    }
    for ( ; left < memory_mid; ++src) {
        *src = memory[left++];
    }
    for ( ; right < memory_end; ++src) {
        *src = memory[right++];
    }
}

bool compare(int a, int b) {
    return a < b;
}

int main(int argc, char const *argv[]) {
    int test[5] = {4,1,3,0,2};
    merge_sort2(test, test+5, compare);

    for (int i = 0; i < 5; ++i) {
        cout << test[i] << " ";
    }

    cout << endl;

    return 0;
}
