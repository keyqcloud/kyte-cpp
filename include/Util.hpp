// Util.hpp
#ifndef KYTE_UTIL_HPP
#define KYTE_UTIL_HPP

#include <string>

namespace kyte {

    // Encode data using base64
    std::string base64_encode(const std::string& input);

    // URL encode a string
    std::string url_encode(const std::string& input);

} // namespace kyte

#endif // KYTE_UTIL_HPP
