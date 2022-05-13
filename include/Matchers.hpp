#pragma once

#include <vector>
#include <string>
#include "dict/OpenCorpaDict.h"

class Matcher {
public:
    virtual bool match(const std::string& word) = 0;
};

class WordsMatcher : public Matcher {
private:
    std::set<std::string> wordsToMatch;
    OpenCorpaDict* dict;
public:
    WordsMatcher(const std::vector<std::string>& words, OpenCorpaDict* dict);

    bool match(const std::string& word) override;
};

class PropsMatcher : public Matcher {
private:
    std::set<std::string> propsToMatch;
    OpenCorpaDict* dict;
public:
    PropsMatcher(std::set<std::string> propsToMatch, OpenCorpaDict* dict);

    bool match(const std::string& word) override;

};

class AnyMatcher: public Matcher{
public:
    bool match(const std::string& word) override;
};