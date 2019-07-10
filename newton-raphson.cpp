#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double origin(double x, int a) {
    return pow(x, 2) - a; //f(x) = x^2 - a
}

double derivative(double x) {
    return 2 * x;         //f'(x) = 2 * x
}

double newton_raphson(double a, double precision = 1e-5, int max_iter_num = 50) {
    if (fabs(a) < precision) {
        return 0.0;
    }

    double x0 = a, x1 = 0.0;

    for (int k = 0; k < max_iter_num; ++k) {
        x1 = x0 - origin(x0, a) / derivative(x0); //newton-raphson
        if (fabs(x1-x0) < precision) {
            break;
        }
        x0 = x1;
    }

    return x1;
}

int main(int argc, char const *argv[]) {
    cout << setiosflags(ios::fixed) << setprecision(3);
    cout << newton_raphson(3) << endl; //1.732050807568877

    return 0;
}
