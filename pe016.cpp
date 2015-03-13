#include<iostream>
#include <vector>
#include <cmath>
#include <sstream>

#include "pe.h"

template<typename T>
std::string get_reverse_buffer_string(const std::vector<T>& buffer) {
    std::stringstream result;
    for (int i = buffer.size()-1; i>=0; --i) {
        result << buffer[i];
    }
    return result.str();
}

size_t sum_power_digits(size_t base, size_t exponent) {
    size_t result = 0;
    //No native data type large enough for 2^1000
    //Must use container. Might as well use vector
    std::vector<size_t> buffer(1);
    buffer[0] = 1;
    //max_index stores the position of our most significant digit.
    size_t max_index = 0;
    size_t digit = 0;
    size_t x2 = 0;
    size_t sum_next = 0;
    for (size_t e = 1; e <= exponent; ++e) {
        for (size_t i = 0; i <= max_index; ++i) {
            digit = buffer[i];
            x2 = digit * base;
            
            sum_next /=10;
            buffer[i] = x2 % 10 + sum_next %10;
            sum_next += x2;

            if (max_index < i + (sum_next ==0 ? 0 : (size_t)(std::log10(sum_next)))) {
                size_t s = (size_t)(i + std::log10(sum_next));
                max_index = std::max(max_index, s);
                buffer.resize(s+1);
            }
        }
        //std::cout << "2^" << e << ": " << get_reverse_buffer_string(buffer) << std::endl;;
    }
    for (size_t i = 0; i <= max_index; ++i) {
        result += buffer[i];
    }
    return result;
}

class pe016 : public pe_base {
    void run_test() {
        int ans = 1366;
        int value = sum_power_digits(2, 1000);
        check("016", ans, value);
    }
};

int main(int argc, char** argv) {
    pe016 test;
    test.go();
    std::cout << test.get_message() << std::endl; 
    return test.exit_code();
}

