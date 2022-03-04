#pragma once

#include <istream>
#include <vector>
#include <unordered_map>
#include <set>

#include "pugixml.hpp"
#include "Lemma.h"

class OpenCorpaDict {
private:
    std::vector<Lemma> lemmas;
    std::unordered_map<std::string, std::set<int>> wordToLemmasId;
public:
    explicit OpenCorpaDict(const std::string &dictFilePath);

    const std::set<int> &getWordLemmas(const std::string &word);

    Lemma getLemma(int idx) const;

private:

    void loadDescriptions(const std::string &dictFilePath);

    static WordForm initWordForm(pugi::xml_node wordFormNode);

    void initHashtable();
};