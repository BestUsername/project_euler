#include <iostream>
#include <map>
#include <new>

#include "pe.h"

/**
  Kinda works, but runs out of memory super fast
  */
int dumb_collatz(int value, size_t counter)
{
    int retval = 0;
    if (value == 1) {
        retval = counter+1;
    } else {
        int nextval;
        if (value % 2 == 0) {
            nextval = value / 2;
        } else {
            nextval = value *3 + 1;
        }
        retval = dumb_collatz(nextval, counter+1);
    }
    //std::cout << counter << ": " << value << std::endl;
    return retval; 
}

//use a list for pre-emptive termination.
template <typename T>
T leaner_collatz(std::map<T, T> & lengths, size_t value, T counter) {
    T ret_val;
    T current = lengths[value];
    if (value <=1) {
        //reached 1, chain ends here.
        ret_val = counter;
    } else if (current !=0) {
        //we've reached a pre-computer chain. Tack on the cached value
        ret_val = counter + current;
    } else if (value %2==0) {
        //we've reached a non-computed chain start.
        //dig deeper using the even path
        ret_val = leaner_collatz(lengths, value/2, counter+1);
        lengths[value] = ret_val - counter;
    } else {
        //we've reached a non-computed chain start.
        //dig deeper using the odd path
        ret_val = leaner_collatz(lengths, value*3+1, counter+1);
        lengths[value] = ret_val - counter;
    }
    
    return ret_val;
}

class pe014 : public pe_base {
    void run_test() {
        typedef int type;
        type under = 1000000;
        type ans = 837799;
        type best_value =0;
        type best_start = 0;

        std::map<type, type> collatz_lengths;
        collatz_lengths[1] = 0;
        collatz_lengths[2] = 1;

        try{
            for (type i = 3; i < under; ++i) {
                //int value = dumb_collatz(i, 0);
                type value = leaner_collatz(collatz_lengths, i, 0);
                if (value > best_value) {
                    best_value = value;
                    best_start = i;
                    //std::cout << "New longest found: [" << best_start << ", " << best_value << "]" << std::endl;
                }
            }
        } catch (std::bad_alloc &b) {
            std::cerr << "Bad_alloc caught: " << b.what() << "\nQuitting Early" << std::endl;
        }
        
        check("014", ans, best_start);
    }
};

int main(int argc, char** argv) {
    pe014 test;
    test.go();
    std::cout << test.get_message() << std::endl; 
    return test.exit_code();
}

