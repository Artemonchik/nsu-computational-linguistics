#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <optional>
#include "../dict/OpenCorpaDict.h"

class TextAnalyzer {
public:
    explicit TextAnalyzer(std::istream &istream);

    TextAnalyzer();

    TextAnalyzer(const TextAnalyzer &rhs);

    TextAnalyzer(TextAnalyzer &&rhs) noexcept;

    TextAnalyzer &operator=(const TextAnalyzer &other);

    TextAnalyzer &operator=(TextAnalyzer &&other) noexcept;

    TextAnalyzer &operator+=(const TextAnalyzer &rhs);

    TextAnalyzer operator+(const TextAnalyzer &rhs) const;

    std::string str(int limit, std::set<std::string> &props) const;

    void setDict(OpenCorpaDict *corpaDict);

    double countNotRecognizedPart();

    double countAmbiguity();

    int countWords();

private:
    void readWords(std::istream &istream);

    void countWordsFreq();

private:
    OpenCorpaDict *dict = nullptr;
    std::vector<std::string> tokens;
    std::unordered_map<std::string, int> wordToCount;

    void stripWords();

    void toLower();
};