#include <iostream>
using namespace std;

void hannoi(int n, char from, char buffer, char to) {
    if (n == 0)
        return;
    hannoi(n-1, from, to, buffer);//move n-1 disk to buffer
    cout << "Move disk " << n << " from " << from << " to " << to << endl;
    hannoi(n-1, buffer, from, to);
}

int main(int argc, char const *argv[]) {
    int n = 0;
    cin >> n;
    hannoi(n, 'A', 'B', 'C');

    return 0;
}
