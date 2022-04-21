#pragma once

#include <vector>
#include <string>

class WordForm {
private:
    std::string word;
    std::vector<std::string> prop_names;
public:
    WordForm(const std::string word, const std::vector<std::string> propNames);

    const std::vector<std::string> &getPropNames() const;

    const std::string &getWord() const;

    std::string str();
};