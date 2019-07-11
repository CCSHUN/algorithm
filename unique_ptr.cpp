#include <iostream>

namespace std2 {//namespace std2 begin

template<class T>
struct default_delete {
    void operator()(T* p) const noexcept {
        delete p;
        p = nullptr;
    }
};

template<typename T, typename D = default_delete<T>>
class unique_ptr {
public:
    explicit unique_ptr(T* p, const D& d = D()) noexcept 
        : ptr_(p, d) {
        std::cout << "T" << std::endl;
    }
    ~unique_ptr() {
        reset();
        std::cout << "~T" << std::endl;
    }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
    unique_ptr(unique_ptr&& rhs) noexcept
        : ptr_(rhs.release(), rhs.ptr_.second) {

    }
    unique_ptr& operator=(unique_ptr&& rhs) noexcept {
        if (this != &rhs) {
            reset(rhs.release());
        }
        return *this;
    }

    T& operator*() const noexcept {
        return *ptr_.first;
    }

    T* operator->() const noexcept {
        return ptr_.first;
    }

    T* release() noexcept {
        T* temp_ptr = ptr_.first;
        ptr_.first = nullptr;
        return temp_ptr;
    }

    void reset(T* p = nullptr) noexcept {
        T* temp_ptr = ptr_.first;
        ptr_.first = p;
        if (temp_ptr) {
            ptr_.second(temp_ptr);
        }
    }

    void swap(T& u) noexcept {
        std::swap(ptr_, u);
    }

    T* get() const noexcept {
        return ptr_.first;
    }
    /**
     * operator > < != == , you can see.
     * https://code.woboq.org/appleseed/include/boost/move/unique_ptr.hpp.html#boost::movelib::unique_ptr::pointer_type_obtainer
     */
private:
    std::pair<T*, D> ptr_;
};

/**
 * Partial specialization of class templates to support T[] types
 */
template<typename T>
struct default_delete<T[]> {
    void operator()(T* p) const noexcept {
        delete[] p;
    }
};

template<typename T, typename D>
class unique_ptr<T[], D> {
public:
    explicit unique_ptr(T* p, const D& d = D()) noexcept 
        : ptr_(p, d) {
        std::cout << "T[]" << std::endl;
    }
    ~unique_ptr() {
        reset();
        std::cout << "~T[]" << std::endl;
    }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
    unique_ptr(unique_ptr&& rhs) noexcept
        : ptr_(rhs.release(), rhs.ptr_.second) {

    }
    unique_ptr& operator=(unique_ptr&& rhs) noexcept {
        if (this != &rhs) {
            reset(rhs.release());
        }
        return *this;
    }

    T& operator[](size_t i) const noexcept {
        return ptr_.first[i];//maybe out range index
    }

    T* release() noexcept {
        T* temp_ptr = ptr_.first;
        ptr_.first = nullptr;
        return temp_ptr;
    }

    void reset(T* p = nullptr) noexcept {
        T* temp_ptr = ptr_.first;
        ptr_.first = p;
        if (temp_ptr) {
            ptr_.second(temp_ptr);
        }
    }

    void swap(T& u) noexcept {
        std::swap(ptr_, u);
    }

    T* get() const noexcept {
        return ptr_.first;
    }

private:
    std::pair<T*, D> ptr_;
};
  

template<typename T, typename... Ts>
std2::unique_ptr<T> make_unique(Ts&&... args) {
    return std2::unique_ptr<T>(new T(std::forward<Ts>(args)...));
}

}//namespace std2 end

int main(int argc, char const *argv[]) {
    auto my_int_delete = [] (int* p) { 
        std::cout << "my int delete called" << std::endl; 
        delete p; 
    };

    std2::unique_ptr<int, decltype(my_int_delete)> ptr1{ new int(5) , my_int_delete };
    std::cout << "ptr1 = " << *ptr1 << std::endl;
    
    std2::unique_ptr<int[]> ptr2{ new int[10] };
    ptr2[3] = 9;
    std::cout << "ptr2[3] = " << ptr2[3] << std::endl;

    std2::unique_ptr<int> ptr3{ new int(123) };
    std2::unique_ptr<int> ptr4(std::move(ptr3));
    std2::unique_ptr<int> ptr5 = std::move(ptr4);
    std::cout << "ptr5 = " << *ptr5 << std::endl;

    std2::unique_ptr<int> ptr6 = std2::make_unique<int>(886);
    std::cout << "ptr6 = " << *ptr6 << std::endl;

    return 0;
}


/**
 * $ g++ -std=c++11 unique_ptr.cpp 
 * $ ./a.out
 * http://senlinzhan.github.io/2015/04/20/%E8%B0%88%E8%B0%88C-%E7%9A%84%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88/
 */