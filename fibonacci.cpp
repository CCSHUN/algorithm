#include <iostream>
using namespace std;
/**
 * 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ...
 */
int fibonacci(int n) {
    if (n < 2) {
        return 1;
    }

    int f1 = 1, f2 = 1, res = 0;

    for (int i = 3; i < n; ++i) {
        f1 += f2;//f3,f5
        f2 += f1;//f4,f6
    }

    res = (n % 2 == 0) ? f2 : f1;

    return res;
}

int main(int argc, char const *argv[]) {
    cout << fibonacci(4) << endl;
    cout << fibonacci(6) << endl;
    cout << fibonacci(13) << endl;
    
    return 0;
}
