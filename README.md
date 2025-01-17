# WebToken

This is a library which implements
[RFC 7519](https://tools.ietf.org/html/rfc7519), "JSON Web Token (JWT)".

## Usage

The `WebToken::WebToken` class represents a JSON Web Token (JWT).  One may be
constructed from an encoded JWT and used to extract the various parts of the
JWT, such as the header, payload, and signature.

## Supported platforms / recommended toolchains

This is a portable C++11 library which depends on the C++11 compiler, standard
library, and the [Base64](https://github.com/rhymu8354/Base64.git) and
[Json](https://github.com/rhymu8354/Json.git) libraries.  It should be
supported on almost any platform.  The following are recommended toolchains for
popular platforms.

* Windows -- [Visual Studio](https://www.visualstudio.com/)
  (Microsoft Visual C++)
* Linux -- clang or gcc
* MacOS -- Xcode (clang)

## Building

This library is not intended to stand alone.  It is intended to be included in
a larger solution which uses [CMake](https://cmake.org/) to generate the build
system and build applications which will link with the library.

There are two distinct steps in the build process:

1. Generation of the build system, using CMake
2. Compiling, linking, etc., using CMake-compatible toolchain

### Prerequisites

* [Base64](https://github.com/rhymu8354/Base64.git) - a library which
  implements encoding and decoding data using the Base64 algorithm, which
  is defined in [RFC 4648](https://tools.ietf.org/html/rfc4648).
* [CMake](https://cmake.org/) version 3.8 or newer
* C++11 toolchain compatible with CMake for your development platform
  (e.g. [Visual Studio](https://www.visualstudio.com/) on Windows)
* [Json](https://github.com/rhymu8354/Json.git) - a library which implements
  [RFC 7159](https://tools.ietf.org/html/rfc7159), "The JavaScript Object
  Notation (JSON) Data Interchange Format".

### Build system generation

Generate the build system using [CMake](https://cmake.org/) from the solution
root.  For example:

```bash
mkdir build
cd build
cmake -G "Visual Studio 15 2017" -A "x64" ..
```

### Compiling, linking, et cetera

Either use [CMake](https://cmake.org/) or your toolchain's IDE to build.
For [CMake](https://cmake.org/):

```bash
cd build
cmake --build . --config Release
```
