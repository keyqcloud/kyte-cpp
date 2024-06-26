# Kyte C++ Client Library

[![C++ Build Workflow](https://github.com/keyqcloud/kyte-cpp/actions/workflows/build.yml/badge.svg)](https://github.com/keyqcloud/kyte-cpp/actions/workflows/build.yml)
[![CodeQL](https://github.com/keyqcloud/kyte-cpp/actions/workflows/codeql.yml/badge.svg)](https://github.com/keyqcloud/kyte-cpp/actions/workflows/codeql.yml)

The Kyte C++ Client Library is designed to facilitate communication between your applications and the Kyte backend API, offering a robust and efficient way to manage API calls.

## Features

- **Easy-to-use API**: Simplified methods for making HTTP GET, POST, PUT, and DELETE requests.
- **Secure Communication**: Integrated handling of encryption and secure connections.
- **Cross-Platform**: Compatible with various operating systems including Linux, macOS, and Windows.

## Getting Started

### Prerequisites

Ensure you have the following installed on your system:

- C++ compiler (GCC or Clang)
- CMake
- libcurl
- OpenSSL

### Building the Project

To build the Kyte C++ Client Library, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/keyqcloud/kyte-cpp.git
   cd kyte-cpp
   ```

2. Build the project using CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

This will compile the library and any associated executables into the `build` directory.

### Usage

Here is a simple example of how to use the library to make API calls:

```cpp
#include "kyte/Client.hpp"

int main() {
    kyte::Client client("your_public_key", "your_private_key", "your_kyte_account",
                        "your_kyte_identifier", "https://api.kyte.io");

    std::string response = client.get("testModel");
    std::cout << "API Response: " << response << std::endl;
    return 0;
}
```

### Documentation

For more detailed documentation on API methods and parameters, refer to the `docs` directory.

## Contributing

Contributions to the Kyte C++ Client Library are welcome! Please refer to the `CONTRIBUTING.md` file for guidelines on how to make contributions.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
