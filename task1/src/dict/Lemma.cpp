//
// Created by sonechka on 23.02.2022.
//

#include "../../include/dict/WordForm.h"
#include "../../include/dict/Lemma.h"

Lemma::Lemma(int lemmaId,
             WordForm initialForm,
             std::vector<WordForm> forms)
        : lemma_id(lemmaId),
          initial_form(std::move(initialForm)),
          forms(std::move(forms)) {}

const std::vector<WordForm> &Lemma::getForms() const {
    return forms;
}

int Lemma::getId() const {
    return lemma_id;
}

std::string Lemma::str() {
    return "id: " + std::to_string(lemma_id) + ", " +  initial_form.str();
}
