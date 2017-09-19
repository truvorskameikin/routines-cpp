#!/bin/bash

g++ -DTEST_BASE64_ROUTINES -std=c++11 base64_routines_test.cpp -o base64_routines_test

rc=$?
if [[ $rc != 0 ]] ; then
    exit $rc
fi

echo "---"
echo "Runing tests..."
./base64_routines_test
echo "Done"
