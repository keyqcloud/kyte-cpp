// Client.hpp
#ifndef KYTE_CLIENT_HPP
#define KYTE_CLIENT_HPP

#include <string>
#include <curl/curl.h>
#include "Util.hpp"

namespace kyte {

class Client {
private:
    std::string public_key;
    std::string private_key;
    std::string kyte_account;
    std::string kyte_identifier;
    std::string kyte_endpoint;
    std::string kyte_app_id;
    std::string sessionToken;
    std::string transactionToken;

    std::string getIdentity(const std::string& timestamp);
    std::string getSignature(const std::string& epoch);

public:
    Client(const std::string& public_key, const std::string& private_key, const std::string& kyte_account,
           const std::string& kyte_identifier, const std::string& kyte_endpoint, const std::string& kyte_app_id = "");

    std::string request(const std::string& method, const std::string& model, const std::string& field = "",
                        const std::string& value = "", const std::string& data = "");

    // Methods to expose high-level functionality like post, get, put, delete
    std::string post(const std::string& model, const std::string& data);
    std::string get(const std::string& model, const std::string& field = "", const std::string& value = "");
    std::string put(const std::string& model, const std::string& field, const std::string& value, const std::string& data);
    std::string deleteRequest(const std::string& model, const std::string& field, const std::string& value);
};

} // namespace kyte

#endif // KYTE_CLIENT_HPP
