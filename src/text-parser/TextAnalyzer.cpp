//
// Created by sonechka on 02.03.2022.
//

#include <sstream>
#include <map>
#include "../../include/text-parser/TextAnalyzer.h"
#include "../../include/text-parser/Converter.hpp"

TextAnalyzer::TextAnalyzer(std::istream& inputStream) {
    readWords(inputStream);
    toLower();
    countWordsFreq();
    //TODO to lower case
}

void TextAnalyzer::readWords(std::istream& inputStream) {
    std::string word;
    while (!inputStream.eof()) {
        inputStream >> word;
        auto wword = convertToWString(word);

        string32 token;
        for (int i = 0; i < wword.size(); i++) {
            if (std::iswpunct(wword[i])) {
                if (!token.empty()) {
                    tokens.push_back(convertToString(token));
                }
                token.resize(0);
                tokens.push_back(convertToString(string32(1, wword[i])));
                continue;
            }
            token.push_back(wword[i]);
        }
        if (token.size() != 0) {
            tokens.push_back(convertToString(token));
        }
    }
}

void TextAnalyzer::countWordsFreq() {
    for (auto& word: tokens) {
        if (!wordToCount.contains(word)) {
            wordToCount[word] = 0;
        }
        wordToCount[word]++;
    }
}

TextAnalyzer& TextAnalyzer::operator+=(const TextAnalyzer& rhs) {
    std::for_each(rhs.wordToCount.begin(), rhs.wordToCount.end(), [this](auto& it) {
        if (!this->wordToCount.contains(it.first)) {
            this->wordToCount[it.first] = 0;
        }
        this->wordToCount[it.first] += it.second;
    });
    tokens.insert(tokens.end(), rhs.tokens.begin(), rhs.tokens.end());
    return *this;
}

TextAnalyzer TextAnalyzer::operator+(const TextAnalyzer& rhs) const {
    TextAnalyzer lhs = *this; // reuse compound assignment
    lhs += rhs;
    return lhs;
}

TextAnalyzer::TextAnalyzer(TextAnalyzer&& rhs) noexcept {
    *this = std::move(rhs);
}

TextAnalyzer::TextAnalyzer(const TextAnalyzer& rhs) = default;

TextAnalyzer& TextAnalyzer::operator=(const TextAnalyzer& rhs) {
    this->wordToCount = rhs.wordToCount;
    this->dict = rhs.dict;
    this->tokens = rhs.tokens;
    return *this;
};

TextAnalyzer& TextAnalyzer::operator=(TextAnalyzer&& rhs) noexcept {
    wordToCount = std::move(rhs.wordToCount);
    tokens = std::move(rhs.tokens);
    this->dict = rhs.dict;
    return *this;
}

std::string TextAnalyzer::str(int limit, std::set<std::string>& props) const {
    std::vector<std::pair<std::string, int>> v;
    v.resize(wordToCount.size());
    std::copy(wordToCount.begin(), wordToCount.end(), v.begin());
    std::sort(v.begin(), v.end(), [](auto& left, auto& right) {
        return left.second > right.second;
    });
    int i = 0;
    std::stringstream result;
    for (auto &[word, count]: v) {
        std::stringstream stringstream;
        if (i > limit) {
            break;
        }
        stringstream << word << ": total count is " << count << std::endl;
        if (dict == nullptr) {
            continue;
        }
        auto lemmasIdSet = dict->getWordLemmas(word);
        if (lemmasIdSet.size() == 0) {
            stringstream << "No lemmas was found for this word" << std::endl;
            result << stringstream.str();
            continue;
        }
        Lemma first_lemma = dict->getLemma(*lemmasIdSet.begin());
        if (!props.empty()) {
            std::set<std::string> intersect;
            std::set<std::string> lemmasPropSet(first_lemma.getInitialForm().getPropNames().begin(),
                                                first_lemma.getInitialForm().getPropNames().end());
            std::set_intersection(props.begin(), props.end(),
                                  lemmasPropSet.begin(), lemmasPropSet.end(),
                                  std::inserter(intersect, intersect.begin()));
            if (intersect.empty()) {
                continue;
            }
        }
        stringstream << "Possible lemmas id are: ";

        std::copy(lemmasIdSet.begin(),
                  lemmasIdSet.end(),
                  std::ostream_iterator<int>(stringstream, " "));
        stringstream << std::endl;
        for (auto id: lemmasIdSet) {
            stringstream << "\t" << dict->getLemma(id).str() << std::endl;
        }

        i++;

        stringstream << std::endl;
        result << stringstream.str();
    }
    return result.str();
}

void TextAnalyzer::setDict(OpenCorpaDict* corpaDict) {
    this->dict = corpaDict;
}


