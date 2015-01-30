#include <cstdlib>
#include <cmath>
#include <memory>
#include <iostream>
/*
The sum of the squares of the first ten natural numbers is,

1^2 + 2^2 + ... + 10^2 = 385
The square of the sum of the first ten natural numbers is,

(1 + 2 + ... + 10)^2 = 55^2 = 3025
Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.

Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
*/

int sped_up(int n) {
    int sum = n * (n+1) / 2;
    int squared = (n * (n+1) * (2*n+1)) / 6;
    return sum * sum - squared;
}

std::shared_ptr<std::pair<int, int> >
find_sums_brute(int start, int end) {
    int sum_squares = 0;
    int square_sums = 0;
    std::shared_ptr<std::pair<int,int> > retval(new std::pair<int, int>());

    for (int i = start; i <= end; ++i) {
        sum_squares += std::pow(i, 2);
        square_sums += i;
    }

    square_sums = std::pow(square_sums, 2);

    retval->first = sum_squares;
    retval->second = square_sums;
    return retval;
}

int main(int argc, char **argv) {
    int retval = EXIT_SUCCESS;
    int start = 1;
    int end = 100;
    std::shared_ptr<std::pair<int, int> > result = find_sums_brute(start, end);
    int ans = 25164150;
    int value = std::abs(result->first - result->second);
    int value2 = sped_up(100);
    std::cout << "Answer should be: " << ans << " - " << value << " - " << value2 << std::endl;
    return retval;
}

