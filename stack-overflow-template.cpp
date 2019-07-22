#include <iostream>
using namespace std;

template<int N = 1024>
class Overflow {
private:
    char array[N];
};

int main(int argc, char const *argv[]) {
    
    Overflow<INT_MAX> memory[INT_MAX];

    return 0;
}
