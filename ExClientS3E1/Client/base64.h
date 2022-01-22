#include <string>

using namespace std;

string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
string base64_decode(string const& encoded_string);