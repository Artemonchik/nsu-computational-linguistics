#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <optional>
#include "../dict/OpenCorpaDict.h"

class TextAnalyzer {
public:
    explicit TextAnalyzer(std::istream& istream);

    TextAnalyzer();

    TextAnalyzer(const TextAnalyzer& rhs);

    TextAnalyzer(TextAnalyzer&& rhs) noexcept;

    TextAnalyzer& operator=(const TextAnalyzer& other);

    TextAnalyzer& operator=(TextAnalyzer&& other) noexcept;

    TextAnalyzer& operator+=(const TextAnalyzer& rhs);

    TextAnalyzer operator+(const TextAnalyzer& rhs) const;

    std::string str(int limit, std::set<std::string>& props) const;

    void setDict(OpenCorpaDict* corpaDict);

    double countNotRecognizedPart();

    double countAmbiguity();

    int countWords();

    std::pair<std::map<std::vector<std::string>, int>, std::map<std::vector<std::string>, int>>
    findExtentions(TextAnalyzer& rhs, int limit);

private:
    void readWords(std::istream& istream);

    void countWordsFreq();

    void toLower();

private:
    OpenCorpaDict* dict = nullptr;
    std::vector<std::string> tokens;
    std::unordered_map<std::string, int> wordToCount;

    bool areTokenEquals(std::string& string1, std::string& string2);

    std::vector<std::string> getLeftExtentions(int i, int limit, TextAnalyzer& rhs);

    std::vector<std::string> getRightExtentions(int i, int limit, TextAnalyzer& rhs);
};