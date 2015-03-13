#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <memory>

#include "pe.h"

/*
   2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

   What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/

template<typename one, typename two>
void display_map(const std::map<one, two> &map) {
    std::cout << "Map contains:" << std::endl;
    for (const std::pair<one, two> o : map) {
        std::cout << "\t" << o.first << ": " << o.second <<std::endl; 
    }
}

std::shared_ptr<std::map<int, int> > prime_factorize( int num ) {
    std::shared_ptr< std::map<int, int> > prime_factors_ptr(new std::map<int,int>());
    for (int prime = 2; prime <= num; ++prime) {
        int prime_count = 0;
        while (num % prime == 0) {
            num /= prime;
            ++prime_count;
        }
        if (prime_count > 0) {
            (*prime_factors_ptr)[prime] = prime_count;
        }
    }
    return prime_factors_ptr;
}

int get_lowest_common_product( const std::vector<int> &values ) {
    int lcp = 1;
    
    std::map<int, int> prime_factors_tally;
    for (int i : values) {
        std::shared_ptr<std::map<int, int> > result = prime_factorize(i);
        for (std::pair<int, int> o : *result) {
           prime_factors_tally[o.first] = std::max(o.second, prime_factors_tally[o.first]);
        }
    }
    
    for (std::pair<int, int> i : prime_factors_tally) {
        lcp *= std::pow(i.first, i.second);;
    }
    return lcp;
}

class pe005 : public pe_base {
    void run_test() {
        std::vector<int> values {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
        int ans = 232792560;
        int result = get_lowest_common_product(values);
        check("005", ans, result);
    }
};

int main(int argc, char** argv) {
    pe005 test;
    test.go();
    std::cout << test.get_message() << std::endl; 
    return test.exit_code();
}

