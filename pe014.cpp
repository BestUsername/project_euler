#include <iostream>
#include <cstdlib>
#include <vector>
#include <new>


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
T leaner_collatz(std::vector<T> & lengths, size_t value, T counter) {
    T ret_val;
    T current = lengths[value];
    if (value <=1) {
        //reached 1, chain ends here.
        ret_val = counter+1;
    } if (current !=0) {
        //we've reached a pre-computer chain. Tack on the cached value
//std::cerr << "Just saved calculating a chain of " << current << std::endl;
        ret_val = counter + current;
    } else if (value %2==0) {
        //we've reached a non-computed chain start.
        //dig deeper using the even path
        ret_val = leaner_collatz(lengths, value/2, counter+1);
    } else {
        //we've reached a non-computed chain start.
        //dig deeper using the odd path

        //need to check if the vector is too small.
        if (value*3+1 >= lengths.size()) {
            std::cerr << "resizing to " << value*4 << std::endl;
            lengths.resize(value*4);
        }
        
        ret_val = leaner_collatz(lengths, value*3+1, counter+1);
        
    }
    lengths[value] = ret_val;
    return ret_val;
}


/**
  Highest number to perform functions on is the largest odd number < under, *3-1
  But that doesn't give longest chain - just the range of keys.
  
  Two rules
    (even) n = n/2;
    (odd)  n = 3n-1;
 */
/*
template <typename T>
T longest_collatz(T under) {

    size_t highest_initial_index = (under % 2 == 0 ? under-1 : under) *3 +1;

    std::vector<T> collatz_lengths(highest_initial_index);

    collatz_lengths[2] = 1;
    
    for (int i = 1; i < under; ++i) {
        std::cout << i << ":\t" << leaner_collatz(collatz_lengths, i, 0) << std::endl;
    }

    auto longest_it = std::max_element(collatz_lengths.begin(), collatz_lengths.end());

    std::cout << "longest chain number under " << under << " is " << longest_it - collatz_lengths.begin() << ": chain length " << *longest_it << std::endl;
    return *longest_it;;
}
*/
int main(int argc, char ** argv) {
    typedef int type;
    
    int exit_code = EXIT_SUCCESS;
    type under = 1000000;
    type ans = 837799;
    type best_value =0;
    type best_start = 0;

    size_t highest_initial_index = (under % 2 == 0 ? under-1 : under) *3 +1;
    std::vector<type> collatz_lengths(highest_initial_index);
    collatz_lengths[2] = 1;
    
    try{
        for (type i = 1; i < under; ++i) {
            //int value = dumb_collatz(i, 0);

            type value = leaner_collatz(collatz_lengths, i, 0);
            if (value > best_value) {
                best_value = value;
                best_start = i;
                std::cout << "New longest found: [" << best_start << ", " << best_value << "]" << std::endl;
            }
        }
    } catch (std::bad_alloc &b) {
        std::cerr << "Bad_alloc caught: " << b.what() << "\nQuitting Early" << std::endl;
    }


    std::cout << "The answer should be " << ans << ": [" << best_start << ", " << best_value << "]" << std::endl;
    return exit_code;
}

