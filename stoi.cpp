#include <iostream>
using namespace std;

namespace std2 {

int stoi(const string& str) {
    if (str.empty()) {
        throw std::invalid_argument(" stoi: no conversion");
    }
    int start = 0;
    while (str[start] == ' ') {//trim
        ++start;
    }
    int neg = 1;
    if (str[start] == '-' || str[start] == '+') {
        neg = (str[start++] == '+') ? 1 : -1;
    }
    if (str[start] < '0' || str[start] > '9') {
        throw std::invalid_argument(" stoi: no conversion");
    }
    int res = 0;
     while (str[start] != '\0') {
        int number = (str[start++] - '0');
        if (res > (INT_MAX - number) / 10) {
            throw std::out_of_range("stoi: out of range");
        }
        if (number >= 0 && number <= 9) {
            res *= 10;
            res += number;
        } else {
            break;
        }
    }

    return neg * res;
}

}

int main(int argc, char const *argv[]) {
    string s = " +01017927394656386203848343456783468 32 ";
    cout << std2::stoi(s) << "   v.s   "<< std::stoi(s) << endl;
    
    return 0;
}
