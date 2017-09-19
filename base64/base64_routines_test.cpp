#include <assert.h>
#include "base64_routines.h"
#include "base64_routines_test.h"

void TestBase64Routines() {
  {
    assert(base64routines::Encode("123456") == "MTIzNDU2");
    assert(base64routines::Encode("1234567") == "MTIzNDU2Nw==");
    assert(base64routines::Encode("12345678") == "MTIzNDU2Nzg=");
    assert(base64routines::Encode("12>4567") == "MTI+NDU2Nw==");
    assert(base64routines::Encode("12?4567") == "MTI/NDU2Nw==");
    assert(base64routines::Encode("") == "");
    assert(base64routines::Encode("A") == "QQ==");
  }

  {
    assert(base64routines::Decode("MTIzNDU2") == "123456");
    assert(base64routines::Decode("MTIzNDU2Nw==") == "1234567");
    assert(base64routines::Decode("MTIzNDU2Nzg=") == "12345678");
    assert(base64routines::Decode("MTI+NDU2Nw==") == "12>4567");
    assert(base64routines::Decode("MTI/NDU2Nw==") == "12?4567");
    assert(base64routines::Decode("") == "");
    assert(base64routines::Decode("QQ==") == "A");
  }
}

#if defined(TEST_BASE64_ROUTINES)
int main(int argc, char* argv[]) {
  TestBase64Routines();
  return 0;
}
#endif
