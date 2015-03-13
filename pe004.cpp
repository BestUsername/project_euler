#include <iostream>
#include <string>
#include <memory>
#include <cmath>

#include "pe.h"

/*
A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/

bool is_pal_brute(int num) {
    bool retval = true;
    std::string text = std::to_string(num);
    //if odd length (eg 12021), no need to compare centre 0 to anything
    int num_digits_check = text.length() / 2;
    for (int index = 0; index < num_digits_check && retval; ++index) {
        if (text[index] != text[text.length()-1-index]) {
            retval = false;
        }
    }
    return retval;
}


std::shared_ptr<std::pair<int, int> >
largest_palindrome_brute(int num_digits) {
    std::shared_ptr<std::pair<int, int> > retval(new std::pair<int,int>());
    if (num_digits > 0) {
        int start = std::pow(10, num_digits - 1);
        int end = std::pow(10, num_digits) - 1;
        int max_product = 0;
        int p1 = 0;
        int p2 = 0;
        int temp = 0;
        for (int i = start; i <= end; ++i) {
            for (int o = start; o <= end; ++o) {
                temp = i * o;
                if (temp > max_product) {
                    if (is_pal_brute(temp)) {
                        p1 = i;
                        p2 = o;
                        max_product = temp;
                    }
                }
            }
        }
        retval->first = p1;
        retval->second = p2;
    }
    return retval;
}

class pe004 : public pe_base {
    void run_test() {
        std::shared_ptr<std::pair<int, int> > solve = largest_palindrome_brute(3);
        int value = solve->first * solve->second;
        check("pe004", 906609, value);
    }
};

int main(int argc, char** argv) {
    pe004 test;
    test.go();
    std::cout << test.get_message() << std::endl; 
    return test.exit_code();
}

