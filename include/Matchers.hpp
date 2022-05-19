#pragma once

#include <vector>
#include <string>
#include <memory>
#include "dict/OpenCorpaDict.h"
#include "types.hpp"
class Matcher {
public:
    virtual bool match(Sentence::iterator begin, Sentence::iterator end) = 0;
    virtual int size() = 0;;
};

class WordsMatcher : public Matcher {
private:
    std::set<std::string> wordsToMatch;
    OpenCorpaDict* dict;
public:
    WordsMatcher(const std::vector<std::string>& words, OpenCorpaDict* dict);

    int size() override;

    bool match(Sentence::iterator begin, Sentence::iterator end) override;
};

class PropsMatcher : public Matcher {
private:
public:
    int size() override;

private:
    std::set<std::string> propsToMatch;
    OpenCorpaDict* dict;
public:
    PropsMatcher(std::set<std::string> propsToMatch, OpenCorpaDict* dict);

    bool match(Sentence::iterator begin, Sentence::iterator end) override;

};

class SequentialMatcher : public Matcher {
private:
    std::vector<std::shared_ptr<Matcher>> matchers;
public:
    int size() override;

    SequentialMatcher(std::vector<std::shared_ptr<Matcher>> matchers);

    bool match(Sentence::iterator begin, Sentence::iterator end) override;
};

class AnyMatcher : public Matcher {

public:
    int size() override;

    bool match(Sentence::iterator begin, Sentence::iterator end) override;
};