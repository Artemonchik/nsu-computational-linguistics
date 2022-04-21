

#include <iostream>
#include "../../include/dict/OpenCorpaDict.h"
#include "pugixml.hpp"

OpenCorpaDict::OpenCorpaDict(const std::string& dictFilePath) {
    loadDescriptions(dictFilePath);
    initHashtable();
}

void OpenCorpaDict::loadDescriptions(const std::string& dictFilePath) {
    pugi::xml_document doc;
    doc.load_file(dictFilePath.c_str());
    for (pugi::xml_node description: doc.child("dictionary").child("lemmata").children("lemma")) {
        int id = description.attribute("id").as_int();
        WordForm initialWordValue = initWordForm(description.child("l"));

        std::vector<WordForm> word_forms;
        for (pugi::xml_node word_form_description: description.children("f")) {
            word_forms.push_back(initWordForm(word_form_description));
        }
        lemmas.emplace_back(id, std::move(initialWordValue), std::move(word_forms));
    }
}

void OpenCorpaDict::initHashtable() {
    for (auto& lemma: lemmas) {
        int id = lemma.getId();
        for (auto& wordform: lemma.getForms()) {
            wordToLemmasId[wordform.getWord()].insert(id);
        }
    }
}

WordForm OpenCorpaDict::initWordForm(pugi::xml_node wordFormNode) {
    std::string initial_word = wordFormNode.attribute("t").as_string();
    std::vector<std::string> props;
    for (auto lemma_prop: wordFormNode.children("g")) {
        props.emplace_back(lemma_prop.attribute("v").as_string());
    }

    return {std::move(initial_word), std::move(props)};
}

const std::set<int>& OpenCorpaDict::getWordLemmas(const std::string& word) {
    return wordToLemmasId[word];
}

Lemma OpenCorpaDict::getLemma(int idx) const {
    auto vectorIdx = std::lower_bound(lemmas.begin(), lemmas.end(), idx,
                                      [](const auto& info, int value) {
                                          return info.getId() < value;
                                      });
    return *vectorIdx;
}

int OpenCorpaDict::size() {
    return (int) lemmas.size();
}
