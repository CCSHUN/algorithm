#include <iostream>
#include <cmath>
using namespace std;

bool is_prime(int x) {
    if (x == 2) {
        return true;
    }
    if (x <= 1 || x % 2 == 0) {
        return false;
    }
    for (int number = 3; number <= sqrt(x); number += 2) {
        if (x % number == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char const *argv[]) {
    for (int i = -4; i < 30; ++i) {
        if (is_prime(i)) {
            cout << i <<" ";
        }
    }
    cout << endl;

    return 0;
}
