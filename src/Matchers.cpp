
#include <string>
#include <algorithm>
#include <vector>

#include "../include/Matchers.hpp"

bool WordsMatcher::match(Sentence::iterator begin, Sentence::iterator end) {
    std::string wordToSearch;
    auto& lemmas = dict->getWordLemmas(*begin);
    if (lemmas.empty()) {
        wordToSearch = *begin;
    } else {
        auto lemma = dict->getLemma(*lemmas.begin());
        wordToSearch = lemma.getInitialForm().getWord();
    }
    return wordsToMatch.count(wordToSearch) > 0;
}

WordsMatcher::WordsMatcher(const std::vector<std::string>& words, OpenCorpaDict* dict) : dict(dict) {
    for (const auto& word: words) {
        auto& lemmas = dict->getWordLemmas(word);
        if (lemmas.empty()) {
            wordsToMatch.insert(word);
            continue;
        }
        auto lemma = dict->getLemma(*lemmas.begin());
        wordsToMatch.insert(lemma.getInitialForm().getWord());
    }
}

int WordsMatcher::size() {
    return 1;
}

PropsMatcher::PropsMatcher(std::set<std::string> propsToMatch, OpenCorpaDict* dict) : propsToMatch(
        std::move(propsToMatch)),
                                                                                      dict(dict) {

}

bool PropsMatcher::match(Sentence::iterator begin, Sentence::iterator end) {
    auto& lemmas = dict->getWordLemmas(*begin);
    if (lemmas.empty()) {
        return false;
    }
    auto lemma = dict->getLemma(*lemmas.begin()).getInitialForm();
    auto props = lemma.getPropNames();
    return std::includes(props.begin(), props.end(), propsToMatch.begin(), propsToMatch.end());
}

int PropsMatcher::size() {
    return 1;
}

bool AnyMatcher::match(Sentence::iterator begin, Sentence::iterator end) {
    return true;
}

int AnyMatcher::size() {
    return 1;
}

bool SequentialMatcher::match(Sentence::iterator begin, Sentence::iterator end) {
    if (std::distance(begin, end) < matchers.size()) {
        return false;
    }
    for (int i = 0; i < matchers.size(); i++) {
        if (!matchers[i]->match(begin + i, end)) {
            return false;
        }
    }
    return true;
}

SequentialMatcher::SequentialMatcher(std::vector<std::shared_ptr<Matcher>> matchers) : matchers(std::move(matchers)) {
}

int SequentialMatcher::size() {
    return matchers.size();
}

