#include <string>
#include <iostream>

int size = 4;

void func(std::string && str, int N, int zero, int one) {
    if ( zero > one && str.length() == size ) {
        if ( str.length() == size)
            std::cout << str << "\n";
        return ;
    }

    if ( N == 0 && str.length() == size) {
        std::cout << str << "\n";
        return ;
    }

    func(str + "0", N - 1, zero + 1, one);
    func(str + "1", N - 1,zero, one + 1);
}

int main(void) {
    func("1", size, 0, 0);
}