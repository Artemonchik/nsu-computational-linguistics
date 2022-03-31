#include <iostream>
#include <string>
#include "include/dict/OpenCorpaDict.h"
#include "include/text-parser/TextAnalyzer.h"
#include <filesystem>
#include <fstream>
#include <numeric>

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));

    OpenCorpaDict openCorpaDict("../dict/dict.opcorpora.small.xml");
    std::string path("../texts-small");

    std::vector<TextAnalyzer> texts;
    for (const auto& entry: std::filesystem::directory_iterator(path)) {
        std::fstream f(entry.path(), std::ios::in);
        texts.emplace_back(f);
    }

    TextAnalyzer result;
    result.setDict(&openCorpaDict);
    for (auto& text: texts) {
        result += text;
    }
    std::set<std::string> props = {};
    std::cout << "size of dictionary is: " << openCorpaDict.size() << std::endl;
    std::cout << "ambiguity percent is: " << result.countAmbiguity() << std::endl;
    std::cout << "recognized percent is: " << result.countNotRecognizedPart() << std::endl;
    std::cout << "size of corpus is: " << result.countWords() << std::endl;
    std::cout << std::endl;
    std::cout << result.str(3000, props);
    return 0;
}
