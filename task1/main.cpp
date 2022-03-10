#include <iostream>
#include <string>
#include "include/dict/OpenCorpaDict.h"
#include "include/text-parser/TextAnalyzer.h"
#include <filesystem>
#include <fstream>
#include <numeric>

static void ru_utf8_tolower(char *str) {
    if (!str) return;
    unsigned char *a, *b;
    a = (unsigned char *) str;
    while (*a != 0) {
        if ((*a >= 0x41) && (*a <= 0x5a)) { // ENG
            *a = 0x61 + (*a - 0x41);
        } else if (*a == 0xd0) { // RUS
            b = a++;
            if (*a == 0) break;
            if ((*a >= 0x90) && (*a <= 0x9f)) {
                *a = 0xb0 + (*a - 0x90);
            } else if ((*a >= 0xa0) && (*a <= 0xaf)) {
                *a = 0x80 + (*a - 0xa0);
                *b = 0xd1;
            } else if (*a == 0x81) { // letter e:
                *a = 0x91;
                *b = 0xd1;
            } else a--;
        }
        a++;
    }
}

int main() {
    system("chcp 65001");

    OpenCorpaDict openCorpaDict("../dict/dict.opcorpora.xml");
    std::string path("../texts");
    std::vector<TextAnalyzer> texts;
    for (const auto &entry: std::filesystem::directory_iterator(path)) {
        std::fstream f(entry.path(), std::ios::in);
        texts.emplace_back(f);
    }

    TextAnalyzer result;
    result.setDict(&openCorpaDict);
    for (auto &text: texts) {
        result += text;
    }
    std::set<std::string> props = {"NOUN"};
    std::cout << "size of dictionary is: " << openCorpaDict.size() << std::endl;
    std::cout << "ambiguity percent is: " << result.countAmbiguity()  << std::endl;
    std::cout << "recognized percent is: " << result.countNotRecognizedPart() << std::endl;
    std::cout << "size of corpus is: " << result.countWords() << std::endl;
    std::cout << std::endl;
    std::cout << result.str(30, props);
    return 0;
}
