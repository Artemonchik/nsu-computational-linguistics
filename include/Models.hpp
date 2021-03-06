#pragma once

#include <string>
#include <memory>
#include <vector>
#include "Matchers.hpp"
#include "types.hpp"

class Model {
public:
    std::string name;
    std::vector<Sentence> sentences;
    std::vector<std::shared_ptr<Matcher>> matchers;
};

std::vector<Model> getModels(OpenCorpaDict* dict);