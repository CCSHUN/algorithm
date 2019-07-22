#include <iostream>
#include <signal.h> //SIGINT
#include <unistd.h> //sleep()
using namespace std;
/**
 * https://feichashao.com/mask_signal/
 */
void ctrl_c(int x) {
    cout << "will be killed" << endl;
}

int main(int argc, char const *argv[]) {
    // signal(SIGINT, SIG_IGN);
    signal(SIGINT, ctrl_c);

    sleep(10);

    return 0;
}
