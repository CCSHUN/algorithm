#include <iostream>
#include <cstdlib>
using namespace std;

int f() {
    double p = 0.7;
    int r = (rand() % 10) + 1;//[1,11)
    return r / 10 > 0.7 ? 1 : 0;
}
/**
 * https://blog.csdn.net/lqglqglqg/article/details/48416413
 */
int g() {
    int a = 0, b = 0;

    while ((a ^ b) != 1) {
        a = f();
        b = f();
    }

    return a > b; //10 = 1, 01 = 0
}

int main(int argc, char const *argv[]) {

    for (int i = 0; i < 20; ++i) {
        cout << g() << endl;
    }

    return 0;
}
