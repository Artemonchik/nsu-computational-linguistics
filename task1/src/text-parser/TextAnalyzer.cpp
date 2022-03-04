//
// Created by sonechka on 02.03.2022.
//

#include <sstream>
#include "../../include/text-parser/TextAnalyzer.h"

TextAnalyzer::TextAnalyzer(std::istream &inputStream) {
    readWords(inputStream);
//    stripWords();
    countWords();
    //TODO to lower case
}

void TextAnalyzer::readWords(std::istream &inputStream) {
    std::string word;
    while (!inputStream.eof()) {
        inputStream >> word;
        tokens.push_back(std::move(word));
    }
}

void TextAnalyzer::countWords() {
    for (auto &word: tokens) {
        if (!wordToCount.contains(word)) {
            wordToCount[word] = 0;
        }
        wordToCount[word]++;
    }
}

TextAnalyzer &TextAnalyzer::operator+=(const TextAnalyzer &rhs) {
    std::for_each(rhs.wordToCount.begin(), rhs.wordToCount.end(), [this](auto &it) {
        if (!this->wordToCount.contains(it.first)) {
            this->wordToCount[it.first] = 0;
        }
        this->wordToCount[it.first] += it.second;
    });
    tokens.insert(tokens.end(), rhs.tokens.begin(), rhs.tokens.end());
    return *this;
}

TextAnalyzer TextAnalyzer::operator+(const TextAnalyzer &rhs) const {
    TextAnalyzer lhs = *this; // reuse compound assignment
    lhs += rhs;
    return lhs;
}

TextAnalyzer::TextAnalyzer(TextAnalyzer &&rhs) noexcept {
    *this = std::move(rhs);
}

TextAnalyzer::TextAnalyzer(const TextAnalyzer &rhs) = default;

TextAnalyzer &TextAnalyzer::operator=(const TextAnalyzer &rhs) {
    this->wordToCount = rhs.wordToCount;
    this->dict = rhs.dict;
    this->tokens = rhs.tokens;
    return *this;
};

TextAnalyzer &TextAnalyzer::operator=(TextAnalyzer &&rhs) noexcept {
    wordToCount = std::move(rhs.wordToCount);
    tokens = std::move(rhs.tokens);
    this->dict = rhs.dict;
    return *this;
}

std::string TextAnalyzer::str() const {
    std::stringstream stringstream;
    if (dict == nullptr) {
        stringstream << "Dict is not provided, so no lemmas information will be provided: " << std::endl;
    }
    std::vector<std::pair<std::string, int>> v;
    v.resize(wordToCount.size());
    std::copy(wordToCount.begin(), wordToCount.end(), v.begin());
    std::sort(v.begin(), v.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });
    for (auto &[word, count]: v) {
        stringstream << word << ": total count is " << count << std::endl;
        if (dict != nullptr) {
            auto lemmasIdSet = dict->getWordLemmas(word);
            if(lemmasIdSet.size() == 0){
                stringstream << "No lemmas was found for this word";
            }else{
                stringstream << "Possible lemmas id are: ";

                std::copy(lemmasIdSet.begin(),
                          lemmasIdSet.end(),
                          std::ostream_iterator<int>(stringstream, " "));
                stringstream << std::endl;
                for (auto id: lemmasIdSet) {
                    stringstream << "\t" << dict->getLemma(id).str() << std::endl;
                }
            }
        }
        stringstream << std::endl;
    }
    return stringstream.str();
}

void TextAnalyzer::setDict(OpenCorpaDict *corpaDict) {
    this->dict = corpaDict;
}

void TextAnalyzer::stripWords() {
    for (auto &s: tokens) {
        for (int i = s.length() - 1; i >= 0; i--) {
            if (::ispunct(s[i])) {
                s.erase(i, 1);
            } else {
                break;
            }
        }
    }
}

TextAnalyzer::TextAnalyzer() = default;
