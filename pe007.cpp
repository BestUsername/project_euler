#include <iostream>
#include <vector>
#include <memory>

#include "pe.h"

/*
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10 001st prime number?
*/

std::shared_ptr<std::vector<int> >
get_nth_prime(int n) {
    //convert N to positive
    const unsigned int num = std::abs(n);
    //initialize return value with funky prime 2
    std::shared_ptr<std::vector<int> > retval(new std::vector<int>({2}));
    if (num <=1 ) {
        retval->resize(num);
    } else {
        // flag is set if a number is found to be divisible by any of the previous primes for early exit
        bool flag = false;
        //starting at 3 because we already have 2 in the primes vector
        //stepping by two to save checking any evens
        for (int i = 3; retval->size() < num; i+=2) {
            //Because we want to avoid checking /2, initialize an iterator to the 2nd element
            for (std::vector<int>::iterator it = retval->begin() + 1; it != retval->end() && !flag; ++it) {
                // if find a divisor, then this number isn't prime and stop checking
                if (i % *it == 0) {
                    flag = true;
                }
            }
            //if the flag hasn't been set after running through the current primes vector, then this number is also a prime
            if (!flag) {
                retval->push_back(i);
            } else {
                flag = false;
            }

        }
    }
    return retval;
}

class pe007 : public pe_base {
    void run_test() {
        int ans = 104743;
        std::shared_ptr<std::vector<int> > primes = get_nth_prime(10001);
        //for this purpose we're only interested in the last prime
        int value = primes->back();
        check("007", ans, value);
    }
};

int main(int argc, char** argv) {
    pe007 test;
    test.go();
    std::cout << test.get_message() << std::endl; 
    return test.exit_code();
}

