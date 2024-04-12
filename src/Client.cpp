// Client.cpp
#include "Client.hpp"
#include <ctime>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <iomanip>

namespace kyte {

    Client::Client(const std::string& public_key, const std::string& private_key, const std::string& kyte_account,
                const std::string& kyte_identifier, const std::string& kyte_endpoint, const std::string& kyte_app_id)
        : public_key(public_key), private_key(private_key), kyte_account(kyte_account), kyte_identifier(kyte_identifier),
        kyte_endpoint(kyte_endpoint), kyte_app_id(kyte_app_id), sessionToken("0"), transactionToken("0") {}

    std::string Client::getIdentity(const std::string& timestamp) {
        std::string identityStr = public_key + "%" + sessionToken + "%" + timestamp + "%" + kyte_account;
        identityStr = base64_encode(identityStr);
        return url_encode(identityStr);
    }

    std::string Client::getSignature(const std::string &epoch) {
        unsigned char result[SHA256_DIGEST_LENGTH];
        unsigned int result_len;

        HMAC(EVP_sha256(), reinterpret_cast<const unsigned char*>(private_key.c_str()), private_key.length(),
            reinterpret_cast<const unsigned char*>(epoch.c_str()), epoch.length(), result, &result_len);

        std::stringstream hex_str;
        hex_str << std::hex << std::setfill('0');
        for (unsigned int i = 0; i < result_len; i++) {
            hex_str << std::setw(2) << static_cast<int>(result[i]);
        }

        return hex_str.str();
    }

    // Additional utility functions or include them from other files
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp) {
        userp->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    std::string Client::post(const std::string& model, const std::string& data) {
        return this->request("POST", model, "", "", data);
    }

    std::string Client::get(const std::string& model, const std::string& field, const std::string& value) {
        return this->request("GET", model, field, value, "");
    }

    std::string Client::put(const std::string& model, const std::string& field, const std::string& value, const std::string& data) {
        return this->request("PUT", model, field, value, data);
    }

    std::string Client::deleteRequest(const std::string& model, const std::string& field, const std::string& value) {
        return this->request("DELETE", model, field, value, "");
    }

    std::string Client::request(const std::string& method, const std::string& model, const std::string& field,
                                const std::string& value, const std::string& data) {
        std::time_t now = std::time(nullptr);
        std::string epoch = std::to_string(now);
        std::string timestamp = std::asctime(std::localtime(&now));
        std::string signature = getSignature(epoch);
        std::string identity = getIdentity(timestamp);

        std::string endpoint = kyte_endpoint + "/" + model;
        if (!field.empty() && !value.empty()) {
            endpoint += "/" + field + "/" + value;
        }

        CURL* curl = curl_easy_init();
        std::string readBuffer;
        if (curl) {
            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, ("Content-Type: application/json").c_str());
            headers = curl_slist_append(headers, ("Accept: application/json").c_str());
            headers = curl_slist_append(headers, ("x-kyte-signature: " + signature).c_str());
            headers = curl_slist_append(headers, ("x-kyte-identity: " + identity).c_str());
            if (!kyte_app_id.empty()) {
                headers = curl_slist_append(headers, ("x-kyte-appid: " + kyte_app_id).c_str());
            }

            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());

            if (method == "POST" || method == "PUT") {
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
            }

            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            }

            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }

        return readBuffer;
    }

} // namespace kyte
