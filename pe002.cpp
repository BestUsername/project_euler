#include <cstdlib>
#include <iostream>

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

int main(int argc, char **argv) {
    std::cout << "Should be 4613732: " << sum_pos_fib<int>(4000000) << std::endl;
    return EXIT_SUCCESS;
}

