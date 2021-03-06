# Routines-cpp #

The collection of header-only routines.

The idea is: you can get any header file with the name *[feature]_routines.h* and use it in your project without any compiler or linker setup. This repository also includes unit tests for all features.

## Base64 ##

Header-only implementation of [Base64](https://en.wikipedia.org/wiki/Base64) Encode/Decode algorithms. The implementation is not intended to be super fast, it just works.

__Location:__

    routines-cpp/base64/base64_routines.h

__Usage:__

    #include <assert.h>
    #include "routines-cpp/base64/base64_routines.h"
    std::string test_string = "1234567";
    std::string encoded = base64routines::Encode(test_string);
    std::string decoded = base64routines::Decode(encoded);
    assert(test_string == decoded);

## Coming soon ##

*  Some secure hash algorithms such as md5, sha1, sha256
*  Endianness routines
*  Big integer routines
*  Unicode routines (Unicode UTF-8 sequense parser, code position categories etc.)
*  String routines (split, strip, substitute etc.)
