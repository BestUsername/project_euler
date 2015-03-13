#include <iostream>
#include <memory>
#include <vector>

#include "pe.h"

/*
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/
typedef long long type;
//since we know the full range of primes, we can use a sieve
type get_primes_sum_under_faster(int n) {
    std::shared_ptr<std::vector<bool> > sieve(new std::vector<bool>(n, true));
    type sum = 0;
    //for first prime 2
    int offset = 2;
    for (int num = offset; num < n; ++num) {
        if (sieve->at(num-offset)) {
            sum+=num;
            //std::cout << "Found prime: " << num << " giving sum: " << sum << std::endl;
            for (int o = num; o < n; o+=num) {
                //remove all multiples of this prime from the sieve
                sieve->at(o-offset) = false;
            }
        }
    }
    return sum;
}

//slow brute-force method
type get_primes_sum_under_slow(int n) {
    //convert N to positive
    const unsigned int num = std::abs(n);
    //initialize return value with funky prime 2
    std::shared_ptr<std::vector<int> > retval(new std::vector<int>({2}));
    //initialize the sum to include 2
    type sum = 2;
    //early cut-off
    if (num <=1 ) {
        retval->resize(num);
    } else {
        // flag is set if a number is found to be divisible by any of the previous primes for early exit
        bool flag = false;
        //starting at 3 because we already have 2 in the primes vector
        //stepping by two to save checking any evens
        for (unsigned int i = 3; i < num; i+=2) {
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
                sum += i;
                //std::cout << "Found prime: " << i << " giving total: " << sum << std::endl; 
            } else {
                flag = false;
            }

        }
    }
    return sum;
}

class pe010 : public pe_base {
    void run_test() {
        type ans = 142913828922;
        type value = get_primes_sum_under_faster(2000000);
        check("010", ans, value);
    }
};

int main(int argc, char** argv) {
    pe010 test;
    test.go();
    std::cout << test.get_message() << std::endl; 
    return test.exit_code();
}