void ru_utf8_tolower(char* str) {
    if (!str) return;
    unsigned char* a, * b;
    a = (unsigned char*) str;
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

void TextAnalyzer::toLower() {
    for (auto& word: tokens) {
        auto wword = convertToWString(word);
        std::transform(wword.begin(),
                       wword.end(),
                       wword.begin(),
                       [](auto c) {
                           return std::towlower(c);
                       });
        word = convertToString(wword);
    }
}

int TextAnalyzer::countWords() {
    return tokens.size();
}

double TextAnalyzer::countNotRecognizedPart() {
    int totalWords = 0;
    int recognized = 0;
    for (auto&[word, count]: wordToCount) {
        auto lemmasIdSet = dict->getWordLemmas(word);
        if (!lemmasIdSet.empty()) {
            recognized++;
        }
        totalWords++;
    }
    return static_cast<double>(recognized) / totalWords;
}

double TextAnalyzer::countAmbiguity() {
    int totalPossibleLemmas = 0;
    int wordsWithLemma = 0;
    for (auto&[word, count]: wordToCount) {
        auto lemmasIdSet = dict->getWordLemmas(word);
        if (lemmasIdSet.empty()) {
            continue;
        }
        totalPossibleLemmas += lemmasIdSet.size();
        wordsWithLemma++;
    }
    return static_cast<double>(wordsWithLemma) / totalPossibleLemmas;
}

bool TextAnalyzer::areTokenEquals(std::string& string1, std::string& string2) {
    if (string1 == string2) {
        return true;
    }
    auto l1 = dict->getWordLemmas(string1);
    auto l2 = dict->getWordLemmas(string2);
    std::set<int> intersect;
    std::set_intersection(l1.begin(), l1.end(),
                          l2.begin(), l2.end(),
                          std::inserter(intersect, intersect.begin()));
    return intersect.size() > 0;
}

static bool isPunctuation(std::string& token) {
    string32 wtoken = convertToWString(token);
    if (wtoken.size() != 1) {
        return false;
    }
    if (std::iswpunct(wtoken[0])) {
        return true;
    } else {
        return false;
    }
}

static std::vector<std::string> normalize(OpenCorpaDict& dict, std::vector<std::string>& tokens) {
    for (auto& token: tokens) {
        auto lemmas = dict.getWordLemmas(token);
        if (lemmas.size() == 0) {
            continue;
        }
        token = (dict.getLemma(*lemmas.begin()).getInitialForm().getWord());
    }
    return tokens;
}


std::pair<std::map<std::vector<std::string>, int>, std::map<std::vector<std::string>, int>>
TextAnalyzer::findExtentions(TextAnalyzer& rhs, int limit) {
    std::map<std::vector<std::string>, int> l_ngrams;
    std::map<std::vector<std::string>, int> r_ngrams;
    tokens = normalize(*rhs.dict, tokens);
    for (int i = 0; i < rhs.tokens.size(); i++) {
        bool contFlag = false;
        for (int j = 0; j < tokens.size(); j++) {
            if (i + j >= rhs.tokens.size()) {
                contFlag = true;
                break;
            }
            if (!areTokenEquals(tokens[j], rhs.tokens[i + j])) {
                contFlag = true;
                break;
            }
        }
        if (contFlag) {
            continue;
        }
        auto leftExtensions = getLeftExtentions(i, limit, rhs);
        while (leftExtensions.size() >= tokens.size()) {
            if (!l_ngrams.contains(leftExtensions)) {
                l_ngrams[leftExtensions] = 0;
            }
            l_ngrams[leftExtensions] += 1;
            leftExtensions.erase(leftExtensions.begin());
        }

        std::vector<std::string> rightExtensions = getRightExtentions(i, limit, rhs);
        while (rightExtensions.size() >= tokens.size()) {
            if (!r_ngrams.contains(rightExtensions)) {
                r_ngrams[rightExtensions] = 0;
            }
            r_ngrams[rightExtensions] += 1;
            rightExtensions.pop_back();
        }
    }

    return {l_ngrams, r_ngrams};
}


std::vector<std::string> TextAnalyzer::getLeftExtentions(int i, int limit, TextAnalyzer& rhs) {
    std::vector<std::string> leftExtensions = tokens;
    for (int j = tokens.size(); j < limit; j++) {
        if (i - j < 0) {
            break;
        }
        if (isPunctuation(rhs.tokens[i - j])) {
            break;
        }
        auto lemmas = dict->getWordLemmas(rhs.tokens[i - j]);
        if (lemmas.size() == 0) {
            leftExtensions.push_back(rhs.tokens[i - j]);
            continue;
        }
        leftExtensions.push_back(dict->getLemma(*lemmas.begin()).getInitialForm().getWord());
    }
    std::reverse(leftExtensions.begin(), leftExtensions.end());
    std::reverse(leftExtensions.end() - tokens.size(), leftExtensions.end());
    return leftExtensions;
}

std::vector<std::string> TextAnalyzer::getRightExtentions(int i, int limit, TextAnalyzer& rhs) {
    std::vector<std::string> rightExtentions = tokens;
    for (int j = tokens.size(); j < limit; j++) {
        if (i + j >= rhs.tokens.size()) {
            break;
        }
        if (isPunctuation(rhs.tokens[i + j])) {
            break;
        }
        auto lemmas = dict->getWordLemmas(rhs.tokens[i + j]);
        if (lemmas.size() == 0) {
            rightExtentions.push_back(rhs.tokens[i + j]);
            continue;
        }
        rightExtentions.push_back(dict->getLemma(*lemmas.begin()).getInitialForm().getWord());
    }
    return rightExtentions;
}

TextAnalyzer::TextAnalyzer() = default;
