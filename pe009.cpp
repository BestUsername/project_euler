#include <cstdlib>
#include <iostream>
/*
A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

a^2 + b^2 = c^2
For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/

int find_product_of_triplet(int sum) {
    int product = 0;
    int a, b, c;
    int a_sqr, b_sqr, c_sqr;
    //for sum = 1000, maximum 'a' can be is 332, since a < b < c and a+b+c = 1000
    for (a = 1; (a < (sum/3)) && !product; ++a) {
        a_sqr = a*a;
        //if a is 1, then the biggest b can be is floor((sum-1)/2)
        for (b = a+1; (b < (sum/2)) && !product; ++b) {
            b_sqr = b*b;
            c = sum - (a+b);
            c_sqr = c*c;
            if (a_sqr + b_sqr == c_sqr) {
                //found it
                product = a * b * c;
            }
        }
    }
    return product;
}

int main(int argc, char **argv) {
    int retval = EXIT_SUCCESS;
    int ans = 31875000;
    int result = find_product_of_triplet(1000);
    std::cout << "Answer should be " << ans << ": " << result << std::endl;
    if (result != ans) {
        retval = EXIT_FAILURE;
    }
    return retval;
}

