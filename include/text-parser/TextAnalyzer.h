#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <optional>
#include <vector>
#include "../dict/OpenCorpaDict.h"
#include "../Models.hpp"

#define DELIMETER "$$##$$"

#include "../types.hpp"

struct NGramInfo {
    int count = 0;
    // text num, pos num
    std::set<std::pair<int, int>> position;
    std::set<int> textNums;
    float stability = 0;
    float tfidf = 0;
};

class TextAnalyzer {
public:
    explicit TextAnalyzer(std::istream& istream, std::string name);

    TextAnalyzer();

    TextAnalyzer(const TextAnalyzer& other);

    TextAnalyzer(TextAnalyzer&& other);

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

    void normalize();

    static std::map<NGram, NGramInfo> findStableNgramms(TextAnalyzer& text, int corpusSize);

    void
    findSemanticEntries(std::vector<Model>& models);

    const std::string& getName() const;

private:
    void readWords(std::istream& istream);

    void countWordsFreq();

    void toLower();

private:
    OpenCorpaDict* dict = nullptr;
    std::vector<std::string> tokens;
    std::unordered_map<std::string, int> wordToCount;
    std::string name;

    bool areTokenEquals(std::string& string1, std::string& string2);

    std::vector<std::string> getLeftExtentions(int i, int limit, TextAnalyzer& rhs);

    std::vector<std::string> getRightExtentions(int i, int limit, TextAnalyzer& rhs);

    static std::map<NGram, NGramInfo>
    findNgrams(TextAnalyzer& text, int size, std::map<NGram, NGramInfo>* previous_ptr);

    static std::map<NGram, NGramInfo> filterNgrams(std::map<NGram, NGramInfo>& ngramsToCount);

    std::vector<std::string>::iterator getNextSentence(std::vector<std::string>::iterator iterator);
};