// main.cpp
#include "../include/kyte/Client.hpp"
#include <iostream>

int main() {
    // Initialize the client with sample credentials and endpoint
    kyte::Client client("your_public_key", "your_private_key", "your_kyte_account",
                        "your_kyte_identifier", "https://api.flykyte.io");

    // Perform a GET request to a sample model with optional field and value
    std::string response = client.get("SampleModel", "SampleField", "SampleValue");

    // Print the response to the console
    std::cout << "Response from Kyte API: " << response << std::endl;

    // Optionally, demonstrate more requests, e.g., POST, PUT, DELETE
    std::string postData = "{\"key\":\"value\"}";
    std::string postResponse = client.post("SampleModel", postData);
    std::cout << "Response from POST to Kyte API: " << postResponse << std::endl;

    return 0;
}
