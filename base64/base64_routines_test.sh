#!/bin/bash

g++ -DTEST_BASE64_ROUTINES base64_routines_test.cpp -o base64_routines

rc=$?
if [[ $rc != 0 ]] ; then
    exit $rc
fi

./base64_routines