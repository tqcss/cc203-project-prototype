#pragma once
#include <sstream>

std::string toUppercase(const std::string &str);

std::string toLowercase(const std::string &str);


/**
 * @brief Concatenates multiple values into a single string.
 * 
 * This function concatenates multiple values into a single string using
 * stream insertion (<<) operator. The values are forwarded and appended
 * to a stringstream object.
 * 
 * @tparam Args The types of arguments to concatenate.
 * @param args The arguments to concatenate.
 * @return A string containing the concatenated values.
 */
template<typename ... Args>
std::string concat(Args&&...args)
{
    std::stringstream ss;
    (ss << ... << std::forward<Args>(args));
    return ss.str();
}