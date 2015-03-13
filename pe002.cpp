#include <iostream>
#include "pe.h"

template<typename ret>
ret sum_pos_fib(ret cap) {
    ret f1 = 0;
    ret f2 = 1;
    ret sum = 0;
    if (cap > 1) {
        for (ret i = f1+f2; i < cap; f1 = f2, f2 = i, i = f1+f2) {
            if (i%2 == 0) {
                sum += i;
            }
        }
    }
    return sum;
}

class pe002 : public pe_base {
    void run_test() {
        check("002", 4613732, sum_pos_fib<int>(4000000));
    }
};

int main(int argc, char** argv) {
    pe002 test;
    test.go();
    std::cout << test.get_message() << std::endl; 
    return test.exit_code();
}

