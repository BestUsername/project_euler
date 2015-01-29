#include <cstdlib>
#include <cmath>
#include <iostream>

bool is_pal(int num) {
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

//does not include leading zeros as valid
int largest_pal_fac(int num_digits) {
    int retval = 0;
    int temp_product = 0;
    
    if (num_digits > 0) {
        int min = std::pow(10, num_digits -1);
        int max = std::pow(10, num_digits) - 1;

        for (int i = max; i >= min; --i) {
            for (int o = max; o >= min; --o) {
                temp_product = i*o;
                if (temp_product > retval && is_pal(temp_product)) {
                    retval = temp_product;
                }
            }
        }
    }
    return retval;
   
}

int main(int argc, char **argv) {
    int retval = EXIT_SUCCESS;

    int fac = largest_pal_fac(3);
    int ans = 906609;
    retval = fac == ans;

    std::cout << "Should be " << ans << ": " << fac << " - " << retval << std::endl;

    return retval;
}

