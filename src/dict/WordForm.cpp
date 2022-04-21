//
// Created by sonechka on 23.02.2022.
//

#include <sstream>
#include <iterator>
#include "../../include/dict/WordForm.h"

const std::vector<std::string> &WordForm::getPropNames() const {
    return prop_names;
}

WordForm::WordForm(std::string word, std::vector<std::string> propNames) :
        word(std::move(word)), prop_names(std::move(propNames)) {

}

const std::string &WordForm::getWord() const {
    return word;
}

std::string WordForm::str() {
    std::stringstream stringstream;
    stringstream << word << ": ";
    std::copy(prop_names.begin(),
              prop_names.end(),
              std::ostream_iterator<std::string>(stringstream, " "));

    return stringstream.str();
}
