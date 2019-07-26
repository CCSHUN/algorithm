#include <iostream>
#include <string.h> //not std::string

namespace std2 {

class string {
public:
    string(const char* ptr = nullptr) {
        size_ = (ptr == nullptr) ? 0 : strlen(ptr);
        if ((ptr_ = new char[size_+1]) == nullptr) {
            throw std::invalid_argument("OOM");
        }
        if (ptr == nullptr) {
            *ptr_ = '\0';
        } else {
            strcpy(ptr_, ptr);
        }
    }
    string(const string& rhs) {
        size_ = rhs.size_;
        if ((ptr_ = new char[size_+1]) == nullptr) {
            throw std::invalid_argument("OOM");
        }
        strcpy(ptr_, rhs.ptr_);
    }
    ~string() {
        delete[] ptr_;
    }
    string& operator= (const string& rhs) {
        if (this == &rhs) {
            return *this;
        }
        string str(rhs);
        std::swap(str.ptr_, ptr_);
        std::swap(str.size_, size_);
        return *this;
    }
    char operator[] (const size_t index) const {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("out of range");
        }
        return *(ptr_+index);
    }
    bool operator== (const string& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (!strcmp(ptr_, rhs.ptr_)) {
            return true;
        }
        return false;
    }
    size_t size() const {
        return size_;
    }
    const char* c_str() const {
        return ptr_;
    }

private:
    friend std::ostream& operator<< (std::ostream& output, const string& rhs);
    friend std::istream& operator>> (std::istream& input, string& rhs);
    friend string operator+ (const string& lhs, const string& rhs);

private:
    char* ptr_;
    size_t size_;
};


string operator+ (const string& lhs, const string& rhs) {//more....
    if (rhs.size() <= 0) {
        return lhs;
    } else if (lhs.size() <= 0) {
        return rhs;
    }
    char* ptr = nullptr;
    size_t size = lhs.size() + rhs.size();
    if ((ptr = new char[size+1]) == nullptr) {
        throw std::invalid_argument("OOM");
    }
    strcpy(ptr, lhs.c_str());
    strcat(ptr, rhs.c_str());
    string str(ptr);
    delete[] ptr;

    return str;
}

std::ostream& operator<< (std::ostream& output, const string& rhs) {
    output << rhs.ptr_;
    return output;
}
std::istream& operator>> (std::istream& input, string& rhs) {
    // TODO
    return input;
}

} //namespace std2

int main(int argc, char const *argv[]) {
    std2::string s1("hello s1");
    std2::string s2("hi s2");
    std2::string s3;
    std::cout << s1 << "   " << s2 << std::endl;//hello s1   hi s2
    s3 = s1 + s2;
    std::cout << s3 << "  " << s3.size() << std::endl;//hello s1hi s2  13
    // s3 += "abcdefg";
    // std::cout << s3 << std::endl;//hello s1hi s2abcdefg
    std::cout << (s3 == s1) << std::endl;//0
    // std::cout << s3.size() << "  "<< s3[1] << std::endl;//e
    s3 = s2;
    std2::string s4(s1);
    std::cout << s3 << "  " << s4 << std::endl;//hi s2  hello s1

    return 0;
}
