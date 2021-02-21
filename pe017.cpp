#include<iostream>
#include <cmath>
#include <sstream>
#include <tuple>

#include "pe.h"

/**
 * Takes in a positive integer (1 <= number < 1000) and returns the string
 * as well as the count of letters. 
 * Example: 128 would return <24, "one hundred and twenty eight">
**/
std::tuple<size_t, std::string> char_count_and_string_e2(int number) {
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

    int remainder = number;
    int temp;

    if (remainder >= 100) {
        temp = int(remainder/100);
        remainder = remainder % 100;

        count += u20[temp-1].length() + hundred.length();
        stream << u20[temp-1] << " " << hundred << " ";
        
        if (remainder > 0) {
            count += and_string.length();
            stream << and_string << " ";
        }
    }

    while (remainder >= 1) {
        if (remainder >=20 && remainder < 100) {
            temp = int(remainder/10);
            remainder = remainder % 10;

            count += tens[temp-2].length();
            stream << tens[temp-2] << " ";
        } else if (remainder >= 1 && remainder < 20) {
            
            count += u20[remainder-1].length();
            stream << u20[remainder-1];
            remainder = 0;
        }
    }
    return std::make_tuple(count, stream.str());
}


std::tuple<size_t, std::string> char_count_and_string_e3(int number) {
    std::string thousand = "thousand";
    
    size_t count = 0;
    std::stringstream stream;


    if (number < 1 || number >= 1e6) {
        throw std::invalid_argument("Input must be between 1 and 999,999 inclusive");
    }

    int temp;

    if (number >= 1000) {
        temp = int(number/1000);
        number -= (temp*1000);

        std::tuple<size_t, std::string> thousands = char_count_and_string_e2(temp);
        count += std::get<0>(thousands) + thousand.length();
        stream << std::get<1>(thousands) << " " << thousand;
        if (number > 0) {
            stream << " ";
        }
    }
    if (number >= 1) {
        std::tuple<size_t, std::string> hundreds = char_count_and_string_e2(number);
        count += std::get<0>(hundreds);
        stream << std::get<1>(hundreds);
    }
    return std::make_tuple(count, stream.str());
}

size_t get_looped_letter_count(int number) {
    size_t counter = 0;
    std::tuple<size_t, std::string> count_and_string;
    for (int i = 1; i <= number; ++i) {
        count_and_string = char_count_and_string_e3(i);
        counter += std::get<0>(count_and_string);
        // std::cout << i << ":\t" << std::get<0>(count_and_string) << "\t" << counter << "\t" << std::get<1>(count_and_string) << std::endl;
    }
    return counter;
}

class pe017 : public pe_base {
    void run_test() {
        //check("017", 19, int(get_looped_letter_count(5)));
        check("017", 21124, int(get_looped_letter_count(1000)));
        //check("017", 56, int(std::get<0>(get_letter_count_of_number(999999))));
        //check("017", 37, int(std::get<0>(get_letter_count_of_number(9324))));
    }
};

int main(int argc, char** argv) {
    pe017 test;
    test.go();
    std::cout << test.get_message() << std::endl; 
    return test.exit_code();
}

