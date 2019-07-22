#include <iostream>
using namespace std;
/**
 * 得出结论：
 * - 栈空间地址  高->低
 * - 堆空间地址  低->高
 * - 这个可能不是一定的，应该是CPU架构、操作系统有关
 * 
 * new int[1] 消耗的空间并不是4字节（事实上是10字节），应该还要维护数组信息。
 */
void pass() {
    int temp = 0;
    int* ptr = &temp;
    while (*ptr != 222) {
        ++ptr;
    }
    *ptr = 333;
}

int main(int argc, char const *argv[]) {
    int x = 222;

    cout << x << endl;
    pass();
    cout << x << endl;

    return 0;
}
