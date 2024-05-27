#include "Functions.hpp"

bool functions::stringIsInt(std::string string) {
    if (string.length() == 0) 
    return false;
    for (int i = 0; i < string.length(); i++) {
        if (isdigit(string[i]) == false) {
            return false;
        }
    }
    return true;
}