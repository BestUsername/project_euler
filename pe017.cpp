#include<iostream>
#include <cmath>
#include <sstream>
#include <tuple>

#include "pe.h"

/**
 * Takes in a positive integer (1 <= number < 1000) and returns the human string
 * as well as the count of letters.
 * Example: 128 would return <24, "one hundred and twenty eight">
**/
template<typename T>
std::tuple<size_t, std::string> char_count_and_string_e2(T number) {
    if (number < 0 || number >1000) {
        std::cerr << "ERROR: " << number << std::endl;
        throw std::invalid_argument("Input must be between 0 and 999 inclusive");
    }
    if (number == 0) {
        return std::make_tuple(0, "");
    }

    std::string u20[19] = {"one", "two", "three", "four", "five", "six", "seven", 
                           "eight", "nine", "ten", "eleven", "twelve", "thirteen",
                           "fourteen", "fifteen", "sixteen", "seventeen", "eighteen",
                           "nineteen"};
    std::string tens[8] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy",
                           "eighty", "ninety"};
    std::string hundred = "hundred";
    std::string and_string = "and";

    size_t count = 0;
    std::stringstream stream;

    T remainder = number;
    T temp;

    if (remainder >= 100) {
        temp = T(remainder/100);
        remainder = remainder % 100;

        count += u20[temp-1].length() + hundred.length();
        stream << u20[temp-1] << " " << hundred;
        
        if (remainder >= 1) {
            count += and_string.length();
            stream << " " << and_string << " ";
        }
    }

    while (remainder >= 1) {
        if (remainder >=20 && remainder < 100) {
            temp = T(remainder/10);
            remainder = remainder % 10;

            count += tens[temp-2].length();
            stream << tens[temp-2];
            // only add a space if we need to finish the number
            if (remainder >= 1) {
                stream << " ";
            }
        } else if (remainder >= 1 && remainder < 20) {
            count += u20[remainder-1].length();
            stream << u20[remainder-1];
            remainder = 0;
        }
    }
    return std::make_tuple(count, stream.str());
}

/**
 * Takes in a positive integer (1 <= number < 1*10^63) and returns the human string
 * as well as the count of letters.
 * Example: 128 would return <24, "one hundred and twenty eight">
 * Example: 100003450000 would return <56, "one hundred billion three million four hundred and fifty thousand">
**/
template<typename T>
std::tuple<size_t, std::string> char_count_and_string_ex3(T number) {
    // These are all of the groupings in increments of 10^3 in wikipedia
    std::string e3s[21] = {
            "thousand", "million", "billion", "trillion", "quadrillion", "quintillion", "sextillion", "septillion",
            "octillion", "nonillion", "decillion", "undecillion", "duodecillion", "tredecillion", "quattuordecillion",
            "quindecillion", "sexdecillion", "septendecillion", "octodecillion", "novemdecillion", "vigintillion"};
    size_t count = 0;
    std::stringstream stream;

    double logval;
    T section, section_scalar, section_value;

    while (number >= 1) {
        // isolate the most significant "section" (named triplet group)
        logval = log10(number);
        section = floor(logval/3);
        section_scalar = pow(10, section*3);
        section_value = number / section_scalar;
        std::tuple<size_t, std::string> section_tuple = char_count_and_string_e2<T>(section_value);

        count += std::get<0>(section_tuple);
        stream << " " << std::get<1>(section_tuple);
        number -= (section_value * section_scalar);

        if (section >=1) {
            count += e3s[section-1].length();
            stream << " " << e3s[section-1];
        }
    }
    return std::make_tuple(count, stream.str());
}

/**
 * Specifically for pe017: loop from 1 through [number] and sum the character count for all human-written words.
 */
size_t get_looped_letter_count(int number) {
    size_t counter = 0;
    std::tuple<size_t, std::string> count_and_string;
    for (int i = 1; i <= number; ++i) {
        count_and_string = char_count_and_string_ex3<int>(i);
        counter += std::get<0>(count_and_string);
        //std::cout << i << ":\t" << std::get<0>(count_and_string) << "\t" << counter << "\t" << std::get<1>(count_and_string) << std::endl;
    }
    return counter;
}

/**
 * Simple util function to print out a number, it's english form, and the character count.
 */
template<typename T>
void printout(T number) {
    std::tuple<size_t, std::string> result = char_count_and_string_ex3<T>(number);
    std::cout << number << "\t" << std::get<0>(result) << "\t" << std::get<1>(result) << std::endl;
}

class pe017 : public pe_base {
    void run_test() {
        //check("017", 19, int(get_looped_letter_count(5)));
        check("017", 21124, int(get_looped_letter_count(1000)));
    }
};

int main(int argc, char** argv) {
    /*
    printout<long long>(100003450000LL);
    printout<long long>(123456789123LL);
    */

    pe017 test;
    test.go();
    std::cout << test.get_message() << std::endl; 
    return test.exit_code();
}

