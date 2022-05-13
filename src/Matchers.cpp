
#include <string>
#include <algorithm>

#include "../include/Matchers.hpp"

bool WordsMatcher::match(const std::string& word) {
    std::string wordToSearch;
    auto& lemmas = dict->getWordLemmas(word);
    if (lemmas.empty()) {
        wordToSearch = word;
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

PropsMatcher::PropsMatcher(std::set<std::string> propsToMatch, OpenCorpaDict* dict) : propsToMatch(
        std::move(propsToMatch)),
                                                                                      dict(dict) {

}

bool PropsMatcher::match(const std::string& word) {
    auto& lemmas = dict->getWordLemmas(word);
    if (lemmas.empty()) {
        return false;
    }
    auto lemma = dict->getLemma(*lemmas.begin()).getInitialForm();
    auto props = lemma.getPropNames();
    return std::includes(props.begin(), props.end(), propsToMatch.begin(), propsToMatch.end());
}

bool AnyMatcher::match(const std::string& word) {
    return true;
}
