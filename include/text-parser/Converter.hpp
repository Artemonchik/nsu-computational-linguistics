#pragma once

#include <string>

using string32 = std::basic_string<char32_t, std::char_traits<char32_t>>;

string32 convertToWString(const std::string& string);

std::string convertToString(const string32& wstring);