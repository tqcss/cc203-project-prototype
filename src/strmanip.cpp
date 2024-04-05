#include <string>
#include "../include/strmanip.h"

/**
 * @brief Capitalizes each character in a string.
 * 
 * This function converts each character in the input string to its uppercase equivalent.
 * 
 * @param str The input string to capitalize.
 * @return A new string with all characters capitalized.
 */
std::string toUppercase(const std::string &str) {
    std::string result;
    for (const char &letter : str) {
        result += std::toupper(letter);
    }
    return result;
}

/**
 * @brief Converts each character in a string to lowercase.
 * 
 * This function converts each character in the input string to its lowercase equivalent.
 * 
 * @param str The input string to convert to lowercase.
 * @return A new string with all characters converted to lowercase.
 */
std::string toLowercase(const std::string &str) {
    std::string result;
    for (const char &letter : str) {
        result += std::tolower(letter);
    }
    return result;
}

