#include <iostream>
#include <string>
#include "include/dict/OpenCorpaDict.h"
#include "include/text-parser/TextAnalyzer.h"
#include <filesystem>
#include <fstream>
#include <numeric>

#include <cassert>

int task1() {
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

int task2() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));

    OpenCorpaDict openCorpaDict("../dict/dict.opcorpora.xml");
    std::string path("../texts");

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

    std::string phraseStr = "зевс";
    auto strStream = std::istringstream(phraseStr);
    TextAnalyzer phrase(strStream);
    phrase.setDict(&openCorpaDict);
    auto exts = phrase.findExtentions(result, 6);
    std::vector<std::pair<std::vector<std::string>, int>> left_exts;
    std::copy(exts.first.begin(), exts.first.end(), std::back_inserter(left_exts));
    std::sort(left_exts.begin(), left_exts.end(), [](auto& left, auto& right) {
        return left.second > right.second;
    });

    std::vector<std::pair<std::vector<std::string>, int>> right_exts;
    std::copy(exts.second.begin(), exts.second.end(), std::back_inserter(right_exts));
    std::sort(right_exts.begin(), right_exts.end(), [](auto& left, auto& right) {
        return left.second > right.second;
    });
    for (auto& left_ext: left_exts) {
        std::string res_str;
        for (auto& str: left_ext.first) {
            res_str += str + " ";
        }
        res_str.back() = '\0';
        std::printf("<л,%s,%d>\n", res_str.c_str(), left_ext.second);
    }
    for (auto& right_ext: right_exts) {
        std::string res_str;
        for (auto& str: right_ext.first) {
            res_str += str + " ";
        }
        res_str.back() = '\0';
        std::printf("<п,%s,%d>\n", res_str.c_str(), right_ext.second);
    }
    return 0;
}

int main() {
    return task2();
}
