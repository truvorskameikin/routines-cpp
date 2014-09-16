#ifndef __BASE64_ROUTINES_H_
#define __BASE64_ROUTINES_H_

#include <string>

namespace base64routines {
  std::string Encode(const std::string& data);
  std::string Decode(const std::string& data);

  namespace {
    const char kPadChar = '=';

    const int kBits2 = 0x3;
    const int kBits4 = 0xF;
    const int kBits6 = 0x3F;

    char indexToChar(int index) {
      if (index < 26)
        return 'A' + index;
      else if (index < 26 * 2)
        return 'a' + index - 26;
      else if (index < 26 * 2 + 10)
        return '0' + index - 26 * 2;
      else if (index == 62)
        return '+';
      else
        return '/';
    }

    int charToIndex(int c) {
      if (c >= 'A' && c <= 'Z')
        return c - 'A';
      else if (c >= 'a' && c <= 'z')
        return c - 'a' + 26;
      else if (c >= '0' && c <= '9')
        return c - '0' + 26 * 2;
      else if (c == '+')
        return 26 * 2 + 10;
      else
        return 63;
    }

    void tripleToQuad(const char* triple, int triple_length, char* quad_out) {
      quad_out[0] = 0;
      quad_out[1] = 0;
      quad_out[2] = 0;
      quad_out[3] = 0;

      if (triple_length >= 1) {
        quad_out[0] |= ((triple[0] >> 2) & kBits6);
        quad_out[1] |= ((triple[0] & kBits2) << 4);
      }
      if (triple_length >= 2) {
        quad_out[1] |= ((triple[1] >> 4) & kBits4);
        quad_out[2] |= ((triple[1] & kBits4) << 2);
      }
      if (triple_length >= 2) {
        quad_out[2] |= ((triple[2] >> 6) & kBits2);
        quad_out[3] |= (triple[2] & kBits6);
      }
    }

    void quadToTriple(const char* quad, char* triple_out) {
      triple_out[0] = 0;
      triple_out[1] = 0;
      triple_out[2] = 0;

      triple_out[0] |= (quad[0] << 2);
      triple_out[0] |= ((quad[1] >> 4) & kBits2);

      triple_out[1] |= ((quad[1] & kBits4) << 4);
      triple_out[1] |= (quad[2] >> 2);

      triple_out[2] |= ((quad[2] & kBits2) << 6);
      triple_out[2] |= quad[3];
    }

    int calculateEncodedSize(int data_size) {
      if (data_size % 3 == 0)
        return (data_size / 3) * 4;
      return ((data_size / 3) + 1) * 4;
    }

    int calculateDecodedSize(const std::string& encoded_data) {
      if (encoded_data.size() % 4 != 0)
        return 0;

      int num_quads = encoded_data.size() / 4;
      if (num_quads == 0)
        return 0;

      int last_quad_start = (num_quads - 1) * 4;
      int result = (num_quads - 1) * 3;

      if (encoded_data[last_quad_start + 2] == kPadChar && encoded_data[last_quad_start + 3] == kPadChar)
        result += 1;
      else if (encoded_data[last_quad_start + 3] == kPadChar)
        result += 2;
      else
        result += 3;

      return result;
    }
  }
}

inline
std::string base64routines::Encode(const std::string& data) {
  std::string result;

  int data_size = data.size();

  int encoded_size = calculateEncodedSize(data.size());
  result.resize(encoded_size);

  int triple_start = 0;
  int quad_start = 0;
  while (triple_start < data_size) {
    int triple_length = data_size - triple_start;
    if (triple_length > 3)
      triple_length = 3;

    tripleToQuad(&data[triple_start], triple_length, &result[quad_start]);
    for (int i = 0; i < 4; ++i)
      result[quad_start + i] = indexToChar(result[quad_start + i]);
    if (triple_length <= 1) {
      result[quad_start + 2] = kPadChar;
      result[quad_start + 3] = kPadChar;
    } else if (triple_length <= 2) {
      result[quad_start + 3] = kPadChar;
    }

    triple_start += 3;
    quad_start += 4;
  }

  return result;
}

inline
std::string base64routines::Decode(const std::string& data) {
  std::string result;

  int data_size = data.size();

  if (data.size() % 4 != 0)
    return result;

  int decoded_size = calculateDecodedSize(data);
  result.resize(decoded_size);

  int quad_start = 0;
  int triple_start = 0;
  while (quad_start < data_size) {
    char quad[4] = {0, 0, 0, 0};
    for (int i = 0; i < 4; ++i) {
      if (data[quad_start + i] != kPadChar)
        quad[i] = charToIndex(data[quad_start + i]);
    }

    char triple[3] = {0, 0, 0};
    quadToTriple(quad, triple);

    int triple_length = decoded_size - triple_start;
    if (triple_length > 3)
      triple_length = 3;

    for (int i = 0; i < triple_length; ++i)
      result[triple_start + i] = triple[i];

    quad_start += 4;
    triple_start += 3;
  }

  return result;
}

#endif