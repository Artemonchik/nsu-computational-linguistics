#include <iostream>
#include <string>
#include "include/dict/OpenCorpaDict.h"
#include "include/text-parser/TextAnalyzer.h"
#include <filesystem>
#include <fstream>
#include <numeric>

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
    std::cout << result.str();

    return 0;
}
