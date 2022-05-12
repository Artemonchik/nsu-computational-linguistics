#include <iostream>
#include <string>
#include "include/dict/OpenCorpaDict.h"
#include "include/text-parser/TextAnalyzer.h"
#include "include/Models.hpp"
#include <filesystem>
#include <fstream>
#include <numeric>

#include <cassert>

//int task1() {
//    std::setlocale(LC_ALL, "ru_RU.UTF-8");
//    std::wcout.imbue(std::locale("ru_RU.UTF-8"));
//
//    OpenCorpaDict openCorpaDict("../dict/dict.opcorpora.small.xml");
//    std::string path("../texts-small");
//
//    std::vector<TextAnalyzer> texts;
//    for (const auto& entry: std::filesystem::directory_iterator(path)) {
//        std::fstream f(entry.path(), std::ios::in);
//        texts.emplace_back(f);
//    }
//
//    TextAnalyzer result;
//    result.setDict(&openCorpaDict);
//    for (auto& text: texts) {
//        result += text;
//    }
//    std::set<std::string> props = {};
//    std::cout << "size of dictionary is: " << openCorpaDict.size() << std::endl;
//    std::cout << "ambiguity percent is: " << result.countAmbiguity() << std::endl;
//    std::cout << "recognized percent is: " << result.countNotRecognizedPart() << std::endl;
//    std::cout << "size of corpus is: " << result.countWords() << std::endl;
//    std::cout << std::endl;
//    std::cout << result.str(3000, props);
//    return 0;
//}

//int task2() {
//    std::setlocale(LC_ALL, "ru_RU.UTF-8");
//    std::wcout.imbue(std::locale("ru_RU.UTF-8"));
//
//    OpenCorpaDict openCorpaDict("../dict/dict.opcorpora.xml");
//    std::string path("../texts");
//
//    std::vector<TextAnalyzer> texts;
//    for (const auto& entry: std::filesystem::directory_iterator(path)) {
//        std::fstream f(entry.path(), std::ios::in);
//        texts.emplace_back(f);
//    }
//
//    TextAnalyzer result;
//    result.setDict(&openCorpaDict);
//    for (auto& text: texts) {
//        result += text;
//    }
//
//    std::string phraseStr = "увидел, что";
//    auto strStream = std::istringstream(phraseStr);
//    TextAnalyzer phrase(strStream, std::string());
//    phrase.setDict(&openCorpaDict);
//    auto exts = phrase.findExtentions(result, 6);
//    std::vector<std::pair<std::vector<std::string>, int>> left_exts;
//    std::copy(exts.first.begin(), exts.first.end(), std::back_inserter(left_exts));
//    std::sort(left_exts.begin(), left_exts.end(), [](auto& left, auto& right) {
//        return left.second > right.second;
//    });
//
//    std::vector<std::pair<std::vector<std::string>, int>> right_exts;
//    std::copy(exts.second.begin(), exts.second.end(), std::back_inserter(right_exts));
//    std::sort(right_exts.begin(), right_exts.end(), [](auto& left, auto& right) {
//        return left.second > right.second;
//    });
//    for (auto& left_ext: left_exts) {
//        std::string res_str;
//        for (auto& str: left_ext.first) {
//            res_str += str + " ";
//        }
////        if(left_ext.second <= 1){
////            continue;
////        }
//        res_str.back() = '\0';
//        std::printf("<л,%s,%d>\n", res_str.c_str(), left_ext.second);
//    }
//    for (auto& right_ext: right_exts) {
//        std::string res_str;
//        for (auto& str: right_ext.first) {
//            res_str += str + " ";
//        }
//        res_str.back() = '\0';
//        std::printf("<п,%s,%d>\n", res_str.c_str(), right_ext.second);
//    }
//    return 0;
//}

int task3(std::vector<TextAnalyzer>& texts, OpenCorpaDict& openCorpaDict) {
    TextAnalyzer analyzer;
    int corpusSize = 0;
    for (auto& text: texts) {
        text.setDict(&openCorpaDict);
        text.normalize();
        analyzer += text;
        corpusSize++;
    }
    analyzer.setDict(&openCorpaDict);
    auto ngrams = TextAnalyzer::findStableNgramms(analyzer, corpusSize);
    std::vector<std::pair<NGram, NGramInfo>> ngramsVector;
    for (auto& [ngram, info]: ngrams) {
        if (ngram.size() >= 4) {
            ngramsVector.emplace_back(ngram, info);
        }
    }
    std::sort(ngramsVector.begin(), ngramsVector.end(),
              [](std::pair<NGram, NGramInfo>& a, std::pair<NGram, NGramInfo>& b) {
                  return a.first.size() > b.first.size();
              });
    std::sort(ngramsVector.begin(), ngramsVector.end(),
              [](std::pair<NGram, NGramInfo>& a, std::pair<NGram, NGramInfo>& b) {
                  return a.second.stability < b.second.stability;
              });
    int i = 0;
    for (auto& [k, v]: ngramsVector) {
        i++;
        if (i == 1000) {
            break;
        }

        std::cout << "\"";
        for (auto& word: k) {
            std::cout << word << " ";
        }
        std::cout << "\" ";

        std::cout << v.count << " " <<
                  v.textNums.size() << " "
                  << std::setprecision(3) << v.stability << " " <<
                  std::endl;
    }
    std::cout << ngrams.size();
    return 0;
}

int task4(std::vector<TextAnalyzer>& texts, OpenCorpaDict& openCorpaDict) {
    auto models = getModels(&openCorpaDict);
    for (auto& text: texts) {
        text.setDict(&openCorpaDict);
        text.normalize();
        auto semanticEntries = text.findSemanticEntries(models);
        for (auto& [num, name, words]: semanticEntries) {
            std::cout << name << ":" << text.getName() << ":" << num << std::endl;
            std::copy(words.begin(),
                      words.end(),
                      std::ostream_iterator<std::string>(std::cout, " "));
            std::cout << std::endl;
        }
    }
    return 0;
}

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));

    auto t1 = std::chrono::steady_clock::now();
    OpenCorpaDict openCorpaDict("../dict/dict.opcorpora.xml");
    std::string path("../texts");
    auto t2 = std::chrono::steady_clock::now();
    std::cout << "open corpora dict was parsed in "
              << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count() << " seconds" << std::endl;

    std::vector<TextAnalyzer> texts;

    for (const auto& entry: std::filesystem::directory_iterator(path)) {
        std::fstream f(entry.path(), std::ios::in);
        texts.emplace_back(f, entry.path().filename());
    }
//    TextAnalyzer textAnalyzer(std::stringstream("убил человека"));
//    auto result = textAnalyzer.findSemanticEntries(getModels(openCorpaDict));
    return task4(texts, openCorpaDict);
}
