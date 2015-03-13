#include <iostream>
#include "pe.h"

int sum_multi(int x1, int x2, int ceiling) {
    int sum = 0;
    bool use1 = true;
    bool use2 = true;
    if (x1 == 0 || x1 >= ceiling) {
        use1 = false;
    }
    if (x2 == 0 || x2 >= ceiling || x2 == x1) {
        use2 = false;
    }
    if (ceiling > 0 && (use1 || use2)) {
        for (int i = 0; i < ceiling; ++i) {
            if ((use1 && i % x1 == 0) || (use2 && i %x2 == 0)) {
                sum += i;
            }
        }
    }
    return sum;
}

class pe001 : public pe_base {
    void run_test() {
        check("001", 233168, sum_multi(3,5,1000));
    }
};

int main(int argc, char** argv) {
    pe001 test;
    test.go();
    std::cout << test.get_message() << std::endl; 
    return test.exit_code();
}

