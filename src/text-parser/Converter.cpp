#include "../../include/text-parser/Converter.hpp"
#include <locale>

template<class Facet>
struct deletable_facet : Facet {
    template<class ...Args>
    deletable_facet(Args&& ...args) : Facet(std::forward<Args>(args)...) {}

    ~deletable_facet() {}
};

static std::wstring_convert<deletable_facet<std::codecvt<char32_t, char, std::mbstate_t>>, char32_t> conv16;

string32 convertToWString(const std::string& string) {
    return conv16.from_bytes(string);
}

std::string convertToString(const string32& wstring) {
    return conv16.to_bytes(wstring);
}