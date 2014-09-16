# Routines-cpp #

The collection of header-only routines.

The idea is: you can get any header file with the name *[feature]_routines.h* and use it in your project without any compiler or linker setup. This repository also includes unit tests for all features.

## Base64 ##
Header-only implementation of Base64 Encode/Decode algorithms. The implementation is not intended to be super fast, it just works.

__Repository location__:

    base64/base64_routines.h

__Usage__:
    
    #include <assert.h>
    #include "base64_routines.h"
    std::string test_string = "1234567";
    std::string encoded = base64routines::Encode(test_string);
    std::string decoded = base64routines::Decode(encoded);
    assert(test_string == decoded);

## Coming soon ##
*  Unicode routines (Unicode UTF-8 sequense parser, code position categories etc.)
