#include <iostream>
#include <string>
using namespace std;

constexpr int line = 10;
constexpr int buffer_size = 16;

bool tail2(char const* file_name) {
    if (file_name == nullptr) {
        throw std::invalid_argument("file name is null");
    }
    FILE* fp = fopen(file_name, "r");
    if (fp == nullptr) {
        throw std::invalid_argument("open file fail");
    }
    fseek(fp, -1, SEEK_END);
    
    int count = 0;
    while (true) {
        if (fgetc(fp) == '\n') {
            ++count;
        }
        if (count > line) {
            break;
        }
        if (fseek(fp, -2, SEEK_CUR) != 0) {
            fseek(fp, 0, SEEK_SET);
            break;
        }
    }

    char buffer[buffer_size];
    while (!feof(fp)) {
        if (fgets(buffer, buffer_size, fp)) {
            cout << buffer;
        }
    }

    fclose(fp);
    return true;
}

int main(int argc, char const *argv[]) {
    tail2("/Users/qingdujun/Work.localized/haha/algorithm/tail2.cpp");
    return 0;
}