# Ubuntu Cloud Image Info

This project fetches the latest Ubuntu Cloud image information in Simplestreams format and provides methods to retrieve supported Ubuntu releases, current LTS version, and SHA256 of disk1.img for a given release.

## Prerequisites

- CMake (version 3.10 or higher)
- C++17 compatible compiler
- libcurl
- nlohmann_json

## Building the Project

1. Clone the repository:
   ```
   git clone https://github.com/Ammar1123/canonical_assignment
   cd UbuntuCloudImageInfo
   ```

2. Create a build directory and navigate to it:
   ```
   mkdir build
   cd build
   ```

3. Run CMake and build the project:
   ```
   cmake ..
   make
   ```

## Usage

After building the project, you can run the executable with the following options:

- List supported Ubuntu releases:
  ```
  ./UbuntuCloudImageInfo releases
  ```

- Get the current Ubuntu LTS version:
  ```
  ./UbuntuCloudImageInfo lts
  ```

- Get the SHA256 of disk1.img for a specific Ubuntu release:
  ```
  ./UbuntuCloudImageInfo sha256 <release>
  ```
  Replace `<release>` with the desired Ubuntu release.

## Notes

- The project uses libcurl for HTTP requests and nlohmann_json for JSON parsing. Make sure these libraries are installed on your system.