#include <iostream>
#include <cstdlib>

#include "pe.h"

/**
  Starting in the top left corner of a 2x2 grid, and only being able to move to the right and down,
  there are exactly 6 routes to the bottom right corner.
  
  How many such routes are there through a 20x20 grid?
  */

/**
` The grid pattern is one of option counting.
  The point of exit has 0 or 1 option(s)
  The bottom-most and right-most edges only have 1 option total once they are reached.
  Any arbitrary point is going to have a total option count of the sum of the option counts for any other point it could go to.
  Confusing wording. Just look for the pattern in the graph

  0 1 1 1
  1 2 3 4
  1 3 6 10
  1 4 10 20

  So a fast solution would only require a cache of the shortest dimension size, and iterate the larger dimension's value.
  O(n) - where n = #graph_points

 */


template<typename T>
T total_paths(T length, T width) {
    //since there will be O(length*width) calculations anyway,
    //it makes sense to use the smaller dimension for the storage capacity.
    T shorter = std::min(length, width);
    T longer = std::max(length, width);
    //initialize and zero out the cache
    T cache[shorter];
	 for (T i = 0;i<shorter;++i) {
		 cache[i] = 0;
	 }
    //the additional iteration is to set up the initial values of all 1;
    for (T i = 0; i <= longer; ++i) {
        cache[0] += 1;
        for (T o = 0; o < shorter; ++o) {
            cache[o+1] += cache[o];
        }
    }
    
    return cache[shorter-1];
}

class pe015 : public pe_base {
    void run_test() {
        typedef long long type;
        type ans = 137846528820;
        type value = total_paths<type>(20,20);
        check("015", ans, value);
    }
};

int main(int argc, char** argv) {
    pe015 test;
    test.go();
    std::cout << test.get_message() << std::endl; 
    return test.exit_code();
}

